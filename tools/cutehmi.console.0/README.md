# Console

Interactive command line interface, which allows one to browse QML object model and evaluate expressions.

This tool allows one to execute QML expressions. One specifies an extension and the tool will make an attempt to import that
extension and instantiate `Console` component. If the extension does not provide `Console` component an alternative non-GUI
component may be specified with `--component` option.

For example following command imports [Console Example](../../extensions/CuteHMI/Examples/Console.0/) extension, which provides
`Console` component allowing for some basic interaction with the tool.
```
cutehmi.console.0 CuteHMI.Examples.Console.0
```

After starting the program, a command prompt is shown. Command line interpreter basically works in two modes: console command mode
and QML expression mode. Any command that starts with `\` character is interpreted as console command; everything else is
interpreted as QML expression.

For example `\quit` command is prepended by `\`, so it is interpreted as console command, which quits the console.
```
# \quit
```

But the following are treated as QML expressions with the results of evaluation printed below.
```
# 2+2
cutehmi.console.0: QVariant(int, 4)
# console.info("huhu")
qml: huhu
```

The motiviation behind this tool is to make it possible to conveniently set up or configure an extenision, in situations, when no
GUI is available. Creating a schema of a database is an example use case.
