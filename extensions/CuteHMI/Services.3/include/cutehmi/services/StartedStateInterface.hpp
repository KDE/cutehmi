#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STARTEDSTATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STARTEDSTATEINTERFACE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QAbstractState>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API StartedStateInterface:
	public QObject
{
		Q_OBJECT

		friend class StateInterface;

	public:
		Q_PROPERTY(QAbstractState * yielding READ yielding NOTIFY yieldingChanged)

		Q_PROPERTY(QAbstractState * active READ active NOTIFY activeChanged)

		Q_PROPERTY(QAbstractState * idling READ idling NOTIFY idlingChanged)

		QAbstractState * yielding() const;

		QAbstractState * active() const;

		QAbstractState * idling() const;

	signals:
		void yieldingChanged();

		void activeChanged();

		void idlingChanged();

	protected:
		StartedStateInterface(QObject * parent = nullptr);

		void setYielding(QAbstractState * yielding);

		void setActive(QAbstractState * active);

		void setIdling(QAbstractState * idling);

	private:
		struct Members {
			QAbstractState * yielding;
			QAbstractState * active;
			QAbstractState * idling;
		};

		MPtr<Members> m;
};

}
}

#endif
