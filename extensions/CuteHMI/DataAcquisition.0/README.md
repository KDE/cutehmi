# Data Acquisition

This extension provides fundamental components for data acquisition - a pillar of SCADA system.

This extension internally relies on [CuteHMI.SharedDatabase.0](../SharedDatabase.0/) extension and it is heavily recommended to use
it with database connection created with [CuteHMI.SharedDatabase.0](../SharedDatabase.0/).

Currently PostgreSQL and SQLite backends are supported.

## Creating the schema

In order to use this extension, apart from making [CuteHMI.SharedDatabase.0](../SharedDatabase.0/) operational, a schema has to be
created. This can be done from QML, but creation and drop scripts are also listed below.

### PostgreSQL

Following script is used for PostgreSQL to create schema. All occurrences of `%1` shall be replaced with given schema name.

@include sql/postgres/create.sql

To drop the schema use the following.

@include sql/postgres/drop.sql

### PostgreSQL

Following script is used for SQLite to create schema. SQLite treats database name as a schema, thereofre schema name is incorporated
into table names. This requires table names to be wrapped in square brackets. All occurrences of `%1` shall be replaced with given
schema name.

@include sql/sqlite/create.sql

To drop the schema use the following.

@include sql/sqlite/drop.sql
