#include <base/PLCClientManager.hpp>	//this is on top to avoid "Please include winsock2.h befor windows.h" warning

#include "MainWindow.hpp"
#include "Settings.hpp"
#include "MessageHandler.hpp"
#include "version.hpp"
#include "PLCWidgetFactory.hpp"
#include "modbus/widgets/ClientControlWidget.hpp"

#include <QMessageBox>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlProperty>
#include <QQuickWidget>
#include <QQuickView>
#include <QQmlEngine>

constexpr const char * MainWindow::INITIAL_ICON_THEME;

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags),
	m_qmlWidgetWrapper(this)
{
	QIcon::setThemeSearchPaths(QIcon::themeSearchPaths() << "../icons");
	if (QIcon::themeName().isEmpty())
		QIcon::setThemeName(INITIAL_ICON_THEME);

	ui.setupUi(this);
	ui.centralLayout->addWidget(m_qmlWidgetWrapper.widget());
	MessageHandler::Instance().setMessageArea(ui.messageArea);
	setWindowTitle(QCoreApplication::applicationName());

	// Need to set context properties before loading qml file and create dock widgets before restoreSettings().
	attachPLCClients();

	QMenu * viewMenu = createPopupMenu();
	viewMenu->setTitle(tr("&View"));
	QAction * viewMenuAct = ui.menuApplication->insertMenu(ui.actionExit, viewMenu);
	viewMenuAct->setStatusTip(tr("Show or hide tool bars and dock windows"));

	//<workaround id="AppFull-1" target="Qt">
	show();

	/// @bug Qt bug - restoreState() fails in some circustamces, if it's called before show().
	/// @bug Qt bug - dock widgets are not properly restored if one of them is shrinked to the minimum and they are both docked at the bottom.
	restoreSettings();
	//</workaround>

	qDebug() << "Icon theme search paths: " << QIcon::themeSearchPaths();
	qDebug() << "Icon theme name: " << QIcon::themeName();

	m_qmlWidgetWrapper.addImportPath("../CuteHMI/QML");
	m_qmlWidgetWrapper.addImportPath("../QML");
	qDebug() << "QML import paths: " << m_qmlWidgetWrapper.importPathList();
	m_qmlWidgetWrapper.setSource(QUrl(QStringLiteral("../QML/Screens/Test/Main.ui.qml")));
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent * event)
{
//	if (ui.saveAct->isEnabled())
//		if (!askSaveDialog()) {
//			event->ignore();
//		} else {
//			storeSettings();
//			event->accept();
//		}
//	else {
		storeSettings();
		event->accept();
//	}
}

void MainWindow::showErrorDialog(const QString & msg, const QString & details) const
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setText(msg);
	if (!details.isEmpty())
		msgBox.setDetailedText(details);
	msgBox.exec();
}

void MainWindow::clientConnected()
{
	qInfo("Connected");
}

void MainWindow::clientDisconnected()
{
	qInfo("Disconnected");
}

void MainWindow::about()
{
	// %1 application name.
	QMessageBox::about(this, tr("About %1").arg(QCoreApplication::applicationName()),
			// %1 application_name, %2 version number.
			tr("<b>%1</b> version %2").arg(QCoreApplication::applicationName()).arg(CUTYHMI_VERSION)
			+ "<hr />"

			+ tr("Material design icons are the official <a href=\"https://design.google.com/icons/\">icon set</a> from Google.") + "<br />"
			// %1 copyright symbol
			+ tr("Material design icons are distributed under the terms of:") + "<br />"
			+ "<a href=\"https://creativecommons.org/licenses/by/4.0/\">Creative Common Attribution 4.0 International License (CC-BY 4.0)</a>." + "<br />"
			+ tr("Copyright %1 2016, Google.").arg("\u00A9")
			+ "<hr />"

			+ tr("Visualization software.") + "<br />"
			// %1 copyright symbol, %2 copyright year.
			+ tr("Copyright %1 %2, EKTERM. All rights reserved.").arg("\u00A9").arg(CUTYHMI_COPYRIGHT_YEAR));
}

void MainWindow::aboutQt()
{
	QApplication::aboutQt();
}

MainWindow::IQMLWidgetWrapper::~IQMLWidgetWrapper()
{
}

MainWindow::QuickWidgetWrapper::QuickWidgetWrapper(QWidget * parent):
	m_qmlEngine(new QQmlEngine),
	m_quickWidget(new QQuickWidget(m_qmlEngine, parent)) // Note: QQuickWidget won't take ownership of m_qmlEngine.
{
	m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
	m_qmlEngine->setParent(m_quickWidget);	// Reparent m_qmlEngine so that proper destruction order is quaranteed.
}

QWidget * MainWindow::QuickWidgetWrapper::widget()
{
	return m_quickWidget;
}

QQmlContext * MainWindow::QuickWidgetWrapper::rootContext() const
{
	return m_quickWidget->rootContext();
}

void MainWindow::QuickWidgetWrapper::setSource(const QUrl & url)
{
	qDebug() << "Loading QML file: " << url;
	m_quickWidget->setSource(url);
}

QStringList MainWindow::QuickWidgetWrapper::importPathList() const
{
	return m_qmlEngine->importPathList();
}

void MainWindow::QuickWidgetWrapper::addImportPath(const QString & dir)
{
	qDebug() << "Adding QML import path: " << dir;
	m_qmlEngine->addImportPath(dir);
}

MainWindow::QuickViewWrapper::QuickViewWrapper(QWidget * parent):
	m_qmlEngine(new QQmlEngine),
	m_quickView(new QQuickView(m_qmlEngine, 0)) // Note: QQuickView won't take ownership of m_qmlEngine.
{
	m_quickView->setResizeMode(QQuickView::SizeRootObjectToView);
	m_qmlEngine->setParent(m_quickView);	// Reparent m_qmlEngine so that proper destruction order is quaranteed.
	m_widget = QWidget::createWindowContainer(m_quickView, parent);	// Note: m_widget (window container) should take ownership of m_quickView.
}

QWidget * MainWindow::QuickViewWrapper::widget()
{
	return m_widget;
}

QQmlContext * MainWindow::QuickViewWrapper::rootContext() const
{
	return m_quickView->rootContext();
}

void MainWindow::QuickViewWrapper::setSource(const QUrl & url)
{
	qDebug() << "Loading QML file: " << url;
	m_quickView->setSource(url);
}

QStringList MainWindow::QuickViewWrapper::importPathList() const
{
	return m_qmlEngine->importPathList();
}

void MainWindow::QuickViewWrapper::addImportPath(const QString & dir)
{
	qDebug() << "Adding QML import path: " << dir;
	m_qmlEngine->addImportPath(dir);
}

void MainWindow::attachPLCClients()
{
	QString clientId = "mb";

	modbus::Client * modbusClient = base::PLCClientManager::Instance().m_modbusClient;
	connect(modbusClient, & modbus::Client::error, this, & MainWindow::showErrorDialog);
	// QSignalMapper may be helpful with more clients to send client id for more verbose info.
	connect(modbusClient, & modbus::Client::connected, this, & MainWindow::clientConnected);
	connect(modbusClient, & modbus::Client::disconnected, this, & MainWindow::clientDisconnected);

//	modbusClient.connect();
	m_qmlWidgetWrapper.rootContext()->setContextProperty(clientId, modbusClient);
	QDockWidget * clientControlDockWidget = createDockWidget(QString("Modbus - ") + clientId, PLCWidgetFactory::Instance().createClientControlWidget(modbusClient));
	// Object name must be set for the dock widget to make it work with storeSetting() and restoreSettings().
	clientControlDockWidget->setObjectName(clientId + QStringLiteral("_clientControlDockWidget"));
	addDockWidget(Qt::LeftDockWidgetArea, clientControlDockWidget);
}

QDockWidget * MainWindow::createDockWidget(const QString & title, QWidget * widget)
{
	QDockWidget * plcDockWidget = new QDockWidget(title, this);
	plcDockWidget->setWidget(widget);
	m_plcDockWidgets.append(plcDockWidget);
	return plcDockWidget;
}

void MainWindow::storeSettings() const
{
	Settings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();
}

void MainWindow::restoreSettings()
{
	Settings settings;
	settings.beginGroup("MainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
	settings.endGroup();
}
