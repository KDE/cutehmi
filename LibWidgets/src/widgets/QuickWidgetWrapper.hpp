#ifndef CUTEHMI_LIBWIDGETS_SRC_WIDGETS_QUICKWIDGETWRAPPER_HPP
#define CUTEHMI_LIBWIDGETS_SRC_WIDGETS_QUICKWIDGETWRAPPER_HPP

#include "AbstractQMLWidgetWrapper.hpp"

class QQuickWidget;

namespace cutehmi {
namespace widgets {

/**
 * QQuickWidget wrapper. Provides QQuickWidget based rendering for QML.
 */
class CUTEHMI_WIDGETS_API QuickWidgetWrapper:
	public AbstractQMLWidgetWrapper
{
	typedef AbstractQMLWidgetWrapper Parent;

	public:
		QuickWidgetWrapper(QWidget * parent);

		QWidget * widget() const override;

		QQuickItem * contentItem() const override;

	private:
		QQuickWidget * m_quickWidget;
};

}
}

#endif
