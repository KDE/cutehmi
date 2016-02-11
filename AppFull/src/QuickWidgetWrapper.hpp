#ifndef CUTEHMI_APPFULL_SRC_QUICKWIDGETWRAPPER_HPP
#define CUTEHMI_APPFULL_SRC_QUICKWIDGETWRAPPER_HPP

#include "AbstractQMLWidgetWrapper.hpp"

class QQuickWidget;

/**
 * QQuickWidget wrapper. Provides QQuickWidget based rendering for QML.
 */
class QuickWidgetWrapper:
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

#endif
