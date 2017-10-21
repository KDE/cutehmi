#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include <QObject>

namespace cutehmi {
namespace lockscreen {

class InternalSettings : public QObject
{
		Q_OBJECT
	public:
		explicit InternalSettings(QObject *parent = nullptr);

		Q_PROPERTY(bool activated READ getActivated WRITE setActivated NOTIFY activatedChanged)

		Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout NOTIFY timeoutChanged)

		void setActivated(const bool & activated);

		void setTimeout(const int & timeout);

		bool getActivated() const;

		int getTimeout() const;

	signals:
		void activatedChanged(const bool & newActivated);

		void timeoutChanged(const int & newTimeout);

	public slots:

	private:

		QSettings * m_settings;
};

}
}

#endif // SETTINGS_HPP
