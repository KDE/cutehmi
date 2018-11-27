import qbs

Product {
	targetName: qbs.buildVariant.contains("debug") ? name + "d" : name

	cpp.defines: ["QT_DEPRECATED_WARNINGS"]

	property string cutehmiType: "product"	///< CuteHMI product type.

	property string vendor					///< Product vendor.

	property string friendlyName			///< Descriptive product name for ordinary humans.

	property string description				///< Product description.

	property string author					///< Author(s).

	property string copyright				///< Copyright holder(s).

	property string license					///< License(s).

	property string baseName				///< Base name of the product (without the major version suffix).

	property int major						///< Major version number.

	property int minor						///< Minor version number (deprecated).

	property int micro						///< Micro version number (deprecated).

	Properties {
		condition: qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_DEBUG"])
	}

	Properties {
		condition: !qbs.buildVariant.contains("debug")
		cpp.defines: outer.concat(["CUTEHMI_RELEASE", "QT_NO_DEBUG_OUTPUT"])
	}

	Depends { name: "cpp" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
