# Changes

## Version 3

- ServiceManager has been replaced with cutehmi::services::ServiceGroup and classes derived from
  cutehmi::services::AbstractServiceController or cutehmi::services::ServiceGroupRule can be used to control service operations.
- cutehmi::services::SelfService can be used to define QML services without the need of using C++ API.
- cutehmi::services::StateInterface provides clean access to service states.
- cutehmi::services::Serviceable has been slightly modified and state interface allows for reconfiguration of the state machine.
- PollingTimer has been removed.
