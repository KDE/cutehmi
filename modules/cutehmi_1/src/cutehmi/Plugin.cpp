#include "../../include/cutehmi/Plugin.hpp"

namespace cutehmi {

QVariantMap Plugin::Metadata::SanitizeMedatada(const QString & binaryd, const QVariantMap & metadata)
{
	QVariantMap sanitized(metadata);

	if (!sanitized.contains("name")) {
		QString fallback(binaryd);
#ifdef CUTEHMI_DEBUG
		fallback.chop(1);
#endif
		CUTEHMI_LOG_WARNING("Using '" << fallback << "' as a fallback for missing 'name' property in '" << binaryd << "' metadata.");
		sanitized.insert("name", fallback);
	}
	if (!sanitized.contains("version")) {
		QString fallback("0.-1");	// Micro version is ignored, so use '-1' to indicate that this is a fallback value.
		CUTEHMI_LOG_WARNING("Using '" << fallback << "' as a fallback for missing 'version' property in '" << binaryd << "' metadata.");
		sanitized.insert("version", fallback);
	}

//	QStringList unavailableMetaData;
//	if (!unavailableMetaData.isEmpty())
//		CUTEHMI_LOG_WARNING("Plugin '" << binaryd <<"' is missing '" << unavailableMetaData.join("', '") << "' metadata information.");

	return sanitized;
}

Plugin::Metadata::Metadata(const QString & binaryd, const QVariantMap & metadata):
	m_data(SanitizeMedatada(binaryd, metadata))
{
}

const QVariantMap & Plugin::Metadata::data() const
{
	return m_data;
}

int Plugin::Metadata::minor() const
{
	return m_data.value("version").toString().split('.').value(0).toInt();
}

int Plugin::Metadata::micro() const
{
	return m_data.value("version").toString().split('.').value(1).toInt();
}

Plugin::Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, const Metadata & metadata, QObject * parent):
	QObject(parent),
	m(new Members{binary, std::move(loader), metadata})
{
}

Plugin::~Plugin()
{
	if (m->loader->unload())
		CUTEHMI_LOG_DEBUG("Unloaded plugin '" << binary() << "'.");
	else
		CUTEHMI_LOG_WARNING("Could not unload plugin '" << binary() << "'.");
}

const QString & Plugin::binary() const
{
	return m->binary;
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
	return m->metadata.data().value("version").toString();
}

QString Plugin::fileName() const
{
	return m->loader->fileName();
}

int Plugin::minor() const
{
	return m->metadata.minor();
}

int Plugin::micro() const
{
	return m->metadata.micro();
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
