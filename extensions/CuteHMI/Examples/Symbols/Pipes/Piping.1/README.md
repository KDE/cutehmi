# Piping example

This example shows how to use piping components provided by [CuteHMI.Symbols.Pipes.1](../../../../Symbols/Pipes.1/) extension.

To run the example use [cutehmi.view.3](../../../../../../tools/cutehmi.view.3/) tool.
```
cutehmi.view.3 --extension="CuteHMI.Examples.Symbols.Pipes.Piping.1"
```

A remark on Qt Creator.

\snippet Main.qml Red-blue pipe

Qt Creator may refuse to render this pipe in "Design" mode. PipeConnector objects are created within named properties of red and
blue rectangles.

\snippet Main.qml Red rectangle outlet property

It comes out Qt Creator has troubles with such bindings if component is defined inplace. It would render pipe correctly however, if
rectangles were defined in separate QML files. Thus if one wants to use PipeConnector objects as item properties with Qt Creator in
"Design" mode, he has to pack such code into custom QML component. For example red rectangle code below could be moved to
`RedRectangle.qml` file.

\snippet Main.qml Red rectangle

\example Main.qml
Here is a complete listing of the example source file.
