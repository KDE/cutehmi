# View

![Development status](doc/status-gamma.svg)

Client, GUI application, which allows one to run CuteHMI project in a window.

By default this tool shows only a simple help screen.

![Default view screenshot](doc/screenshot.png)

CuteHMI approach is to treat each project as a first-class QML extension, so the purpose of the tool is to load specified extension
and display one of its QML components. Any extension that provides graphical UI QML component can be loaded as *cutehmi.view.4*
project. Use command line argument to specify an extension.

For example to run [Simple View](../../extensions/CuteHMI/Examples/SimpleView.2/) example use following command.
```
cutehmi.view.4 CuteHMI.Examples.SimpleView.2
```

To run project from QtCreator click `Projects` -> `Run`. Select `cutehmi.view.4` from `Run configuration`. In the
`Command line arguments` box type: `CuteHMI.Examples.SimpleView.2`.
The window should look similar to the screenshot below.

![SimpleView screenshot](doc/SimpleView.png)

Default loader picks `View` as default QML component to load. Component can be specified with second positional argument. For
example following displays `RectangularElement` component from the previous example.
```
cutehmi.view.4 CuteHMI.Examples.SimpleView.2 RectangularElement
```

One can also use `--init` option to replace default loader with custom one.

You can use `--help` command line argument to see a list of all possible command line options.

For debug builds use `cutehmi.view.4.debug` instead of `cutehmi.view.4`.

## Changes

Compared to previous major version following changes were made.
- View looks for `View` component instead of `Main`.
- Extension is specified with first positional argument instead of `--extension` argument.
- Component is specified with second positional argument instead of `--component` argument.
