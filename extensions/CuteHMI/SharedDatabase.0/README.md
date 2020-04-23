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
