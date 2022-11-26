# Data Acquisition

![Development status](doc/status-alpha.svg)

This extension provides fundamental components for data acquisition - a pillar of SCADA system.

This extension internally relies on [CuteHMI.SharedDatabase.1](../SharedDatabase.1/) extension and it is heavily recommended to use
it with database connection created with [CuteHMI.SharedDatabase.1](../SharedDatabase.1/).

Currently PostgreSQL and SQLite backends are supported.

## Creating the schema

In order to use this extension, apart from making [CuteHMI.SharedDatabase.1](../SharedDatabase.1/) operational, a schema has to be
created. This can be done from C++ or QML, but creation and drop scripts are also listed below.

### Console tool

Schema can be created with [cutehmi.console.0](../../../tools/cutehmi.console.0/) tool. To do so launch the tool.
```
cutehmi.console.0 CuteHMI.DataAcquisition.1
```

#### TL;DR

To determine whether it will work at all, type the following in the console.
```
# service.start()
CuteHMI.2: [NOTIFICATION] Service 'Database Service' has started.
# schema.create()
CuteHMI.2: [NOTIFICATION] Successfully created 'console' schema.
```
This should create default SQLite database, appropriate for testing.

To drop the schema type:
```
# schema.drop()
CuteHMI.2: [NOTIFICATION] Dropped 'console' schema.
```

#### Custom setup

For customized setup, first you need to pick a database type.
```
# db.type = "QPSQL"
```
Valid types are `QPSQL` for PostgreSQL and `QSQLITE` for SQLite.

Supply database name.
```
# db.name = "meinDatabase"
```
Note that SQLite will create a file with database given name, but for PostgreSQL you must create database beforehand!

Then for PostgreSQL typically follows `host`, `port`, `user` and `password`, but SQLite driver ignores most of these fields.
```
# db.host = "localhost"
# db.port = 5432
# db.user = "postgres"
# db.password = "postgres"
```

Start the service.
```
# service.start()
CuteHMI.2: [NOTIFICATION] Service 'Database Service' has started.
```
If you get errors, fix database setup, ensure that database is runnig, check permissions, firewall, default gateway, etc. Start
with cables...

Now you may choose shcema name.
```
# schema.name = "meinSchema"
```

Schema user can be also selected. Database defaults are used if left empty.
```
# schema.user = "Adolf"
```

To complete the process call create() slot.
```
# schema.create()
CuteHMI.2: [NOTIFICATION] Successfully created 'meinSchema' schema.
```

Schema can be dropped in a similar way by calling drop() slot.
```
# schema.drop()
CuteHMI.2: [NOTIFICATION] Dropped 'meinSchema' schema.
```

### PostgreSQL

Following script is used for PostgreSQL to create schema. All occurrences of `%1` shall be replaced with given schema name.

@include sql/postgres/create.sql

To drop the schema use the following.

@include sql/postgres/drop.sql

### SQLite

Following script is used for SQLite to create schema. SQLite treats database name as a schema, therefore schema name is incorporated
into table names. This requires table names to be wrapped in square brackets. All occurrences of `%1` shall be replaced with given
schema name.

@include sql/sqlite/create.sql

To drop the schema use the following.

@include sql/sqlite/drop.sql
