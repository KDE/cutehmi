import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_charts_1_qml"

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

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_charts_1" } cutehmi_charts_1.version: "0.0"
	//</workaround>

	Depends { name: "Qt.quick" }
}

