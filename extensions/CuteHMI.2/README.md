# CuteHMI

This module provides core functionality to other modules.

It provides various utility classes and bridges that help other extensions and tools to communicate with each other.

## Bridges

[Logging macros](@ref loggingMacros.hpp) help deliver consistently looking logging messages to power users and developers.

Messages that should show up in user interface can be delivered through cutehmi::Dialog and cutehmi::Notification classes.

## Utility classes

cutehmi::Singleton class template can be used to create singleton classes.

cutehmi::Worker class can be helpful, when dealing with Qt database connections.

cutehmi::MPtr can be helpful, when class uses PImpl idiom to maintain binary compatibility.

cutehmi::Error, cutehmi::ErrorInfo, cutehmi::Exception and cutehmi::ExceptionMixin may be useful, when dealing with errors and
exceptions.

## QML components

CuteHMI::Palette and CuteHMI::ColorSet help provide consistent color codes accross projects.

CuteHMI::Element component should be used to create color code aware items.

CuteHMI::NumberDisplay provides convenient display.

## Frontend tools

Frontend tools should take care about cutehmi::Notifier and cutehmi::Dialogist classes to deliver messages to the users. They should
also call cutehmi::destroySingletonInstances() function.
