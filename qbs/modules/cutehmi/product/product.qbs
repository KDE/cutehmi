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
