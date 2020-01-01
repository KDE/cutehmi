# qmlplugindump

This is a fork of _qmlplugindump_ shipped with Qt. It is provided as a solution for generating _qmltypes_ artifacts in debug builds.
Standard _qmlplugindump_ is linked against release version of Qt libraries, hence an attempt to generate _qmltypes_ from debug
versions of plugins ends with an error message: "cannot mix debug and release libraries".
