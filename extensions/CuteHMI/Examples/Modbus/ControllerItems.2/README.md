# Modbus Controller Items

The purpose of this example is to demonstrate the use of controller items, which are especially useful, when dealing with Qt Creator
"Design" mode.

Read a documentation on \ref using-qt-creator-in-design-mode.md "Using Qt Creator in Design mode" to see how to set up environment
for this example.

In this example component \ref Screen.ui.qml "Screen" is intended to be edited in "Design" mode. This should look similar to the
screenshot below.

![Design mode](doc/design_mode.png)

As one can observe CuteHMI.Modbus.CoilItem and CuteHMI.Modbus.HoldingRegisterItem are created as child items of respective Qt
Quick controls, which they use as their delegates. Binding is established between controller and specified delegate property.

The example can be run with [cutehmi.view.4](../../../../../tools/cutehmi.view.4/) tool.
```
cutehmi.view.4 CuteHMI.Examples.Modbus.ControllerItems.1
```

\example View.qml
Here is a complete listing of the example source file.

\example Screen.ui.qml
Here is a complete listing of the example source file.
