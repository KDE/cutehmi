#ifndef QMODBUSRTUSERIALSERVER_HPP
#define QMODBUSRTUSERIALSERVER_HPP

//<CuteHMI.Workarounds.Qt5Compatibility-3.workaround target="Qt" cause="Qt5">

#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QModbusRtuSerialServer>
#else
#include <QModbusRtuSerialSlave>
#endif

namespace cutehmi {
namespace workarounds {
namespace qt5compatibility {

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
typedef ::QModbusRtuSerialSlave QModbusRtuSerialServer;
#else
typedef ::QModbusRtuSerialServer QModbusRtuSerialServer;
#endif

}
}
}

//</CuteHMI.Workarounds.Qt5Compatibility-3.workaround>

#endif // QMODBUSRTUSERIALSERVER_HPP
