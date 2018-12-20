#ifndef COREDATA_HPP
#define COREDATA_HPP

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

#endif // COREDATA_HPP
