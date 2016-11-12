#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_DATABASECONNECTIONDATA_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_DATABASECONNECTIONDATA_HPP

#include <QString>

namespace cutehmi {
namespace stupid {

struct DatabaseConnectionData
{
	QString type;
	QString connectionName;
	QString hostName;
	int port;
	QString databaseName;
	QString userName;
	QString password;
};

}
}

#endif
