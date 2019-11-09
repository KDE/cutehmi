/**
  This module is provided mainly as a workaround to propagate information about disabled products to their dependencies.
 */
Module {
//<qbs-cutehmi.product-1.workaround target="Qbs" cause="missing">
	/**
	  Whether product is enabled. Use this property to signal that product should not be build.
	  */
	property bool enabled: cutehmi.product.disabledProducts.length == 0

	/**
	  A list of disabled products. This list propagates to dependent items, thus each product has a list of disabled products it
	  depends on.
	  */
	property stringList disabledProducts: []

	validate: {
		if (!product.builtByDefault) {
			var message = "Product '" + product.name + "' will not be built by default"
			if (product.cutehmi.product.disabledProducts.length)
				message += ', because following products it depends on are not built by default: ' + product.cutehmi.product.disabledProducts
			console.info(message + ".")
		}
	}
//</qbs-cutehmi.product-1.workaround>
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
