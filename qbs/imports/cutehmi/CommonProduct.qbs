import qbs

/**
  Common product. Defines common properties for all CuteHMI product types.
  */
Product {
	targetName: qbs.buildVariant.contains("debug") ? name + "d" : name

	//<qbs-imports-cutehmi-1.workaround target="Qbs" cause="design">
	// Using 'builtByDefault' instead of 'condition', because products with condition set to false are not evaluated at all, which
	// gives no chance to propagate condition accross dependencies.
	builtByDefault: cutehmi.product.disabledProducts.length == 0 && cutehmi.product.enabled
	//</qbs-imports-cutehmi-1.workaround>

	property string cutehmiType: "product"	///< CuteHMI product type.

	property string vendor					///< Product vendor.

	property string domain					///< Organization domain.

	property string friendlyName			///< Descriptive product name for ordinary humans.

	property string description				///< Short product description.

	property string baseName				///< Base name of the product (without the major version suffix).

	property int major						///< Major version number.

	property int minor: 0					///< Minor version number.

	property int micro: 0					///< Micro version number.

	property bool i18n: false				///< Indicates whether translations should be loaded for this product.

	//<qbs-cutehmi.product-1.workaround target="Qbs" cause="missing">

	Export {
		Depends { name: "cutehmi.product" }
		Properties {
			//<qbs-imports-cutehmi-1.workaround target="Qbs" cause="design">
			condition: !exportingProduct.builtByDefault
			//</qbs-imports-cutehmi-1.workaround>
			cutehmi.product.disabledProducts: exportingProduct.name
		}
	}

	Depends { name: "cutehmi.product" }

	//</qbs-cutehmi.product-1.workaround>
}

//(c)C: Copyright © 2018-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
