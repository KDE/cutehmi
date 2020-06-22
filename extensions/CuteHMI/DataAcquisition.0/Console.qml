import QtQml 2.0

import CuteHMI.Services 2.0
import CuteHMI.SharedDatabase 0.0
import CuteHMI.DataAcquisition 0.0

QtObject {
	objectName: "console"

	property Database db: Database {
		objectName: "db"

		connectionName: "cutehmi::dataacquisition"
		type: "QSQLITE"
		host: "localhost"
		port: 5432
		name: "cutehmi_dataacquisition"
		user: "postgres"
		password: "postgres"
		threaded: false

		/**
		  Set PostgreSQL default settings.
		  */
		function setPostgresDefaults() {
			type = "QPSQL"
			host = "localhost"
			port = 5432
			name = "postgres"
			user = "postgres"
			passowrd = "postgres"
		}

		/**
		  Set SQLite default settings.
		  */
		function setSQLiteDefaults() {
			type = "QSQLITE"
			name = "cutehmi_dataacquisition"
		}
	}

	property Schema schema: Schema {
		objectName: "schema"
		name: "cutehmi_dataacquisition"

		connectionName: "cutehmi::dataacquisition"
	}

	property Service service: Service {
		objectName: "service"

		name: "Database Service"
		serviceable: db
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
