#ifndef VISITORDELEGATE_H
#define VISITORDELEGATE_H

#include <base/ProjectModel.hpp>

namespace cutehmi {
namespace pluginModbus {

class VisitorDelegate:
	public base::ProjectModel::Node::VisitorDelegate
{
	public:
		VisitorDelegate(const base::ProjectModel::Node * node);

		void visit(QMLContextPropertyProxy & proxy) override;

	private:
		const base::ProjectModel::Node * m_node;
};

}
}

#endif // VISITORDELEGATE_H
