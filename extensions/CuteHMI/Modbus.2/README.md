# Modbus

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

Device classes are intended to be used with [CuteHMI.Services](../Services.2/README.md). Notably device object will not perform
polling on its own. For this purpose device classes implement cutehmi::services::Serviceable interface. Device object must be
embedded in cutehmi::services::Service object to perform polling (after services are started by cutehmi::services::ServiceManager).
In return its state is managed by the state machine, which will handle start/stop requests, try to repair broken connections etc.

## Register controllers

Modbus protocol is oriented around four classes of registers, which can be viewed as four contiguous memory regions. These are:
holding registers, input registers, coils and discrete inputs. Clients can read and write to holding registers and coils; input
registers and discrete inputs provide read-only access for clients. Holding registers and input registers are addressed with 16 bit
byte, while byte is 1 bit wide for discrete inputs and coils (byte is smallest addressable unit of memory).

While registers can be accessed with device classes, in most cases imperative function calls do not fit well into QML declarative
syntax. Typically it is better to access a register from QML using one of the controller classes. There is one controller class for
each of the Modbus register types: cutehmi::modbus::CoilController, cutehmi::modbus::DiscreteInputController,
cutehmi::modbus::InputRegisterController and cutehmi::modbus::HoldingRegisterController, but they share most of the code, because
there is not much of the difference between them.

Controllers are better suited for accessing registers from QML, because they reveal various register aspects through a set of
properties. They allow one to easily control how reads and writes are performed. They track requests, interpret responses and
translate the sequence of events in between into convenient signals. Their properties can be binded with other QML components.

## Register items

Register items are convenient components, which are composed of a controller and visual indicator item. They are particularly
useful in "Design" mode. For each register controller there is corresponding register item, that is: CuteHMI::Modbus::CoilItem,
CuteHMI::Modbus::DiscreteInputItem, CuteHMI::Modbus::HoldingRegisterItem and CuteHMI::Modbus::InputRegisterItem.

Relationship between extension classes is conceptually shown on the following quasi-UML diagram.

![Relationship between extension classes](doc/quasi_uml.svg)

[National Instruments - The Modbus Protocol In-Depth]: https://www.ni.com/pl-pl/innovations/white-papers/14/the-modbus-protocol-in-depth.html
[Acromag - Introdution To Modbus TCP/IP]: https://www.prosoft-technology.com/kb/assets/intro_modbustcp.pdf
