import qbs

Product {
	targetName: qbs.buildVariant.contains("debug") ? name + "d" : name

	property stringList buildDefines: ["QT_DEPRECATED_WARNINGS"]

	property string vendor					///< Product vendor.

	property string friendlyName			///< Descriptive product name for ordinary humans.

	property string description				///< Product description.

	property string author					///< Author(s).

	property string copyright				///< Copyright holder(s).

	property string license					///< License(s).

	property string baseName

	property int major

	property int minor

	property int micro

	Properties {
		condition: qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_DEBUG"]).concat(buildDefines)
	}

	Properties {
		condition: !qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_RELEASE", "QT_NO_DEBUG_OUTPUT"]).concat(buildDefines)
	}
}
