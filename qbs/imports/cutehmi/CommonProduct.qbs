import qbs

Product {
	targetName: qbs.buildVariant.contains("debug") ? name + "d" : name

	property stringList buildDefines: ["QT_DEPRECATED_WARNINGS"]

	Properties {
		condition: qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_DEBUG"]).concat(buildDefines)
	}

	Properties {
		condition: !qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_RELEASE", "QT_NO_DEBUG_OUTPUT"]).concat(buildDefines)
	}
}
