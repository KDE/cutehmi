import QtQml 2.0

import CuteHMI.Services 2.0
import CuteHMI.SharedDatabase 0.0
import CuteHMI.DataAcquisition 0.0

QtObject {
	objectName: "console"

	property Database db: Database {
		objectName: "db"

		connectionName: "cutehmiDataAcquisition"
		type: "QSQLITE"
		host: "localhost"
		port: 5432
		name: "cutehmi_data_acquisition"
		user: "postgres"
		password: "postgres"
		threaded: false
	}

	property Schema schema: Schema {
		objectName: "schema"
		name: "console"

		connectionName: "cutehmiDataAcquisition"
	}

	property Service service: Service {
		objectName: "service"

		name: "Database Service"
		serviceable: db
	}
}
