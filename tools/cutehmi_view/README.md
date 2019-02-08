# CuteHMI - View

Client, GUI application, which allows one to run CuteHMI project in a window.

Use `--project` command line option to specify a QML project file to open.
For example to run 'Simple View' example use following command.
```
cutehmi_view --project="examples/SimpleView/_Main.qml"
```

Fore debug builds use `cutehmi_view_debug` instead of `cutehmi_view`.

To run project from QtCreator click `Projects` -> `Run`. Select `cutehmi_view` from `Run configuration:`. In the
`Command line arguments:` box type: `--project="examples/SimpleView/_Main.qml"`.

You can use `--help` command line argument to see a list of all possible command
line options.
