#ifndef LOGGINGCATEGORYCHECK_HPP
#define LOGGINGCATEGORYCHECK_HPP

#include "platform.hpp"
#include "../metadata.hpp"

#include <QtDebug>
#include <QLoggingCategory>

namespace cutehmi {
namespace internal {

/**
 * Logging category check.
 */
class CUTEHMI_API LoggingCategoryCheck
{
	public:
		explicit LoggingCategoryCheck(const QLoggingCategory & loggingCategory);
};

inline
LoggingCategoryCheck::LoggingCategoryCheck(const QLoggingCategory & loggingCategory)
{
	if (!loggingCategory.isInfoEnabled()
#ifndef CUTEHMI_NDEBUG
			|| !loggingCategory.isDebugEnabled()
#endif
			|| !loggingCategory.isWarningEnabled()
			|| !loggingCategory.isCriticalEnabled())
		qCWarning(QLoggingCategory(CUTEHMI_NAME ".LoggingCategoryCheck")).nospace().noquote() << "Logging for category '" << loggingCategory.categoryName() << "' has been disabled!";
}

}
}

#endif // LOGGINGCATEGORYCHECK_HPP
