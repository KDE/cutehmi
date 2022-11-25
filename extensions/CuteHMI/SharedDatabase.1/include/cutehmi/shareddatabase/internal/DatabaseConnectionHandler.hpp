#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONNECTIONHANDLER_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONNECTIONHANDLER_HPP

#include "common.hpp"
#include "DatabaseConfig.hpp"

#include <cutehmi/InplaceError.hpp>

#include <QObject>
#include <QBasicTimer>
#include <QSqlDatabase>


namespace cutehmi {
namespace shareddatabase {
namespace internal {

class CUTEHMI_SHAREDDATABASE_PRIVATE DatabaseConnectionHandler:
	public QObject
{
		Q_OBJECT

		typedef QObject Parent;

	public:
		static constexpr int INITIAL_MONITOR_INTERVAL = 1000;

		static constexpr int INITIAL_MAINTENANCE_INTERVAL = 1000 * 60 * 60 * 12;

		DatabaseConnectionHandler(DatabaseConfig config, QObject * parent = nullptr);

	public slots:
		void connect();

		void disconnect();

	signals:
		void connected(QString connectionName);

		void disconnected(QString connectionName);

		void errored(cutehmi::InplaceError error);

	protected:
		void timerEvent(QTimerEvent * event) override;

	private slots:
		void printError(cutehmi::InplaceError error);

	private:
		struct Members
		{
			int monitorInterval;
			int maintenanceCount;
			DatabaseConfig config;
			QBasicTimer monitorTimer;
			QSqlDatabase db;
			QString connectionName;

			Members(DatabaseConfig p_config):
				monitorInterval(INITIAL_MONITOR_INTERVAL),
				maintenanceCount(0),
				config(p_config)
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
