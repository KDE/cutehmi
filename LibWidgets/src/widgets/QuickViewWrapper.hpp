#ifndef CUTEHMI_LIBWIDGETS_SRC_WIDGETS_QUICKVIEWWRAPPER_HPP
#define CUTEHMI_LIBWIDGETS_SRC_WIDGETS_QUICKVIEWWRAPPER_HPP

#include "AbstractQMLWidgetWrapper.hpp"

class QQuickView;

namespace cutehmi {
namespace widgets {

/**
 * QQuickView wrapper. Provides QQuickView based rendering for QML.
 */
class CUTEHMI_WIDGETS_API QuickViewWrapper:
	public AbstractQMLWidgetWrapper
{
	typedef AbstractQMLWidgetWrapper Parent;

	public:
		QuickViewWrapper(QWidget * parent);

		QWidget * widget() const override;

		QQuickItem * contentItem() const override;

	private:
		QQuickView * m_quickView;
		QWidget * m_widget;
};

}
}

#endif
