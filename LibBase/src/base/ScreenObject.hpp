#ifndef CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP

#include "../platform.hpp"

#include <QObject>

namespace base {

class CUTEHMI_BASE_API ScreenObject:
	public QObject
{
	Q_OBJECT

	public:
		ScreenObject(const QString & source, QObject * parent = 0);

		virtual ~ScreenObject() = default;

		QString source() const;

	private:
		QString m_source;
};

}

#endif
