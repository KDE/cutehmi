#include <cutehmi/services/Initializer.hpp>
#include <cutehmi/services/Serviceable.hpp>

namespace cutehmi {
namespace services {

Initializer::Initializer():
	ExtensionInitializer<Initializer>(
			[]() {
	qRegisterMetaType<cutehmi::services::Serviceable * >();
}
)
{
}

}
}
