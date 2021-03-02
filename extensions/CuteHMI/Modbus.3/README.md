# Modbus

![Development status](doc/status-alpha.svg)

This extension provides support for Modbus protocol. Its main purpose is to allow for configuring and interacting with Modbus
devices from QML.

Modbus is an industrial communcation protocol originally designed by Modicon to be used with a series of their PLCs (Programmable
Logic Controllers). It is still one of the most popular protocols used in automation and many devices support Modbus as their
communication interface.

## Device classes

Modbus devices can be divided into two basic categories: servers and clients. In Modbus nomenclature clients are often called
masters and servers are called slaves.

Modbus is a higher level protocol [[1]][National Instruments - The Modbus Protocol In-Depth]
[[2]][Acromag - Introdution To Modbus TCP/IP], hence each server or client can perform communication over arbitrary lower level
protocol stack. Two most common solutions are TCP/IP and RTU (Remote Terminal Unit, which again is a sort of abstraction, but
typically means serial port communcation).

cutehmi::modbus::AbstractDevice is a base class for all Modbus devices. It defines common features of all Modbus devices.

cutehmi::modbus::AbstractClient and cutehmi::modbus::AbstractServer are abstract classes for clients and servers respectively.

cutehmi::modbus::RTUClient and cutehmi::modbus::RTUServer implement client and server functionalities using serial port communication.

cutehmi::modbus::TCPClient and cutehmi::modbus::TCPServer implement client and server functionalities using TCP/IP to communicate.

cutehmi::modbus::DummyClient is a special client that does not need a server to communicate with and it can be used to test UI for example.

Device classes are lowest level API of the extension. They are centered around an idea of JSON requests and replies, inspired by web
REST interfaces. Additionaly classes have various properties allowing one to configure devices or check their statuses from QML.

Device classes are intended to be used with [CuteHMI.Services](../Services.2/). Notably device object will not perform
polling on its own. For this purpose device classes implement cutehmi::services::Serviceable interface. Device object must be
embedded in cutehmi::services::Service object to perform polling (after services are started by cutehmi::services::ServiceManager).
In return its state is managed by the state machine, which will handle start/stop requests, try to repair broken connections etc.

## Register controllers

Modbus protocol is oriented around four classes of registers, which can be viewed as four contiguous memory regions. These are:
holding registers, input registers, coils and discrete inputs. Clients can read and write to holding registers and coils; input
registers and discrete inputs provide read-only access for clients. Holding registers and input registers are addressed with 16 bit
byte, while byte is 1 bit wide for discrete inputs and coils (byte is smallest addressable unit of memory).

While registers can be accessed with device classes, in most cases imperative function calls do not fit well into QML declarative
syntax. Typically it is better to access a register from QML using one of the controller classes. There is one class registered as
QML component for each of the Modbus register types: CuteHMI.Modbus.CoilController, CuteHMI.Modbus.DiscreteInputController,
CuteHMI.Modbus.InputRegisterController and CuteHMI.Modbus.HoldingRegisterController, but they share most of the code, because
there is not much of the difference between them.

Controllers are better suited for accessing registers from QML, because they reveal various register aspects through a set of
properties. They allow one to easily control how reads and writes are performed. They track requests, interpret responses and
translate the sequence of events in between into convenient signals. Their properties can be binded with other QML components.

## Register items

Register items are convenient components, which are composed of a controller and visual indicator item. They are particularly
useful in "Design" mode. For each register controller there is corresponding register item, that is: CuteHMI.Modbus.CoilItem,
CuteHMI.Modbus.DiscreteInputItem, CuteHMI.Modbus.HoldingRegisterItem and CuteHMI.Modbus.InputRegisterItem.

## Relationship between classes

Structural relationship between extension classes is conceptually shown on the following quasi-UML diagram.

![Relationship between extension classes](doc/quasi_uml.svg)

[National Instruments - The Modbus Protocol In-Depth]: https://www.ni.com/pl-pl/innovations/white-papers/14/the-modbus-protocol-in-depth.html
[Acromag - Introdution To Modbus TCP/IP]: https://www.prosoft-technology.com/kb/assets/intro_modbustcp.pdf

## QML components

Classes exposed as QML components are listed within CuteHMI.Modbus namespace.

## Examples

The extension is supplemented by following examples.

- [CuteHMI.Examples.Modbus.Basic.2](../Examples/Modbus/Basic.2/)
- [CuteHMI.Examples.Modbus.ClientServer.2](../Examples/Modbus/ClientServer.2/)
- [CuteHMI.Examples.Modbus.ControllerItems.2](../Examples/Modbus/ControllerItems.2/)
- [CuteHMI.Examples.Modbus.Controllers.2](../Examples/Modbus/Controllers.2/)
- [CuteHMI.Examples.Modbus.Requests.2](../Examples/Modbus/Requests.2/)

The one to get started with is [CuteHMI.Examples.Modbus.Basic.2](../Examples/Modbus/Basic.2/). This example shows basic usage of QML
components. Another simple example [CuteHMI.Examples.Modbus.ControllerItems.2](../Examples/Modbus/ControllerItems.2/) is provided to
work with Qt Creator in "Design" mode. The other examples are provided to demonstrate more advanced features.

### Changes

Compared to previous major version, following changes have been made.

Register items do not have aliases to internal controller, instead they expose `controller` property.

