#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASETHREAD_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASETHREAD_HPP

#include "common.hpp"
#include "DatabaseConnectionHandler.hpp"

#include <QThread>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

class CUTEHMI_SHAREDDATABASE_PRIVATE DatabaseThread:
	public QThread
{
		Q_OBJECT

	public:
		DatabaseThread(QObject * parent = nullptr);

		void start(std::unique_ptr<DatabaseConnectionHandler> handler);

	protected:
		void run() override;

	private:
		struct Members
		{
			std::unique_ptr<DatabaseConnectionHandler> handler;
		};

		MPtr<Members> m;
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
