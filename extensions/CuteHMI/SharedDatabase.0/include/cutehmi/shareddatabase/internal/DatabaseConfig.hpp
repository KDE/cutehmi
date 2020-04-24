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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
