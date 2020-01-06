# Basic Modbus Example

Baisc Modbus example. Example demonstrates basic usage of QML components provided by [CuteHMI.Modbus.2](../../../Modbus.2/)
extension.

To run the example use [cutehmi.view.2](../../../../../tools/cutehmi.view.2/) tool.
```
cutehmi.view.2 --extension="CuteHMI.Examples.Modbus.Basic.0"
```

Let's make a quick tour over `Main.qml` file.

First thing to notice are %CuteHMI imports.

\snippet Main.qml Import statements

Example uses [CuteHMI.Modbus.2](../../../Modbus.2/) and [CuteHMI.Services.2](../../../Services.2/) extensions.

Next thing to notice is a configuration of a Modbus server. The server is given an IP address, a port and a slave address.

\snippet Main.qml Configuring a server

Similarly we configure Modbus client.

\snippet Main.qml Configuring a client

We want our server to be managed by cutehmi::services::ServiceManager, so that we don't need to worry about its connection status.
This is simply done by embedding it inside cutehmi::services::Service component.

\snippet Main.qml Setting up server service

Similarly we want the client to be turned into a service. Outside a service client would not perform polling, handle connection
errors and so on.

\snippet Main.qml Setting up client service

As the client and the server are configured we can move on to establishing some interaction between them. Let's create a button that
will tell the client to send a request to turn on a coil.

\snippet Main.qml  Client set coil button

Once the button is clicked it will send a request to write coil value at address 10. This may look suspicious on a localhost, but
the whole communication is done over TCP/IP protocol. Now let's reset coil value to off on the server side.

\snippet Main.qml  Server reset coil button

Now let's introduce cutehmi::modbus::CoilController. Controllers typically are a better mean of control as they allow for property
binding.

\snippet Main.qml Coil controller

We assign a device using \a id of of the client. We also set up the same address as used by buttons. We use `onValueChanged` signal
handler to update value of a corresponding switch once the value in the controller changes. The switch itself updates the value of
a controller once the user changes its value.

\snippet Main.qml Switch onCheckedChanged handler

Value of the coil can be binded to other properties as it is done with `active` property of status indicator.

\snippet Main.qml Status indicator binding

The same procedure is repeated for a holding register, of course using different set of controls - adequate to holding register 16
bit integer capacity.

\snippet Main.qml Holding register controls

Last, but not least. We start the services by calling cutehmi::services::ServiceManager::start() slot.

\snippet Main.qml Start services

\example Main.qml
Here is a complete listing of the example source file.
