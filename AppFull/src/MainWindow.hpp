#ifndef CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP
#define CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP

#include "../uic/ui_MainWindow.h"

#include <QMainWindow>

#include <debug/DestructorTest.hpp>

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

	private:
		/**
		 * QQuickWidget wrapper. Provides QQuickWidget based rendering for QML.
		 */
		class QuickWidgetWrapper
		{
			public:
				QuickWidgetWrapper(QWidget * parent);

				QWidget * widget();

				QQmlContext * rootContext() const;

				void setSource(const QUrl & url);

			private:
				QQmlEngine * m_qmlEngine;
				QQuickWidget * m_quickWidget;
		};

		/**
		 * QQuickView wrapper. Provides QQuickView based rendering for QML.
		 */
		class QuickViewWrapper
		{
			public:
				QuickViewWrapper(QWidget * parent);

				QWidget * widget();

				QQmlContext * rootContext() const;

				void setSource(const QUrl & url);

			private:
				QQmlEngine * m_qmlEngine;
				QQuickView * m_quickView;
				QWidget * m_widget;
		};

		typedef QuickViewWrapper QMLWidgetWrapper;	///< QML widget wrapper. Either QuickViewWrapper or QuickWidgetWrapper can be used.
		typedef QList<QDockWidget *> PLCDockWidgetsContainer;

		void attachPLCClients();

		QDockWidget * createDockWidget(const QString & title, QWidget * widget);

		void storeSettings() const;

		void restoreSettings();

		Ui::MainWindow ui;
		QMLWidgetWrapper m_qmlWidgetWrapper;
		PLCDockWidgetsContainer m_plcDockWidgets;
};


#endif
