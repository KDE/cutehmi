# Changes

## Version 4

- This version has switched from CuteHMI.Services.2 to CuteHMI.Services.3.
- Property `initialized` has been introduced in cutehmi::modbus::AbstractRegisterController. Controller items use it for more robust
delegate initialization.

## Version 3

- Register items do not have aliases to internal controller, instead they expose `controller` property.
- Property `pollingTimer` has been replaced in cutehmi::modbus::AbstractClient by `pollingInterval` and `pollingTaskInterval`
properties.
- Property `requestInterval` has been added to cutehmi::modbus::AbstractClient.
- Names of protected signals have been changed in server and client classes from `requestReceived` to `requestAccepted`.
