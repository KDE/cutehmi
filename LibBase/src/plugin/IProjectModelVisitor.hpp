#ifndef CUTEHMI_LIBBASE_SRC_PLUGIN_IPROJECTMODELVISITOR_HPP
#define CUTEHMI_LIBBASE_SRC_PLUGIN_IPROJECTMODELVISITOR_HPP

#include "../platform.hpp"
#include "../base/ProjectModel.hpp"

#include <QtPlugin>

namespace plugin {

/**
 * @todo gather all GUI plugin interfaces into IGUIPlugin.
 */
class IProjectModelVisitor
{
	public:
		virtual void visit(base::ProjectModel::Node & node) = 0;

	protected:
		virtual ~IProjectModelVisitor() = default;

		IProjectModelVisitor() = default;
};

}

Q_DECLARE_INTERFACE(plugin::IProjectModelVisitor, "CuteHMI.Plugin.IProjectModelVisitor")

#endif
