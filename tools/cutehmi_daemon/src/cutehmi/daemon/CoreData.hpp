#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_COREDATA_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_COREDATA_HPP

#include <QCoreApplication>
#include <QCommandLineParser>

namespace cutehmi {
namespace daemon {

struct CoreData
{
	QCoreApplication * app;
	QCommandLineParser * cmd;

	struct Options
	{
		QCommandLineOption app;
		QCommandLineOption basedir;
		QCommandLineOption lang;
		QCommandLineOption pidfile;
		QCommandLineOption project;
	} * opt;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
