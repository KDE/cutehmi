#ifndef CUTEHMI_APPFULL_SRC_QUICKVIEWWRAPPER_HPP
#define CUTEHMI_APPFULL_SRC_QUICKVIEWWRAPPER_HPP

#include "AbstractQMLWidgetWrapper.hpp"

class QQuickView;

namespace cutehmi {

/**
 * QQuickView wrapper. Provides QQuickView based rendering for QML.
 */
class QuickViewWrapper:
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

#endif
