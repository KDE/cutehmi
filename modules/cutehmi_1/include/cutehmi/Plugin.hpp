#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PLUGIN_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PLUGIN_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QPluginLoader>

#include <memory>

namespace cutehmi {

class CUTEHMI_API Plugin:
	public QObject
{
	Q_OBJECT

	public:
		struct MetaData
		{
			QString id;
			QString name;
			int minor;
			int micro;
		};

		Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, const cutehmi::Plugin::MetaData & metaData, QObject * parent = 0);

		~Plugin() override;

		const QString & binary() const;

		const QPluginLoader & loader() const;

		QObject * instance();

		const QString & id() const;

		const QString & name() const;

		int minor() const;

		int micro() const;

		QString version() const;

	private:
		struct Members
		{
			QString binary;
			std::unique_ptr<QPluginLoader> loader;
			MetaData metaData;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
