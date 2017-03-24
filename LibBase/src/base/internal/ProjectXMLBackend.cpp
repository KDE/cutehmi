#include "../../../include/base/internal/ProjectXMLBackend.hpp"
#include "../../../include/base/internal/PluginNodeData.hpp"
#include "../../../include/base/xml/ParseHelper.hpp"
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

constexpr const char * ProjectXMLBackend::NAMESPACE_URI;

ProjectXMLBackend::ProjectXMLBackend(ProjectModel * model, PluginLoader * pluginLoader, QQmlContext * qmlContext):
	m(new Members{{}, model, pluginLoader, qmlContext})
{
}

void ProjectXMLBackend::load(QIODevice & device)
{
	m->xmlReader.setDevice(& device);

	xml::ParseHelper helper(& m->xmlReader, NAMESPACE_URI);
	helper << xml::ParseElement("cutehmi_project", {xml::ParseAttribute("name"),
													xml::ParseAttribute("version", "[0-9]+\\.[0-9]+")}, 1, 1);
	while (helper.readNextRecognizedElement()) {
		if (m->xmlReader.name() == "cutehmi_project") {
			m->model->root().data().setName(m->xmlReader.attributes().value("name").toString());
			QVector<QStringRef> versionMM = m->xmlReader.attributes().value("version").split(".");
			bool okMajor = true;
			bool okMinor = true;
			int versionMajor = versionMM.value(0).toInt(& okMajor);
			int versionMinor = versionMM.value(1).toInt(& okMinor);
			if (!okMajor || !okMinor) {
				m->xmlReader.raiseError(QObject::tr("Could not parse 'version' attribute. Value of the attribute must be in 'MAJOR.MINOR' format, where 'MAJOR' and 'MINOR' are non-negative integers."));
				break;
			}
			CUTEHMI_BASE_QDEBUG("Document version is '" << versionMajor << "."  << versionMinor << "'.");
			if (versionMajor == 1) {
				Loader1 loader(& m->model->root(), m->pluginLoader, m->qmlContext);
				loader.parse(m->xmlReader, versionMinor);
			} else
				throw UnsupportedDocumentVersionException(versionMajor, versionMinor);
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

constexpr int ProjectXMLBackend::Loader1::VERSION_MAJOR;

ProjectXMLBackend::Loader1::Loader1(ProjectNode * root, PluginLoader * pluginLoader, QQmlContext * qmlContext):
	m_root(root),
	m_pluginLoader(pluginLoader),
	m_qmlContext(qmlContext)
{
}

void ProjectXMLBackend::Loader1::parse(QXmlStreamReader & reader, int versionMinor)
{
	CUTEHMI_BASE_QDEBUG("Loader starts parsing a document...");

	if (versionMinor > 0)
		throw UnsupportedDocumentVersionException(VERSION_MAJOR, versionMinor);

	xml::ParseHelper helper(& reader, ProjectXMLBackend::NAMESPACE_URI);
	helper << xml::ParseElement("plugin", {xml::ParseAttribute("binary", "[a-z|A-Z|0-9|_-]+"), xml::ParseAttribute("min_version", "[0-9]+\\.[0-9]+")}, 0)
		   << xml::ParseElement("context_properties", 0);

	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "plugin") {
			QString binary = reader.attributes().value("binary").toString();
			QString minVersion = reader.attributes().value("min_version").toString();
#ifdef CUTEHMI_DEBUG
			binary.append('d');
#endif
			Plugin * plugin = (m_pluginLoader->loadPlugin(binary, minVersion));	// Note: loadPlugin() may throw exception.
			IPlugin * pluginInstance = qobject_cast<IPlugin *>(plugin->instance());
			if (pluginInstance == 0)
				throw MissingInterfaceException(binary, plugin->version(), CUTEHMI_BASE_IPLUGIN_IID);
			ProjectNode * pluginNode;
			if (!plugin->id().isEmpty())
				pluginNode = m_root->addChild(plugin->id(), ProjectNode::Data(plugin->name()), false);
			else
				pluginNode = m_root->addChild(ProjectNode::Data(plugin->name()), false);
			pluginNode->data().append(std::unique_ptr<DataBlock>(new PluginNodeData(plugin, minVersion)));
			pluginNode->addExtension(plugin);
			pluginInstance->init(*pluginNode);
			parsePlugin(reader, *pluginNode);
		} else if (reader.name() == "context_properties")
			parseNodeRef(reader, *m_root);
	}
}

void ProjectXMLBackend::Loader1::parsePlugin(QXmlStreamReader & reader, ProjectNode & node)
{
	Plugin * plugin = qobject_cast<Plugin *>(node.extension(Plugin::staticMetaObject.className()));
	CUTEHMI_BASE_ASSERT(plugin != nullptr, "Pointer must be not nullptr.");

	xml::ParseHelper helper(& reader, ProjectXMLBackend::NAMESPACE_URI);
	helper << xml::ParseElement("extension", {xml::ParseAttribute("object", XMLBackendPlugin::staticMetaObject.className())}, 0);

	while (helper.readNextRecognizedElement()) {
		if ((reader.name() == "extension") && (reader.attributes().value("object") == XMLBackendPlugin::staticMetaObject.className())) {
			XMLBackendPlugin * xmlPlugin = qobject_cast<XMLBackendPlugin *>(node.extension(XMLBackendPlugin::staticMetaObject.className()));
			if (xmlPlugin == nullptr)
				throw MissingExtensionException(plugin->binary(), plugin->version(), XMLBackendPlugin::staticMetaObject.className());
			xmlPlugin->implementation()->readXML(reader, node);
		}
	}
}

void ProjectXMLBackend::Loader1::parseNodeRef(QXmlStreamReader & reader, ProjectNode & currentNode)
{
	xml::ParseHelper helper(& reader, ProjectXMLBackend::NAMESPACE_URI);
	helper << xml::ParseElement("node_ref", {xml::ParseAttribute("id")}, 0)
		   << xml::ParseElement("extension_ref", {xml::ParseAttribute("object"), xml::ParseAttribute("context_property", "[a-z|A-Z|_][a-z|A-Z|0-9|_]*")}, 0);

	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "node_ref") {
			QString id = reader.attributes().value("id").toString();
			if (currentNode.child(id))
				parseNodeRef(reader, *currentNode.child(id));
			else
				CUTEHMI_BASE_QWARNING("Could not find child node with an id '"<< id << "' referenced at: " << xml::internal::readerPositionString(reader) << ".");
		} else if (reader.name() == "extension_ref") {
			QString contextProperty = reader.attributes().value("context_property").toString();
			if (contextProperty.startsWith("cutehmi_"))
				reader.raiseError(QObject::tr("Context properties starting with 'cutehmi_' string are reserved by CuteHMI."));
			else {
				QString object = reader.attributes().value("object").toString();
				if (m_qmlContext->contextProperty(contextProperty).isValid())
					CUTEHMI_BASE_QWARNING("Context property '"<< contextProperty << "' has been already set. Redefined at: " << xml::internal::readerPositionString(reader) << ".");
				if (!currentNode.extension(object))
					CUTEHMI_BASE_QWARNING("Could not find extension object '"<< object << "' referenced at: " << xml::internal::readerPositionString(reader) << ".");
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
