#ifndef CUTEHMI_APPFULL_SRC_DEVICEPOINT_HPP
#define CUTEHMI_APPFULL_SRC_DEVICEPOINT_HPP

#include <QObject>

class DevicePoint : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
	Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

	public:
		explicit DevicePoint(QObject * parent = 0);

		virtual ~DevicePoint();

		void setSource(const QString & source);

		QString source() const;

		void setValue(double value);

		double value() const;

	signals:
		void sourceChanged();
		void valueChanged();

	public slots: 

	private:
		QString m_source;
		double m_value;
};

#endif
