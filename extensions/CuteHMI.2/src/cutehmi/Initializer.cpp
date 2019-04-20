#include <cutehmi/Initializer.hpp>
#include <cutehmi/ErrorInfo.hpp>

namespace cutehmi {

Initializer::Initializer():
	ExtensionInitializer<Initializer>(
		[]() {
			qRegisterMetaType<cutehmi::ErrorInfo>();
		}
	)
{
}

}
