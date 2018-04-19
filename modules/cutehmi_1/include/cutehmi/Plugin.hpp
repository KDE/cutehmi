#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PLUGIN_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PLUGIN_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QVariantMap>
#include <QPluginLoader>

#include <memory>

namespace cutehmi {

class CUTEHMI_API Plugin:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QString binary READ binary CONSTANT)
		Q_PROPERTY(QString fileName READ fileName CONSTANT)
		Q_PROPERTY(QVariantMap metadata READ metadata CONSTANT)

		class Metadata
		{
			public:
				/**
				 * Sanitize metadata. Checks if all required metadata is present. Provide fallbacks
				 * if required metadata is missing.
				 * @param binaryd binary name. This can be used as a fallback, if metadata does not
				 * contain 'name' property. Function expects binary name to contain 'd' suffix
				 * in debug mode, so in debug mode last character of the string will be chopped.
				 * @param metadata metadata to sanitize.
				 * @return sanitized metadata.
				 */
				static QVariantMap SanitizeMedatada(const QString & binaryd, const QVariantMap & metadata);

				Metadata(const QString & binaryd, const QVariantMap & metadata);

				const QVariantMap & data() const;

				int minor() const;

				int micro() const;

			private:
				QVariantMap m_data;
		};

		Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, const Metadata & metadata, QObject * parent = 0);

		~Plugin() override;

		const QString & binary() const;

		QString fileName() const;

		const QVariantMap & metadata() const;

		const QPluginLoader & loader() const;

		QObject * instance();

		QString name() const;

		QString friendlyName() const;

		QString version() const;

		int minor() const;

		int micro() const;

	private:
		struct Members
		{
			QString binary;
			std::unique_ptr<QPluginLoader> loader;
			Metadata metadata;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
