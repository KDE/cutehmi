#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_PLUGIN_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_PLUGIN_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QPluginLoader>

#include <memory>

namespace cutehmi {

/**
 * %Plugin.
 */
class CUTEHMI_API Plugin:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QString binary READ binary CONSTANT)
		Q_PROPERTY(QString fileName READ fileName CONSTANT)
		Q_PROPERTY(QString version READ version CONSTANT)
		Q_PROPERTY(QVariantMap metadata READ metadata CONSTANT)
		Q_PROPERTY(bool implicitLoad READ implicitLoad CONSTANT)

		class Metadata
		{
			public:
				/**
				 * Sanitize metadata. Checks if all required metadata is present. Provide fallbacks
				 * if required metadata is missing.
				 * @param binary binary name. This can be used as a fallback, if metadata does not
				 * contain 'name' property. Function expects binary name to contain 'd' suffix
				 * in debug mode, so in debug mode last character of the string will be chopped.
				 * @param metadata metadata to sanitize.
				 * @return sanitized metadata.
				 */
				static QVariantMap SanitizeMedatada(const QString & binary, const QVariantMap & metadata);

				Metadata(const QString & binary, const QVariantMap & metadata);

				const QVariantMap & data() const;

				/**
				 * Get major version number. This function is provided for convenience. It converts value of 'major' field accessible through data() function
				 * to @p int value.
				 * @return major version number.
				 */
				int major() const;

				/**
				 * Get minor version number. This function is provided for convenience. It converts value of 'minor' field accessible through data() function
				 * to @p int value.
				 * @return minor version number.
				 */
				int minor() const;

				/**
				 * Get micro version number. This function is provided for convenience. It converts value of 'micro' field accessible through data() function
				 * to @p int value.
				 * @return micro version number.
				 */
				int micro() const;

			private:
				QVariantMap m_data;
		};

		static QString NameToBinary(const QString & name);

		static QString NameFromBinary(const QString & binary);

		static Metadata BinaryMetadata(const QString & binary);

		static bool BinaryExists(const QString & binary);

		static int CheckReqMinors(int reqMinor, QList<Metadata> & metadataList);

		Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, bool implicitLoad, QObject * parent = nullptr);

		Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, bool implicitLoad, const Metadata & metadata, QObject * parent = nullptr);

		~Plugin() override;

		const QString & binary() const;

		QString fileName() const;

		bool implicitLoad() const;

		const QVariantMap & metadata() const;

		const QPluginLoader & loader() const;

		QObject * instance();

		QString name() const;

		QString friendlyName() const;

		QString version() const;

	private:
		struct Members
		{
			QString binary;
			std::unique_ptr<QPluginLoader> loader;
			bool implicitLoad;
			Metadata metadata;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
