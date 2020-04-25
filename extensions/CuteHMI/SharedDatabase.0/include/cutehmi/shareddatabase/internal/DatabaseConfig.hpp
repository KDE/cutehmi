#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONFIG_HPP

#include "common.hpp"

#include <QSharedDataPointer>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

class CUTEHMI_SHAREDDATABASE_PRIVATE DatabaseConfig final
{
	public:
		class Data:
			public QSharedData
		{
			public:
				Data();

				Data(const Data & other) = default;

				QString type;
				QString host;
				int port;
				QString name;
				QString user;
				QString password;
				QString connectionName;
		};

		typedef QSharedDataPointer<Data> DataPtr;

		DatabaseConfig();

		DatabaseConfig(const DatabaseConfig &) = default;

		~DatabaseConfig() = default;

		DatabaseConfig & operator=(const DatabaseConfig &) = default;

		const DataPtr & data() const;

		DataPtr & data();

	private:
		QSharedDataPointer<Data> m_data;
};

}
}
}

#endif
