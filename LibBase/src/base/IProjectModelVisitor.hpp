#ifndef CUTEHMI_LIBBASE_SRC_PLUGIN_IPROJECTMODELVISITOR_HPP
#define CUTEHMI_LIBBASE_SRC_PLUGIN_IPROJECTMODELVISITOR_HPP

#include "../platform.hpp"
#include "../base/ProjectModel.hpp"

#include <QtPlugin>

namespace cutehmi {
namespace base {

/**
 * Project model visitor interface.
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
}

#endif
