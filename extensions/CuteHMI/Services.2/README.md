# Services

Extension that helps creating services. Many extensions may need to behave like services or daemons, doing their tasks in the
background, independently from UI. This extension helps to organize and coordinate them.

# Main classes

Each object that wants to becme a service implements cutehmi::services::Serviceable interface.

In order to turn object that implements cutehmi::services::Serviceable interface into a service one has to embed it inside
cutehmi::services::Service object.

Singleton cutehmi::services::ServiceManager is responsible for managing services as well as starting and stopping them.
