#ifndef CHIPENUMERATOR_HPP
#define CHIPENUMERATOR_HPP

#include "internal/common.hpp"

#include <cutehmi/Singleton.hpp>

#include <QObject>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API ChipEnumerator:
	public QObject,
	public Singleton<ChipEnumerator>
{
	Q_OBJECT

	friend class Singleton<ChipEnumerator>;

	public slots:
		void update();

	private:
		ChipEnumerator();
};

}
}

extern template class cutehmi::Singleton<cutehmi::gpio::ChipEnumerator>;

#endif // CHIPENUMERATOR_HPP
