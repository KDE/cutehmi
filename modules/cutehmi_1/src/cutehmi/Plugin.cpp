#include "../../include/cutehmi/Plugin.hpp"

namespace cutehmi {

QString Plugin::NameToBinary(const QString & name)
{
	QString binary(name);
#ifndef CUTEHMI_NDEBUG
	binary.append('d');
#endif
	return binary;
}

QString Plugin::NameFromBinary(const QString & binary)
{
	QString name(binary);
#ifndef CUTEHMI_NDEBUG
	name.chop(1);
#endif
	return name;
}

Plugin::Metadata Plugin::BinaryMetadata(const QString & binary)
{
	QPluginLoader loader(binary);
	return Plugin::Metadata(binary, loader.metaData().value("MetaData").toObject().toVariantMap());
}

bool Plugin::BinaryExists(const QString & binary)
{
	QPluginLoader loader(binary);
	return !loader.fileName().isEmpty();
}

int Plugin::CheckReqMinors(int reqMinor, QList<Metadata> & metadataList)
{
	if (metadataList.empty())
		return 0;

	Metadata metadata = metadataList.last();
	if (metadata.minor() < reqMinor)
		return reqMinor;

	QVariantList dependencies = metadata.data().value("dependencies").toList();
	for (auto dependency = dependencies.begin(); dependency != dependencies.end(); ++dependency) {
		QMap<QString, QVariant> map = dependency->toMap();
		QString name = map.value("name").toString();
		reqMinor = map.value("reqMinor").toInt();
		QString binary = NameToBinary(name);
		Metadata depMetadata = BinaryMetadata(NameToBinary(name));
		metadataList.append(depMetadata);
		if (!BinaryExists(binary))
			return -1;
		if ((reqMinor = CheckReqMinors(reqMinor, metadataList)) != 0)
			return reqMinor;
	}
	metadataList.removeLast();
	return 0;
}

QVariantMap Plugin::Metadata::SanitizeMedatada(const QString & binary, const QVariantMap & metadata)
{
	QVariantMap sanitized(metadata);

	if (!sanitized.contains("name")) {
		QString fallback(NameFromBinary(binary));
		CUTEHMI_LOG_WARNING("Using '" << fallback << "' as a fallback for missing 'name' property in '" << binary << "' metadata.");
		sanitized.insert("name", fallback);
	}
	if (!sanitized.contains("minor")) {
		int fallback = -1;
		CUTEHMI_LOG_WARNING("Using '" << fallback << "' as a fallback for missing 'minor' property in '" << binary << "' metadata.");
		sanitized.insert("minor", fallback);
	}
	if (!sanitized.contains("micro")) {
		int fallback = -1;
		CUTEHMI_LOG_WARNING("Using '" << fallback << "' as a fallback for missing 'micro' property in '" << binary << "' metadata.");
		sanitized.insert("micro", fallback);
	}

//	QStringList unavailableMetaData;
//	if (!unavailableMetaData.isEmpty())
//		CUTEHMI_LOG_WARNING("Plugin '" << binary <<"' is missing '" << unavailableMetaData.join("', '") << "' metadata information.");

	return sanitized;
}

Plugin::Metadata::Metadata(const QString & binary, const QVariantMap & metadata):
	m_data(SanitizeMedatada(binary, metadata))
{
}

const QVariantMap & Plugin::Metadata::data() const
{
	return m_data;
}

int Plugin::Metadata::major() const
{
	return m_data.value("major").toInt();
}

int Plugin::Metadata::minor() const
{
	return m_data.value("minor").toInt();
}

int Plugin::Metadata::micro() const
{
	return m_data.value("micro").toInt();
}

Plugin::Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, bool implicitLoad, QObject * parent):
	QObject(parent),
	m(new Members{binary, std::move(loader), implicitLoad, BinaryMetadata(binary)})
{
}

Plugin::Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, bool implicitLoad, const Metadata & metadata, QObject * parent):
	QObject(parent),
	m(new Members{binary, std::move(loader), implicitLoad, metadata})
{
}

Plugin::~Plugin()
{
	if (!m->implicitLoad) {
		if (m->loader->unload())
			CUTEHMI_LOG_DEBUG("Unloaded plugin '" << binary() << "'.");
		else
			CUTEHMI_LOG_WARNING("Could not unload plugin '" << binary() << "'.");
	}
}

const QString & Plugin::binary() const
{
	return m->binary;
}

bool Plugin::implicitLoad() const
{
	return m->implicitLoad;
}

const QVariantMap & Plugin::metadata() const
{
	return m->metadata.data();
}

const QPluginLoader & Plugin::loader() const
{
	return *m->loader;
}

QObject * Plugin::instance()
{
	return m->loader->instance();
}

QString Plugin::name() const
{
	return m->metadata.data().value("name").toString();
}

QString Plugin::friendlyName() const
{
	return m->metadata.data().value("friendlyName").toString();
}

QString Plugin::version() const
{
	return QString::number(m->metadata.major()) + '.', QString::number(m->metadata.minor()) + '.' + QString::number(m->metadata.micro());
}

QString Plugin::fileName() const
{
	return m->loader->fileName();
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
