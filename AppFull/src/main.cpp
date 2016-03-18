#include "MainWindow.hpp"
#include "MessageHandler.hpp"

#include <QApplication>
#include <QTranslator>

#include <memory>

void qtMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
{
	cutehmi::MessageHandler::Instance().qtMessageHandler(type, context, msg);
}

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationDomain("ekterm.pl");
	QCoreApplication::setApplicationName("CuteHMI");

	qInstallMessageHandler(qtMessageHandler);

	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/img/icon.png"));

//	QTranslator translator;
//	translator.load(":/locale/appfull_pl");
//	app.installTranslator(& translator);

	std::unique_ptr<cutehmi::MainWindow> win(new cutehmi::MainWindow);

	return app.exec();
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
