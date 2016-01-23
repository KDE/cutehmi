#ifndef CUTEHMI_LIBBASE_SRC_BASE_IPLCCLIENTPLUGIN_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_IPLCCLIENTPLUGIN_HPP

#include <QtPlugin>

namespace base {

class IPLCClientPlugin
{
	public:

	protected:
		virtual ~IPLCClientPlugin() = default;

		IPLCClientPlugin() = default;
};

}

#endif
