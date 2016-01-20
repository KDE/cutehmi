#include <base/PLCClientManager.hpp>	//this is on top to avoid "Please include winsock2.h befor windows.h" warning

#include "MainWindow.hpp"
#include "Settings.hpp"
#include "MessageHandler.hpp"
#include "version.hpp"
#include "PLCWidgetFactory.hpp"
#include "modbus/widgets/ClientControlWidget.hpp"

#include <base/ProjectModel.hpp>

#include <QMessageBox>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlProperty>
#include <QQuickWidget>
#include <QQuickView>
#include <QQmlEngine>
#include <QFileDialog>

constexpr const char * MainWindow::INITIAL_ICON_THEME;

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags),
	m_qmlWidgetWrapper(this),
	m_recentFiles(new RecentFiles("MainWindow/recentFiles", this)),
	m_recentFilesMenu(new QMenu(tr("&Recent files"), this)),
	m_projectModel(new base::ProjectModel(this))
{
	QIcon::setThemeSearchPaths(QIcon::themeSearchPaths() << "../icons");
	if (QIcon::themeName().isEmpty())
		QIcon::setThemeName(INITIAL_ICON_THEME);

	ui.setupUi(this);
	ui.centralFrameLayout->addWidget(m_qmlWidgetWrapper.widget());
	MessageHandler::Instance().setMessageArea(ui.messageArea);
	setWindowTitle(QCoreApplication::applicationName());

	// Need to set context properties before loading qml file and create dock widgets before restoreSettings().
	attachPLCClients();

	// Set up view menu.
	QMenu * menuView = createPopupMenu();
	menuView->setTitle(tr("&View"));
	QAction * actionViewMenu = ui.menuApplication->insertMenu(ui.actionExit, menuView);
	actionViewMenu->setStatusTip(tr("Show or hide tool bars and dock windows"));

	// Set up recent files.
	QAction * actionRecentFiles = ui.menuFile->insertMenu(ui.actionExit, m_recentFilesMenu);
	actionRecentFiles->setStatusTip(tr("Open recently used file"));
	ui.menuFile->insertSeparator(ui.actionExit);
	m_recentFiles->updateMenu(*m_recentFilesMenu);
	connect(m_recentFiles, SIGNAL(actionTriggered(const QString &)), this, SLOT(loadRecentFile(const QString &)));

	// Set up project view.
	m_projectModel->tmpSetup();
	ui.projectView->setModel(m_projectModel);

	//<workaround id="AppFull-1" target="Qt" cause="bug">
	// Some bug causes restoreState() to fail in some circustamces, if it's called before show() (Qt bug).
	// Need to put restoreSettings() after show().
	show();

	/// @bug [Qt bug] dock widgets are not properly restored if one of them is shrinked to the minimum and they are both docked at the bottom.
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
	if (ui.actionSave->isEnabled())
		if (!askSaveDialog()) {
			event->ignore();
		} else {
			storeSettings();
			event->accept();
		}
	else {
		storeSettings();
		event->accept();
	}
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

void MainWindow::enableSaveFile()
{
	ui.actionSave->setEnabled(true);
}

void MainWindow::newFile()
{
	qDebug("New");

	if (ui.actionSave->isEnabled())
		if (!askSaveDialog())
			return;
	resetFile();
	ui.actionSave->setEnabled(false);
}

bool MainWindow::saveFile()
{
	qDebug("Save");

	if (m_file.isFile()) {
		ui.actionSave->setDisabled(saveFile(m_file.filePath()));
	} else
		ui.actionSave->setDisabled(saveFileAs());
	return !ui.actionSave->isEnabled();
}

bool MainWindow::saveFileAs()
{
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save file as"), m_recentFiles->lastDir(), QCoreApplication::applicationName() + " " + tr("file (*.xml)"));
	if (filePath.isEmpty())
		return false;

	qDebug() << "Save as " << filePath;

	if (saveFile(filePath)) {
		m_file.setFile(filePath);
		setWindowTitle(m_file.fileName());
		ui.actionSave->setEnabled(false);
		return true;
	} else
		return false;
}

bool MainWindow::loadFile()
{
	if (ui.actionSave->isEnabled())
		if (!askSaveDialog())
			return false;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), m_recentFiles->lastDir(), QCoreApplication::applicationName() + " " + tr("file (*.xml)"));
	if (fileName.isEmpty())
		return false;

	qDebug() << "Load " << fileName;

	if (loadFile(fileName)) {
		m_file.setFile(fileName);
		setWindowTitle(m_file.fileName());
		ui.actionSave->setEnabled(false);
		return true;
	} else
		return false;
}

bool MainWindow::loadRecentFile(const QString & filePath)
{
	if (ui.actionSave->isEnabled())
		if (!askSaveDialog())
			return false;

	qDebug() << "Load recent " << filePath;

	if (loadFile(filePath)) {
		m_file.setFile(filePath);
		setWindowTitle(m_file.fileName());
		ui.actionSave->setEnabled(false);
		return true;
	} else
		return false;
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


bool MainWindow::saveFile(const QString & filePath)
{
	qWarning("saveFile() not implemented yet.");

	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly))
		return false;
//	QDataStream out(& file);
//	ui.fxView->save(out);
	file.close();
//	SmartStatusBar::ShowAutoMessage(tr("Saved file ") + filePath);
	m_recentFiles->put(filePath);
	m_recentFiles->updateMenu(*m_recentFilesMenu);
	return true;
}

bool MainWindow::loadFile(const QString & filePath)
{
	qWarning("loadFile() not implemented yet.");

	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly)) {
		if (!filePath.isEmpty()) {
			qWarning() << "Could not load file " << filePath;
			QMessageBox msgBox;
			msgBox.setText(tr("Could not open file."));
			if (!QFileInfo(filePath).exists())
				msgBox.setInformativeText(tr("File does not exist"));
			msgBox.setIcon(QMessageBox::Information);
			msgBox.exec();
		}
		m_recentFiles->remove(filePath);
		m_recentFiles->updateMenu(*m_recentFilesMenu);
		return false;
	}

	return false;	///< @todo remove this return and implement loading below.

//	QDataStream in(& file);
//	int ledFileVersion;
//	in >> ledFileVersion;

//	if (ui.fxView->loadable(ledFileVersion)) {
//		resetFile();
//		ui.fxView->load(in, ledFileVersion);
//		file.close();
//		SmartStatusBar::ShowAutoMessage(tr("Loaded file ") + filePath);
//		m_recentFiles->put(filePath);
//		m_recentFiles->updateMenu(m_recentFilesMenu);
//		return true;
//	}
}

void MainWindow::resetFile()
{
	qWarning("resetFile() not implemented yet.");

//	AbstractFx::ResetCloneCtr();
//	ui.fxView->removeAll(false);
//	m_file.setFile("");
//	setWindowTitle("");
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

bool MainWindow::askSaveDialog()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setText(tr("File has been modified."));
	msgBox.setInformativeText(tr("All unsaved data will be lost. Would you like to keep changes?"));
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	switch (msgBox.exec()) {
		case QMessageBox::Save:
			return saveFile();
		case QMessageBox::Discard:
			return true;
		case QMessageBox::Cancel:
		default:
			return false;
	}
}
