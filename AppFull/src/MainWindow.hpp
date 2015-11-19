#ifndef CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP
#define CUTEHMI_APPFULL_SRC_MAINWINDOW_HPP

#include "../uic/ui_MainWindow.h"

#include <utils/DestructorTest.hpp>

#include <QMainWindow>

class QQmlEngine;
class QQmlContext;
class QQuickWidget;

class MainWindow : public QMainWindow
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

		/**
		 * Show about dialog.
		 */
		void about();

		/**
		 * Show about Qt dialog.
		 */
		void aboutQt();

	private:
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

		typedef QuickWidgetWrapper QMLWidgetWrapper;
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
