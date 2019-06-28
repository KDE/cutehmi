#ifndef NAVIERSTOKESSUPGHEAT_HPP
#define NAVIERSTOKESSUPGHEAT_HPP

#include "internal/common.hpp"

#include <cutehmi/Singleton.hpp>

namespace cutehmi {
namespace modfem {

class CUTEHMI_MODFEM_API NavierStokesSUPGHeat:
	public QObject,
	public Singleton<NavierStokesSUPGHeat>
{
	Q_OBJECT

	friend class Singleton<NavierStokesSUPGHeat>;

	public slots:
		void timeIntegration();

	private:
		NavierStokesSUPGHeat();
};

}
}

#endif // NAVIERSTOKESSUPGHEAT_HPP
