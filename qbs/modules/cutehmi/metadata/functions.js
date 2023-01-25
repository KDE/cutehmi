function versionString(product)
{
	if (product.cutehmiType !== undefined)
		return product.major + "." + product.minor + "." + product.micro + (product.hash !== "" ? "." + product.hash : "")
	else
		return product.version
}
