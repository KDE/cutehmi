# Command

Console program, which allows one to run QML script.

This is a simple tool that allows one to execute script in a context of QML extension. One specifies extension to import with
`--extension` command line argument option. Then `--script` option can be used to specify JavaScript code to be executed.

For example following command imports `CuteHMI.2` extension and prints default, maximal amount of notifications that `Notifier`
singleton keeps.

```
cutehmi.cmd.0 --extension="CuteHMI.2" --script="console.info('maxNotifications: ' + Notifier.maxNotifications)"
```

Which should give output similar to the one below.

```
qml: maxNotifications: 2147483647
```

The motiviation behind this tool is to make it possible to conveniently set up or configure an extenision, in situations, when no
GUI is available. Creating a schema of a database is an example use case.

If required minor version of the extension can be specified with `--minor` option.
