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
		QCommandLineOption project;
	} * opt;
};

}
}

#endif
