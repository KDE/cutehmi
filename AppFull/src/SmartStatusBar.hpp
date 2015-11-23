#ifndef CUTEHMI_APPFULL_SRC_SMARTSTATUSBAR_HPP
#define CUTEHMI_APPFULL_SRC_SMARTSTATUSBAR_HPP

#include <QStatusBar>

class SmartStatusBar:
	public QStatusBar
{
	public:
		static const int INITIAL_TIMEOUT_PER_CHAR = 500;

		SmartStatusBar(QWidget * parent = 0);

		~SmartStatusBar() override = default;

		int timeoutPerChar() const;

		void setTimeoutPerChar(int timeout);

		void showIdleMessage();

	public slots:
		void showAutoMessage(const QString & message);

	private slots:
		void setIdleForEmpty(const QString & message);

	private:
		int m_timeoutPerChar;
};

#endif
