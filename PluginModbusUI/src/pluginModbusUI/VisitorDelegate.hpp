#ifndef VISITORDELEGATE_H
#define VISITORDELEGATE_H

#include "UIVisitorDelegate.hpp"

#include <base/ProjectModel.hpp>

namespace cutehmi {
namespace pluginModbusUI {

class VisitorDelegate:
	public base::ProjectModel::Node::VisitorDelegate
{
	public:
		VisitorDelegate(QWidget * parentWidget, modbus::Client * client, const QString & clientName);

		widgets::UIVisitorDelegate * ui() override;

	private:
		UIVisitorDelegate m_uiDelegate;
};

}
}

#endif // VISITORDELEGATE_H
