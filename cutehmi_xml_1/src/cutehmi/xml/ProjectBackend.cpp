#include "../../../include/cutehmi/xml/ProjectBackend.hpp"
#include "../../../include/cutehmi/xml/BackendPlugin.hpp"

#include <cutehmi/ProjectNodeData.hpp>

#include <QIODevice>
#include <QtDebug>
#include <QLibraryInfo>
#include <QQmlContext>

namespace cutehmi {
namespace xml {

ProjectBackend::ProjectBackend(QIODevice * device, QQmlContext * qmlContext):
	m(new Members{{}, qmlContext})
{
	m->xmlReader.setDevice(device);
}

void ProjectBackend::load(const ProjectPluginLoader & pluginLoader, ProjectNode & rootNode) noexcept(false)
{
	if (m->xmlReader.device()->open(QIODevice::ReadOnly)) {
		QStringList supportedVersions1;
		supportedVersions1 << "http://michpolicht.github.io/CuteHMI/cutehmi_1/xsd/1.0/";

		ParseHelper helper(& m->xmlReader, supportedVersions1);
		helper << ParseElement("cutehmi_project", {ParseAttribute("name")}, 1, 1);
		while (helper.readNextRecognizedElement()) {
			if (m->xmlReader.name() == "cutehmi_project") {
				rootNode.data().setName(m->xmlReader.attributes().value("name").toString());

				if (supportedVersions1.contains(helper.lastRecognizedNamespaceURI())) {
					Loader1 loader(& rootNode, & pluginLoader, m->qmlContext);
					loader.parse(helper);
				}
			}
		}

		try {
			if (m->xmlReader.hasError())
				throw ParseErrorException(m->xmlReader);
			if (!m->xmlReader.readNextStartElement() && m->xmlReader.atEnd())
				CUTEHMI_LOG_DEBUG("Finished parsing the document.");
			else {
				m->xmlReader.raiseError(QObject::tr("Could not finish parsing the document."));
				throw ParseErrorException(m->xmlReader);
			}
		} catch (...) {
			m->xmlReader.device()->close();
			throw;
		}

		m->xmlReader.device()->close();
	} else
		throw DeviceOpenReadException();
}

//void ProjectBackend::load(QIODevice & device)
//{
//	m->xmlReader.setDevice(& device);

//	QStringList supportedVersions1;
//	supportedVersions1 << "http://michpolicht.github.io/CuteHMI/cutehmi_1/xsd/1.0/";

//	ParseHelper helper(& m->xmlReader, supportedVersions1);
//	helper << ParseElement("cutehmi_project", {ParseAttribute("name")}, 1, 1);
//	while (helper.readNextRecognizedElement()) {
//		if (m->xmlReader.name() == "cutehmi_project") {
//			m->model->root().data().setName(m->xmlReader.attributes().value("name").toString());

//			if (supportedVersions1.contains(helper.lastRecognizedNamespaceURI())) {
//				Loader1 loader(& m->model->root(), m->pluginLoader, m->qmlContext);
//				loader.parse(helper);
//			}
//		}
//	}

//	if (m->xmlReader.hasError())
//		throw ParseErrorException(m->xmlReader);
//	if (!m->xmlReader.readNextStartElement() && m->xmlReader.atEnd())
//		CUTEHMI_LOG_DEBUG("Finished parsing the document.");
//	else {
//		m->xmlReader.raiseError(QObject::tr("Could not finish parsing the document."));
//		throw ParseErrorException(m->xmlReader);
//	}
//}

//bool XMLProjectBackend::save(QIODevice * device)
//{
//}

ProjectBackend::Loader1::Loader1(ProjectNode * root, const ProjectPluginLoader * pluginLoader, QQmlContext * qmlContext):
	m_root(root),
	m_pluginLoader(pluginLoader),
	m_qmlContext(qmlContext)
{
}

void ProjectBackend::Loader1::parse(const ParseHelper & parentHelper)
{
	CUTEHMI_LOG_DEBUG("Loader starts parsing a document...");

	ParseHelper helper(& parentHelper);
	helper << ParseElement("plugin", {ParseAttribute("binary", "[a-z|A-Z|0-9|_-]+"), ParseAttribute("req_minor", "-?[0-9]+")}, 0)
		   << ParseElement("context_properties", 0);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "plugin") {
			QString binary = reader.attributes().value("binary").toString();
			bool reqMinorOk;
			int reqMinor = reader.attributes().value("req_minor").toInt(& reqMinorOk);
			if (!reqMinorOk) {
				helper.raiseError(QObject::tr("Could not convert 'req_minor' attribute to integer."));
				break;
			}
			ProjectNode * pluginNode = m_pluginLoader->addPluginNode(binary, reqMinor, *m_root);
			parsePlugin(helper, *pluginNode);
		} else if (reader.name() == "context_properties")
			parseNodeRef(helper, *m_root);
	}
}

void ProjectBackend::Loader1::parsePlugin(const ParseHelper & parentHelper, ProjectNode & node)
{
	Plugin * plugin = qobject_cast<Plugin *>(node.extension(Plugin::staticMetaObject.className()));
	CUTEHMI_ASSERT(plugin != nullptr, "pointer must be not nullptr");

	ParseHelper helper(& parentHelper);
	helper << ParseElement("extension", {ParseAttribute("object", BackendPlugin::staticMetaObject.className())}, 0);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if ((reader.name() == "extension") && (reader.attributes().value("object") == BackendPlugin::staticMetaObject.className())) {
			BackendPlugin * xmlPlugin = qobject_cast<BackendPlugin *>(node.extension(BackendPlugin::staticMetaObject.className()));
			if (xmlPlugin == nullptr)
				throw MissingExtensionException(plugin->binary(), plugin->version(), BackendPlugin::staticMetaObject.className());
			xmlPlugin->implementation()->readXML(static_cast<QXmlStreamReader &>(helper), node);
		}
	}
}

void ProjectBackend::Loader1::parseNodeRef(const ParseHelper & parentHelper, ProjectNode & currentNode)
{
	ParseHelper helper(& parentHelper);
	helper << ParseElement("node_ref", {ParseAttribute("id")}, 0)
		   << ParseElement("extension_ref", {ParseAttribute("object"), ParseAttribute("context_property", "[a-z|A-Z|_][a-z|A-Z|0-9|_]*")}, 0);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "node_ref") {
			QString id = reader.attributes().value("id").toString();
			if (currentNode.child(id))
				parseNodeRef(helper, *currentNode.child(id));
			else
				CUTEHMI_LOG_WARNING("Could not find child node with an id '"<< id << "' referenced at: " << internal::readerPositionString(reader) << ".");
		} else if (reader.name() == "extension_ref") {
			QString contextProperty = reader.attributes().value("context_property").toString();
			if (contextProperty.startsWith("cutehmi_"))
				helper.raiseError(QObject::tr("Context properties starting with 'cutehmi_' string are reserved by CuteHMI."));
			else {
				QString objectName = reader.attributes().value("object").toString();
				if (m_qmlContext->contextProperty(contextProperty).isValid())
					CUTEHMI_LOG_WARNING("Context property '"<< contextProperty << "' has been already set. Redefined at: " << internal::readerPositionString(reader) << ".");
				QObject * object = currentNode.extension(objectName);
				if (object == nullptr)
					CUTEHMI_LOG_WARNING("Could not find extension object '"<< objectName << "' referenced at: " << internal::readerPositionString(reader) << ".");
				else
					m_qmlContext->setContextProperty(contextProperty, object);
			}
		}
	}
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
