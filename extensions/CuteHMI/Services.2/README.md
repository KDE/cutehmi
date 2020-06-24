# Services

![Development status](doc/status-beta.svg)

Extension that helps creating services. Many extensions may need to behave like services or daemons, doing their tasks in the
background, independently from UI. This extension helps to organize and coordinate them.

Services work on a basis of [The State Machine Framework](https://doc.qt.io/qt-5/statemachine-api.html). Each service is controlled
by its own state machine. This state machine is composed of some standard, predefined states commonly referred as _state interface_.
The details of actions performed in those state, as well as some of the transitions, are a subject of cutehmi::services::Serviceable
implementation.

# Major classes

Each object that wants to become a service implements cutehmi::services::Serviceable interface.

In order to turn object that implements cutehmi::services::Serviceable interface into a service one has to embed it inside
cutehmi::services::Service object.

Singleton cutehmi::services::ServiceManager is responsible for managing services as well as starting and stopping them.
