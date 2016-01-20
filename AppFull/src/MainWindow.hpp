#ifndef CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP
#define CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP

#include "../uic/ui_MainWindow.h"
#include "RecentFiles.hpp"

#include <base/ProjectModel.hpp>

#include <QMainWindow>
#include <QFileInfo>

class QQmlEngine;
class QQmlContext;
class QQuickWidget;
class QQuickView;

class MainWindow:
	public QMainWindow
{
	Q_OBJECT
	typedef QMainWindow Parent;

	public:
		static constexpr const char * INITIAL_ICON_THEME = "oxygen";

		MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);

		virtual ~MainWindow();

		void closeEvent(QCloseEvent * event) override;

	private slots:
		/**
		 * Show error dialog.
		 * @param msg brief error message.
		 * @param details detailed information.
		 */
		void showErrorDialog(const QString & msg, const QString & details = QString()) const;

		void clientConnected();

		void clientDisconnected();

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
		class IQMLWidgetWrapper
		{
			public:
				virtual QWidget * widget() = 0;

				virtual QQmlContext * rootContext() const = 0;

				virtual void setSource(const QUrl & url) = 0;

				virtual QStringList importPathList() const = 0;

				virtual void addImportPath(const QString & dir) = 0;

			protected:
				~IQMLWidgetWrapper();
		};

		/**
		 * QQuickWidget wrapper. Provides QQuickWidget based rendering for QML.
		 */
		class QuickWidgetWrapper:
			public virtual IQMLWidgetWrapper
		{
			public:
				QuickWidgetWrapper(QWidget * parent);

				QWidget * widget() override;

				QQmlContext * rootContext() const override;

				void setSource(const QUrl & url) override;

				QStringList importPathList() const override;

				void addImportPath(const QString & dir) override;

			private:
				QQmlEngine * m_qmlEngine;
				QQuickWidget * m_quickWidget;
		};

		/**
		 * QQuickView wrapper. Provides QQuickView based rendering for QML.
		 */
		class QuickViewWrapper:
			public virtual IQMLWidgetWrapper
		{
			public:
				QuickViewWrapper(QWidget * parent);

				QWidget * widget() override;

				QQmlContext * rootContext() const override;

				void setSource(const QUrl & url) override;

				QStringList importPathList() const override;

				void addImportPath(const QString & dir) override;

			private:
				QQmlEngine * m_qmlEngine;
				QQuickView * m_quickView;
				QWidget * m_widget;
		};

		typedef QuickViewWrapper QMLWidgetWrapper;	///< QML widget wrapper. Either QuickViewWrapper or QuickWidgetWrapper can be used.
		typedef QList<QDockWidget *> PLCDockWidgetsContainer;

		void attachPLCClients();

		QDockWidget * createDockWidget(const QString & title, QWidget * widget);

		bool saveFile(const QString & filePath);

		bool loadFile(const QString & filePath);

		void resetFile();

		void storeSettings() const;

		void restoreSettings();

		bool askSaveDialog();

		Ui::MainWindow ui;
		QMLWidgetWrapper m_qmlWidgetWrapper;
		PLCDockWidgetsContainer m_plcDockWidgets;
		QFileInfo m_file;
		RecentFiles * m_recentFiles;
		QMenu * m_recentFilesMenu;
		base::ProjectModel * m_projectModel;
};


#endif
