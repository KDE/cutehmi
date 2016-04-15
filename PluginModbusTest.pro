TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    LibBase \
    LibModbus \
    PluginModbus \
    PluginModbusTest

PluginModbusTest.file = PluginModbus/PluginModbusTest.pro
