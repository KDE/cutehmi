#include "../../../include/base/internal/ProjectXMLBackend.hpp"
#include "../../../include/base/internal/PluginNodeData.hpp"
#include "../../../include/base/IPlugin.hpp"
#include "../../../include/base/XMLBackendPlugin.hpp"
#include "../../../include/base/PluginLoader.hpp"

#include <QIODevice>
#include <QtDebug>
#include <QLibraryInfo>
#include <QQmlContext>

namespace cutehmi {
namespace base {
namespace internal {

ProjectXMLBackend::ProjectXMLBackend(ProjectModel * model, PluginLoader * pluginLoader, QQmlContext * qmlContext):
	m(new Members{{}, model, pluginLoader, qmlContext})
{
}

void ProjectXMLBackend::load(QIODevice & device)
{
	m->xmlReader.setDevice(& device);

	QStringList supportedVersions1;
	supportedVersions1 << "http://michpolicht.github.io/CuteHMI/BaseLib/xsd/1.0/";

	xml::ParseHelper helper(& m->xmlReader, supportedVersions1);
	helper << xml::ParseElement("cutehmi_project", {xml::ParseAttribute("name")}, 1, 1);
	while (helper.readNextRecognizedElement()) {
		if (m->xmlReader.name() == "cutehmi_project") {
			m->model->root().data().setName(m->xmlReader.attributes().value("name").toString());

			if (supportedVersions1.contains(helper.lastRecognizedNamespaceURI())) {
				Loader1 loader(& m->model->root(), m->pluginLoader, m->qmlContext);
				loader.parse(helper);
			}
		}
	}

	if (m->xmlReader.hasError())
		throw ParseErrorException(m->xmlReader);
	if (!m->xmlReader.readNextStartElement() && m->xmlReader.atEnd())
		CUTEHMI_BASE_QDEBUG("Finished parsing the document.");
	else {
		m->xmlReader.raiseError(QObject::tr("Could not finish parsing the document."));
		throw ParseErrorException(m->xmlReader);
	}
}

//bool XMLProjectBackend::save(QIODevice * device)
//{
//}

ProjectXMLBackend::Loader1::Loader1(ProjectNode * root, PluginLoader * pluginLoader, QQmlContext * qmlContext):
	m_root(root),
	m_pluginLoader(pluginLoader),
	m_qmlContext(qmlContext)
{
}

void ProjectXMLBackend::Loader1::parse(const xml::ParseHelper & parentHelper)
{
	CUTEHMI_BASE_QDEBUG("Loader starts parsing a document...");

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("plugin", {xml::ParseAttribute("binary", "[a-z|A-Z|0-9|_-]+"), xml::ParseAttribute("req_minor", "-?[0-9]+")}, 0)
		   << xml::ParseElement("context_properties", 0);

	QXmlStreamReader & reader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "plugin") {
			QString binary = reader.attributes().value("binary").toString();
			bool reqMinorOk;
			int reqMinor = reader.attributes().value("req_minor").toInt(& reqMinorOk);
			if (!reqMinorOk) {
				reader.raiseError(QObject::tr("Could not convert 'req_minor' attribute to integer."));
				break;
			}
#ifdef CUTEHMI_DEBUG
			binary.append('d');
#endif
			Plugin * plugin = (m_pluginLoader->loadPlugin(binary, reqMinor));	// Note: loadPlugin() may throw exception.
			IPlugin * pluginInstance = qobject_cast<IPlugin *>(plugin->instance());
			if (pluginInstance == 0)
				throw MissingInterfaceException(binary, plugin->version(), CUTEHMI_BASE_IPLUGIN_IID);
			ProjectNode * pluginNode;
			if (!plugin->id().isEmpty())
				pluginNode = m_root->addChild(plugin->id(), ProjectNode::Data(plugin->name()), false);
			else
				pluginNode = m_root->addChild(ProjectNode::Data(plugin->name()), false);
			pluginNode->data().append(std::unique_ptr<DataBlock>(new PluginNodeData(plugin, reqMinor)));
			pluginNode->addExtension(plugin);
			pluginInstance->init(*pluginNode);
			parsePlugin(helper, *pluginNode);
		} else if (reader.name() == "context_properties")
			parseNodeRef(helper, *m_root);
	}
}

void ProjectXMLBackend::Loader1::parsePlugin(const xml::ParseHelper & parentHelper, ProjectNode & node)
{
	Plugin * plugin = qobject_cast<Plugin *>(node.extension(Plugin::staticMetaObject.className()));
	CUTEHMI_BASE_ASSERT(plugin != nullptr, "pointer must be not nullptr");

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("extension", {xml::ParseAttribute("object", XMLBackendPlugin::staticMetaObject.className())}, 0);

	QXmlStreamReader & reader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if ((reader.name() == "extension") && (reader.attributes().value("object") == XMLBackendPlugin::staticMetaObject.className())) {
			XMLBackendPlugin * xmlPlugin = qobject_cast<XMLBackendPlugin *>(node.extension(XMLBackendPlugin::staticMetaObject.className()));
			if (xmlPlugin == nullptr)
				throw MissingExtensionException(plugin->binary(), plugin->version(), XMLBackendPlugin::staticMetaObject.className());
			xmlPlugin->implementation()->readXML(reader, node);
		}
	}
}

void ProjectXMLBackend::Loader1::parseNodeRef(const xml::ParseHelper & parentHelper, ProjectNode & currentNode)
{
	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("node_ref", {xml::ParseAttribute("id")}, 0)
		   << xml::ParseElement("extension_ref", {xml::ParseAttribute("object"), xml::ParseAttribute("context_property", "[a-z|A-Z|_][a-z|A-Z|0-9|_]*")}, 0);

	QXmlStreamReader & reader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "node_ref") {
			QString id = reader.attributes().value("id").toString();
			if (currentNode.child(id))
				parseNodeRef(helper, *currentNode.child(id));
			else
				CUTEHMI_BASE_QWARNING("Could not find child node with an id '"<< id << "' referenced at: " << xml::internal::readerPositionString(reader) << ".");
		} else if (reader.name() == "extension_ref") {
			QString contextProperty = reader.attributes().value("context_property").toString();
			if (contextProperty.startsWith("cutehmi_"))
				reader.raiseError(QObject::tr("Context properties starting with 'cutehmi_' string are reserved by CuteHMI."));
			else {
				QString objectName = reader.attributes().value("object").toString();
				if (m_qmlContext->contextProperty(contextProperty).isValid())
					CUTEHMI_BASE_QWARNING("Context property '"<< contextProperty << "' has been already set. Redefined at: " << xml::internal::readerPositionString(reader) << ".");
				QObject * object = currentNode.extension(objectName);
				if (object == nullptr)
					CUTEHMI_BASE_QWARNING("Could not find extension object '"<< objectName << "' referenced at: " << xml::internal::readerPositionString(reader) << ".");
				else
					m_qmlContext->setContextProperty(contextProperty, object);
			}
		}
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
