import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_charts_qml_1"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "Charts QML"

	description: "QML components for data visualization with charts."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIChartsQMLPlugin.cpp",
        "src/CuteHMIChartsQMLPlugin.hpp",
        "src/cutehmi/charts/qml/CartesianAxis.cpp",
        "src/cutehmi/charts/qml/CartesianAxis.hpp",
        "src/cutehmi/charts/qml/DateTimeAxis.cpp",
        "src/cutehmi/charts/qml/DateTimeAxis.hpp",
        "src/cutehmi/charts/qml/LinearAxis.cpp",
        "src/cutehmi/charts/qml/LinearAxis.hpp",
        "src/cutehmi/charts/qml/PlotArea.cpp",
        "src/cutehmi/charts/qml/PlotArea.hpp",
        "src/cutehmi/charts/qml/ScatterPlot.cpp",
        "src/cutehmi/charts/qml/ScatterPlot.hpp",
        "src/cutehmi/charts/qml/TickedAxis.cpp",
        "src/cutehmi/charts/qml/TickedAxis.hpp",
        "src/cutehmi/charts/qml/ValueAxis.cpp",
        "src/cutehmi/charts/qml/ValueAxis.hpp",
    ]

	//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_charts_1" } cutehmi_charts_1.reqMinor: 0
	//</workaround>

	Depends { name: "Qt.quick" }
}

