# CuteHMI - View

Client, GUI application, which allows one to run CuteHMI project in a window.

Any extension that provides graphical UI QML component can be loaded as CuteHMI project. Use `--extension` command line argument to
specify an extension. To run 'Simple View' example use following command.
```
cutehmi_view --extension="CuteHMI.Examples.SimpleView.0"
```
To run project from QtCreator click `Projects` -> `Run`. Select `cutehmi_view` from `Run configuration:`. In the
`Command line arguments:` box type: `cutehmi_view --extension="CuteHMI.Examples.SimpleView.0"`.
The window should look similar to the screenshot below.
![SimpleView screenshot](doc/SimpleView.png)

For debug builds use `cutehmi_view_debug` instead of `cutehmi_view`.

Default loader picks `Main.qml` as default QML component to load. Component can be specified with `--component` option. One can also
use `--init` option to replace default loader with custom one.

You can use `--help` command line argument to see a list of all possible command line options.
