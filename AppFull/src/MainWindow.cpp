#include "MainWindow.hpp"
#include "Settings.hpp"
#include "MessageHandler.hpp"
#include "version.hpp"

#include <base/ProjectModel.hpp>
#include <widgets/IUIPlugin.hpp>
#include <widgets/UIVisitorDelegate.hpp>
#include <widgets/ErrorBox.hpp>

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QCloseEvent>

namespace cutehmi {

constexpr const char * MainWindow::INITIAL_ICON_THEME;
constexpr const char * MainWindow::PLUGINS_SUBDIR;

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
	makeWindowTitle();
/// @todo remove line below if model saving is implemented.
	ui.actionSaveAs->setEnabled(false);	// Temp until saving model is done.

	// Set up control buttons.
	connect(ui.actionStart, & QAction::triggered, & m_runners, & base::RunnersRegister::start);
	connect(ui.actionStop, & QAction::triggered, & m_runners, & base::RunnersRegister::stop);

	// Set up plugins.
	QDir dir(qApp->applicationDirPath());
	dir.cd(PLUGINS_SUBDIR);
	m_projectPluginLoader.setPluginsDir(dir.canonicalPath());
	qDebug() << "Library paths: " << QCoreApplication::libraryPaths();

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
	ui.projectView->setHeaderHidden(true);
	ui.projectView->setModel(m_projectModel);
	connect(ui.projectView, & QTreeView::activated, this, & MainWindow::activateVisualComponent);

	//<workaround id="AppFull-1" target="Qt" cause="bug">
	// Some bug causes restoreState() to fail in some circustamces, if it's called before show() (Qt bug).
	// Need to put restoreSettings() after show().
	show();

	//<unsolved id="AppFull-7" target="Qt" cause="bug">
	// Dock widgets are not properly restored if one of them is shrinked to the minimum and they are both docked at the bottom.
	restoreSettings();
	//</unsolved>
	//</workaround>

	qDebug() << "Icon theme search paths: " << QIcon::themeSearchPaths();
	qDebug() << "Icon theme name: " << QIcon::themeName();

	m_qmlWidgetWrapper.addImportPath("../CuteHMI/QML");
	m_qmlWidgetWrapper.addImportPath("../QML");
	qDebug() << "QML import paths: " << m_qmlWidgetWrapper.importPathList();
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
			m_runners.stop();
			storeSettings();
			event->accept();
		}
	else {
		m_runners.stop();
		storeSettings();
		event->accept();
	}
}

void MainWindow::activateVisualComponent(const QModelIndex & index)
{
	if (!m_qmlWidgetWrapper.protoVisualComponent()->isNull())
		return;
	base::ProjectModel::Node::VisitorDelegate::QMLVisualComponentProxy proxy(m_qmlWidgetWrapper.protoVisualComponent());
	static_cast<base::ProjectModel::Node *>(index.internalPointer())->visitorDelegate()->visit(proxy);
	if (m_qmlWidgetWrapper.protoVisualComponent()->isLoading())
		connect(m_qmlWidgetWrapper.protoVisualComponent(), & QQmlComponent::statusChanged, & m_qmlWidgetWrapper, & QMLWidgetWrapper::showVisualComponent);
	else
		m_qmlWidgetWrapper.showVisualComponent();
}

void MainWindow::about()
{
	// %1 application name.
	QMessageBox::about(this, tr("About %1").arg(QCoreApplication::applicationName()),
			// %1 application_name, %2 version number.
			tr("<b>%1</b> version %2").arg(QCoreApplication::applicationName()).arg(CUTEHMI_APPFULL_VERSION)
			+ tr("<a href=\"http://libmodbus.org/\">libmodbus</a> - a Modbus library for Linux, Mac OS X, FreeBSD, QNX and Win32.") + "<br />"
			+ tr("Free use of this software is granted under the terms of the GNU Lesser General Public License (LGPL v2.1+)") + "<br />"
			+ tr("For details see the file COPYING.LESSER included with the libmodbus distribution.") + "<br />"
			// %1 copyright symbol
			+ tr("Copyright %1 2015, Stéphane Raimbault.").arg("\u00A9")
			+ "<hr />"

			+ tr("Material design icons are the official <a href=\"https://design.google.com/icons/\">icon set</a> from Google.") + "<br />"
			+ tr("Material design icons are distributed under the terms of:") + "<br />"
			+ "<a href=\"https://creativecommons.org/licenses/by/4.0/\">Creative Common Attribution 4.0 International License (CC-BY 4.0)</a>." + "<br />"
			// %1 copyright symbol
			+ tr("Copyright %1 2016, Google.").arg("\u00A9")
			+ "<hr />"

			+ tr("Visualization software.") + "<br />"
			// %1 copyright symbol, %2 copyright year.
			+ tr("Copyright %1 %2, EKTERM. All rights reserved.").arg("\u00A9").arg(CUTEHMI_APPFULL_COPYRIGHT_YEAR));
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
	resetModel(new base::ProjectModel(this));
	m_file.setFile("");
	makeWindowTitle();
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
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save file as"), m_recentFiles->lastDir(), QCoreApplication::applicationName() + " " + tr("project (*.xml)"));
	if (filePath.isEmpty())
		return false;

	qDebug() << "Save as " << filePath;

	if (saveFile(filePath)) {
		m_file.setFile(filePath);
		makeWindowTitle();
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), m_recentFiles->lastDir(), QCoreApplication::applicationName() + " " + tr("project (*.xml)"));
	if (fileName.isEmpty())
		return false;

	qDebug() << "Load " << fileName;

	if (loadFile(fileName)) {
		m_file.setFile(fileName);
		makeWindowTitle();
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
		makeWindowTitle();
		ui.actionSave->setEnabled(false);
		return true;
	} else
		return false;
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
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly)) {
		base::ProjectModel * newModel = new base::ProjectModel(this);
		{
			base::XMLProjectBackend xmlBackend(newModel, & m_projectPluginLoader);
			widgets::ErrorBox errorBox(tr("Could not load file %1.").arg(filePath));
			if (errorBox.exec(xmlBackend.load(file))) {
				file.close();
				resetModel(newModel);
				qDebug() << "Loaded project file " << filePath << ".";
				m_recentFiles->put(filePath);
				m_recentFiles->updateMenu(*m_recentFilesMenu);
				return true;	// Won't reach delete newModel line.
			}
		}
		delete newModel;	// This line won't be reached if xmlBackend.load() succeeds.
		file.close();
	} else if (!filePath.isEmpty()) {
		qWarning() << "Could not open file " << filePath;
// @todo use custom MessageBox or ExtMessageBox.
		QMessageBox msgBox;
		msgBox.setText(tr("Could not open file."));
		if (!QFileInfo(filePath).exists())
			msgBox.setInformativeText(tr("File does not exist"));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
	qDebug() << "Failed to load project file " << filePath << ".";
	m_recentFiles->remove(filePath);
	m_recentFiles->updateMenu(*m_recentFilesMenu);
	return false;
}

void MainWindow::resetModel(base::ProjectModel * newModel)
{
	// Reset runners register.
	m_runners.clear();

	// Reset QML view.
	m_qmlWidgetWrapper.resetVisualComponent();

	// Set new model and delete old selection model as docs suggest.
	QItemSelectionModel * oldSelectionModel = ui.projectView->selectionModel();
	ui.projectView->setModel(newModel);
	if (oldSelectionModel)
		oldSelectionModel->deleteLater();
	if (m_projectModel)
		m_projectModel->deleteLater();
	m_projectModel = newModel;
	if (m_projectModel) {
		visitRunnersRegister(*m_projectModel);
		visitProjectContext(*m_projectModel);
		attachUIPlugins(*m_projectModel);
	}
}

void MainWindow::attachUIPlugins(base::ProjectModel & model)
{
	QStringList plugins = m_projectPluginLoader.loadedPlugins();
	QString uiPluginName;
	QString uiPluginVersion;

	// Load UI plugins and let them visit all nodes. In the first pass they will make an attempt to recognize
	// internal data objects. If succesful they will set up visitors for the relevant nodes.
	for (QString plugin : plugins)
		if (m_projectPluginLoader.uiPlugin(plugin, uiPluginName, uiPluginVersion)) {
			base::PluginLoader::Error err;
			if ((err = m_projectPluginLoader.loadPlugin(uiPluginName, uiPluginVersion)) == base::PluginLoader::Error::OK) {
				widgets::IUIPlugin * uiPlugin;
				if ((uiPlugin = qobject_cast<widgets::IUIPlugin *>(m_projectPluginLoader.instance(uiPluginName))) != 0) {
					uiPlugin->setParentWidget(this);
					for (auto it = model.begin(); it != model.end(); ++it)
						uiPlugin->visit(*it);
				} else
					qWarning() << "UI plugin does not implement required interface";
			} else {
				qWarning() << "Could not load UI plugin " << uiPluginName << " version: " << uiPluginVersion;
				qWarning() << err.str();
			}
		}
}

void MainWindow::visitProjectContext(base::ProjectModel & model)
{
	m_qmlWidgetWrapper.renewProjectContext();
	base::ProjectModel::Node::VisitorDelegate::QMLContextPropertyProxy proxy(m_qmlWidgetWrapper.projectContext());
	for (auto it = model.begin(); it != model.end(); ++it)
		it->visitorDelegate()->visit(proxy);
}

void MainWindow::visitRunnersRegister(base::ProjectModel & model)
{
	base::ProjectModel::Node::VisitorDelegate::RunnersRegisterProxy proxy(& m_runners);
	for (auto it = model.begin(); it != model.end(); ++it)
		it->visitorDelegate()->visit(proxy);
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

void MainWindow::makeWindowTitle()
{
	QString title = QCoreApplication::applicationName();
	if (!m_file.fileName().isEmpty())
		title += QString(" - ") + m_file.fileName();
	setWindowTitle(title);
}

}
