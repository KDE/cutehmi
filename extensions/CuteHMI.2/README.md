# CuteHMI

This module provides core functionality to other modules.

It provides various utility classes and bridges that help other extensions and tools to communicate with each other.

## Bridges

[Logging macros](@ref loggingMacros.hpp) help deliver consistently looking logging messages to power users and developers.

Messages that should show up in user interface can be delivered through Dialog and Notification classes.

## Utility classes

Singleton class template can be used to create singleton classes.

Worker class can be helpful, when dealing with Qt database connections.

MPtr can be helpful, when class uses PImpl idiom to maintain binary compatibility.

Error, ErrorInfo, Exception and ExceptionMixin may be useful, when dealing with errors and exceptions.

## Frontend tools

Frontend tools should take care about Notifier and Dialogist classes to deliver messages to the users. They should also call
destroySingletonInstances() function.
