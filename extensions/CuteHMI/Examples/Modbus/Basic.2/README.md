# Basic Modbus Example

Baisc Modbus example. Example demonstrates basic usage of QML components provided by [CuteHMI.Modbus.3](../../../Modbus.3/)
extension.

To run the example use [cutehmi.view.4](../../../../../tools/cutehmi.view.4/) tool.
```
cutehmi.view.4 CuteHMI.Examples.Modbus.Basic.0
```

Let's make a quick tour over `View.qml` file.

First thing to notice are CuteHMI imports.

\snippet View.qml Import statements

Example uses [CuteHMI.Modbus.3](../../../Modbus.3/) and [CuteHMI.Services.2](../../../Services.2/) extensions.

Next thing to notice is a configuration of a Modbus server. The server is given an IP address, a port and a slave address.

\snippet View.qml Configuring a server

Similarly we configure Modbus client.

\snippet View.qml Configuring a client

We want our server to be managed by CuteHMI.Services.ServiceManager, so that we don't need to worry about its connection status.
This is simply done by embedding it inside CuteHMI.Services.Service component.

\snippet View.qml Setting up server service

Similarly we want the client to be turned into a service. Outside a service client would not perform polling, handle connection
errors and so on.

\snippet View.qml Setting up client service

As the client and the server are configured we can move on to establishing some interaction between them. Let's create a button that
will tell the client to send a request to turn on a coil.

\snippet View.qml  Client set coil button

Once the button is clicked it will send a request to write coil value at address 10. This may look suspicious on a localhost, but
the whole communication is done over TCP/IP protocol. Now let's reset coil value to off on the server side.

\snippet View.qml  Server reset coil button

Now let's introduce CuteHMI.Modbus.CoilController. Controllers typically are a better mean of control as they allow for property
binding.

\snippet View.qml Coil controller

We assign a device using \a id of of the client. We also set up the same address as used by buttons. We use `onValueChanged` signal
handler to update value of a corresponding switch once the value in the controller changes. The switch itself updates the value of
a controller once the user changes its value.

\snippet View.qml Switch onCheckedChanged handler

Value of the coil can be binded to other properties as it is done with `active` property of status indicator.

\snippet View.qml Status indicator binding

The same procedure is repeated for a holding register, of course using different set of controls - adequate to holding register 16
bit integer capacity.

\snippet View.qml Holding register controls

Last, but not least. We start the services by calling CuteHMI.Services.ServiceManager.start() slot.

\snippet View.qml Start services

\example View.qml
Here is a complete listing of the example source file.
