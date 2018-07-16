#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_LOGGING_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_LOGGING_HPP

#include <cutehmi/loggingMacros.hpp>

Q_DECLARE_LOGGING_CATEGORY(cutehmi_termobot_1_loggingCategory)

namespace cutehmi {
namespace termobot {

inline
const QLoggingCategory & loggingCategory()
{
	return cutehmi_termobot_1_loggingCategory();
}

}
}

#endif
