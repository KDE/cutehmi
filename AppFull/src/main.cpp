#include "MainWindow.hpp"
#include "MessageHandler.hpp"

#include <QApplication>
#include <QTranslator>

#include <memory>

void qtMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
{
	MessageHandler::Instance().qtMessageHandler(type, context, msg);
}

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationDomain("ekterm.pl");
	QCoreApplication::setApplicationName("CuteHMI");

	qInstallMessageHandler(qtMessageHandler);

	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/img/icon.png"));

//	QTranslator translator;
//	translator.load(":/locale/cutyhmi_pl");
//	app.installTranslator(& translator);

	std::unique_ptr<MainWindow> win(new MainWindow);

	return app.exec();
}
