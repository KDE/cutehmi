#include "../../include/cutehmi/Singleton.hpp"
#include "../../include/cutehmi/CuteHMI.hpp"

namespace cutehmi {

void destroySingletonInstances()
{
	internal::destroySingletonInstances();
	CuteHMI::Destroy();		// Until CuteHMI is not removed (or extends Singleton).
}

}
