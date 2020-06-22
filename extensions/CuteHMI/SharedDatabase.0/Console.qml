import QtQml 2.0

import CuteHMI.Services 2.0
import CuteHMI.SharedDatabase 0.0

QtObject {
	objectName: "console"

	property Database db: Database {
		objectName: "db"

		connectionName: "cutehmi::shareddatabase"
		type: "QSQLITE"
		host: "localhost"
		port: 5432
		name: "cutehmi_shareddatabase"
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
			name = "cutehmi_shareddatabase"
		}
	}

	property Service service: Service {
		objectName: "service"

		name: "Database Service"
		serviceable: db
	}

	property PostgresMaintenance postgres: PostgresMaintenance {
		objectName: "postgres"

		connectionName: "cutehmi::shareddatabase"
	}
}
