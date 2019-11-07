/**
  This module provides common C++ settings to be used accross Product items.
  */
Module {
//<qbs-cutehmi.cpp-1.workaround target="Qbs" cuase="missing">
// Qbs does not allow Export within Module items. Because of that modules can not export C++ include paths. Workaround is to provide
// a property containing include paths to export (which can be accessed by Module items) and use this property in a product export.
	/**
	  List of include paths to be exported by a product.
	  */
	property stringList exportedIncludePaths: []
//</qbs-cutehmi.cpp-1.workaround>

	Depends { name: "cpp" }

	Properties {
		condition: !qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_NDEBUG", "QT_NO_DEBUG_OUTPUT"])
	}

	cpp.defines: ["QT_DEPRECATED_WARNINGS"]

	cpp.cxxLanguageVersion: "c++14"
}
