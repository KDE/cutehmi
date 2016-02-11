#ifndef CUTEHMI_LIBBASE_SRC_BASE_SCREENVISITORDELEGATE_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SCREENVISITORDELEGATE_HPP

#include "ProjectModel.hpp"

namespace base {

class CUTEHMI_BASE_API ScreenVisitorDelegate:
	public ProjectModel::Node::VisitorDelegate
{
	public:
		ScreenVisitorDelegate(const base::ProjectModel::Node * node);

		void visit(QQmlComponent & component) override;

	private:
		const base::ProjectModel::Node * m_node;
};

}

#endif
