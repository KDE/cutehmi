#ifndef CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP
#define CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP

#include "../uic/ui_MainWindow.h"
#include "RecentFiles.hpp"

#include <widgets/QuickViewWrapper.hpp>

#include <base/ProjectModel.hpp>
#include <base/XMLProjectBackend.hpp>
#include <base/PluginLoader.hpp>
#include <base/Services.hpp>

#include <QMainWindow>
#include <QFileInfo>

namespace cutehmi {

class MainWindow:
	public QMainWindow
{
	Q_OBJECT
	typedef QMainWindow Parent;

	public:
		static constexpr const char * INITIAL_ICON_THEME = "oxygen";
		static constexpr const char * PLUGINS_SUBDIR = "plugins";

		MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);

		virtual ~MainWindow();

		void closeEvent(QCloseEvent * event) override;

	private slots:
		void activateVisualComponent(const QModelIndex & index);

		/**
		 * Show about dialog.
		 */
		void about();

		/**
		 * Show about Qt dialog.
		 */
		void aboutQt();

		/**
		 * Enable file save action.
		 *
		 * @todo check if it can be replaced with some QAction slot.
		 */
		void enableSaveFile();

		/**
		 * New file.
		 */
		void newFile();

		/**
		 * Save file.
		 * @return
		 */
		bool saveFile();

		/**
		 * Bring file dialog and save file if requested.
		 */
		bool saveFileAs();

		/**
		 * Bring file dialog and load file if requested.
		 */
		bool loadFile();

		bool loadRecentFile(const QString & filePath);

	private:
		typedef widgets::QuickViewWrapper QMLWidgetWrapper;	///< QML widget wrapper. Either QuickViewWrapper or QuickWidgetWrapper can be used.

		bool saveFile(const QString & filePath);

		bool loadFile(const QString & filePath);

		void resetModel(base::ProjectModel * newModel);

		void attachUIPlugins(base::ProjectModel & model);

		void visitProjectContext(base::ProjectModel & model);

		void visitServices(base::ProjectModel & model);

		void storeSettings() const;

		void restoreSettings();

		bool askSaveDialog();

		void makeWindowTitle();

		Ui::MainWindow ui;
		base::PluginLoader m_projectPluginLoader;
		QMLWidgetWrapper m_qmlWidgetWrapper;
		QFileInfo m_file;
		RecentFiles * m_recentFiles;
		QMenu * m_recentFilesMenu;
		base::ProjectModel * m_projectModel;
		base::Services m_services;
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
