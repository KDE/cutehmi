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

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags),
	m_qmlWidgetWrapper(this)
{
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

	show();

	// Some bug causes restoreState() to fail in some circustamces, if it's called before show().
	restoreSettings();

	m_qmlWidgetWrapper.setSource(QUrl(QStringLiteral("qrc:/qml/MainForm.ui.qml")));
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
			tr("%1 version %2").arg(QCoreApplication::applicationName()).arg(CUTYHMI_VERSION) + "\n\n"
			+ tr("Visualization software.") + "\n"
			// %1 copyright symbol, %2 copyright year.
			+ tr("Copyright %1 %2, EKTERM. All rights reserved.").arg("\u00A9").arg(CUTYHMI_COPYRIGHT_YEAR));
}

void MainWindow::aboutQt()
{
	QApplication::aboutQt();
}

MainWindow::QuickWidgetWrapper::QuickWidgetWrapper(QWidget * parent):
	m_qmlEngine(new QQmlEngine),
	m_quickWidget(new QQuickWidget(m_qmlEngine, parent)) // Note: QQuickWidget won't take ownership of m_qmlEngine.
{
	m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
	m_qmlEngine->addImportPath("qrc:/qml");
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
	m_quickWidget->setSource(url);
}

MainWindow::QuickViewWrapper::QuickViewWrapper(QWidget * parent):
	m_qmlEngine(new QQmlEngine),
	m_quickView(new QQuickView(m_qmlEngine, 0)) // Note: QQuickView won't take ownership of m_qmlEngine.
{
	m_quickView->setResizeMode(QQuickView::SizeRootObjectToView);
	m_qmlEngine->addImportPath("qrc:/qml");
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
	m_quickView->setSource(url);
}

void MainWindow::attachPLCClients()
{
	QString clientId = "mb";

	modbus::Client & modbusClient = base::PLCClientManager::Instance().m_modbusClient;
	connect(& modbusClient, & modbus::Client::error, this, & MainWindow::showErrorDialog);
	// QSignalMapper may be helpful with more clients to send client id for more verbose info.
	connect(& modbusClient, & modbus::Client::connected, this, & MainWindow::clientConnected);
	connect(& modbusClient, & modbus::Client::disconnected, this, & MainWindow::clientDisconnected);

//	modbusClient.connect();
	m_qmlWidgetWrapper.rootContext()->setContextProperty(clientId, & modbusClient);
	QDockWidget * clientControlDockWidget = createDockWidget(QString("Modbus - ") + clientId, PLCWidgetFactory::Instance().createClientControlWidget(& modbusClient));
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
