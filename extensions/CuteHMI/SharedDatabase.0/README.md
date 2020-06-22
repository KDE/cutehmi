# Shared Database

This extension acts as shared database provider. The intent of this extension is to provide database connections, which live in
dedicated database threads, but can be shared across different extensions. Below is a brief description of classes, which help to
accomplish this.

Class cutehmi::shareddatabase::Database is responsible for configuring and maintaining database connection that lives in dedicated
thread. From QML (`import CuteHMI.SharedDatabase.0`) it is available as @ref CuteHMI::SharedDatabase::Database "Database" component.

cutehmi::shareddatabase::DatabaseWorker is a convenient class that allows one to run SQL-specific code in the dedicated database
thread.

In order to make this extension work you need Qt SQL module and appropriate client library as explained in Qt documentation on
[SQL Database Drivers](https://doc.qt.io/qt-5/sql-driver.html). For development purposes you can copy library files to `deploy/lib`
subdirectory of [external](../../../external/) folder. This is handy especially on Windows.

## Console

Extensions provides cutehmi::shareddatabase::Console component, which can be used with
[cutehmi.console.0](../../../tools/cutehmi.console.0/) tool.
```
cutehmi.console.0 CuteHMI.SharedDatabase.0
```

This component allows for some very basic database operations. You can check out whether connection works by setting properties on
`db` object. For example below is a typical default PostgreSQL configuration.
```
# db.type = "QPSQL"
# db.name = "postgres"
# db.host = "localhost"
# db.port = 5432
# db.user = "postgres"
# db.password = "postgres"
```

Connection can be tested by starting the service.
```
# service.start()
CuteHMI.2: [NOTIFICATION] Service 'Database Service' has started.
```

In case of error different notification is shown.
```
CuteHMI.2: [NOTIFICATION] Service 'Database Service' broke.
```

Once connection is established one can create PostgreSQL database.
```
# postgres.createDatabase("some_database")
CuteHMI.2: [NOTIFICATION] Created 'some_database' database.
```

One can use JavaScript object to specify parameters after `WITH` keyword.
```
# postgres.createDatabase("some_database", {"OWNER":"postgres", "TEMPLATE":"default"})
```

Database can be dropped in a similar way.
```
# postgres.dropDatabase("some_database")
CuteHMI.2: [NOTIFICATION] Dropped 'some_database' database.
```
