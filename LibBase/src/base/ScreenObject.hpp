#ifndef CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SCREENOBJECT_HPP

#include "../platform.hpp"

#include <QObject>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API ScreenObject:
	public QObject
{
	Q_OBJECT

	public:
		ScreenObject(const QString & source, bool def = false, QObject * parent = 0);

		virtual ~ScreenObject() = default;

		QString source() const;

		void setSource(const QString & source);

		bool isDefault() const;

		void setDefault(bool def);

	private:
		QString m_source;
		bool m_default;
};

}
}

#endif
