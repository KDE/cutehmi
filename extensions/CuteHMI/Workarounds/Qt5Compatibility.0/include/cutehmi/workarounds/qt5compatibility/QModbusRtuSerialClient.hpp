#ifndef QMODBUSRTUSERIALCLIENT_HPP
#define QMODBUSRTUSERIALCLIENT_HPP

//<CuteHMI.Workarounds.Qt5Compatibility-2.workaround target="Qt" cause="Qt5">

#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QModbusRtuSerialClient>
#else
#include <QModbusRtuSerialMaster>
#endif

namespace cutehmi {
namespace workarounds {
namespace qt5compatibility {

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
typedef ::QModbusRtuSerialMaster QModbusRtuSerialClient;
#else
typedef ::QModbusRtuSerialClient QModbusRtuSerialClient;
#endif

}
}
}

//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#endif // QMODBUSRTUSERIALCLIENT_HPP
