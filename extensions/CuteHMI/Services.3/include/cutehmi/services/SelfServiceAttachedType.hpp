#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SELFSERVICEATTACHEDTYPE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SELFSERVICEATTACHEDTYPE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API SelfServiceAttachedType:
	public QObject
{
		Q_OBJECT
		QML_ANONYMOUS

		Q_PROPERTY(QString status READ status WRITE setStatus RESET resetStatus NOTIFY statusChanged)

	public:
		explicit SelfServiceAttachedType(QObject * parent = nullptr);

		QString status() const;

		void setStatus(const QString & status);

		void resetStatus();

	signals:
		void statusChanged();

	private:
		struct Members {
			QString status;
		};

		MPtr<Members> m;
};

}
}

#endif
