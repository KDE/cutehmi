#include "DevicePoint.hpp"
#include "DeviceCommunicationDispatcher.hpp"

#include <QVariant>

DevicePoint::DevicePoint(QObject * parent):
	QObject(parent)
{
//	setProperty("test", 3);
//	qDebug("%d", property("test").toInt());
	DeviceCommunicationDispatcher::Instance().registerPoint(this);
}

DevicePoint::~DevicePoint()
{
	DeviceCommunicationDispatcher::Instance().deregisterPoint(this);
}

void DevicePoint::setSource(const QString & source)
{
	if (source != m_source) {
		m_source = source;
		emit sourceChanged();
	}
}

QString DevicePoint::source() const
{
	return m_source;
}

void DevicePoint::setValue(double value)
{
	qDebug("DevicePoint::setValue(double)");
	if (value != m_value) {
		m_value = value;
		emit valueChanged();
	}
}

double DevicePoint::value() const
{
	qDebug("DevicePoint::value()");
	return m_value;
}
