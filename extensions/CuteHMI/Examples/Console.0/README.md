# Console Example

This extension can be used to demonstrate basic usage of [cutehmi.console.0](../../../../tools/cutehmi.console.0/) tool.

To run the example use following command.
```
cutehmi.console.0 CuteHMI.Examples.Console.0
```

The example defines very simple QtObject-based `Console` component, which looks as follows.

\snippet Console.qml QtObject

This component is instantiated by [cutehmi.console.0](../../../../tools/cutehmi.console.0/) tool and it can be queried from the
command line. Let's ask for its `book` property.
```
# book
cutehmi.console.0: QVariant(QString, Mein Kampf by Adolf Hitler)
```

We can call `tell()` function as well.
```
# tell()
qml: I highly recommend the book Mein Kampf by Adolf Hitler!
```

If you don't like this book the `book` property can be altered from the command line.
```
# book = "The Star Diaries by Stanislaw Lem"
```

Now `tell()` function yields.
```
# tell()
qml: I highly recommend the book The Star Diaries by Stanislaw Lem!
```

To finish the console session type `\q`.

\example Console.qml
Here is a complete listing of the example source file.
