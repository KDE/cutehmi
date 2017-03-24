#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_PLUGIN_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_PLUGIN_HPP

#include "internal/common.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Plugin:
	public QObject
{
	Q_OBJECT

	public:
		struct MetaData
		{
			QString id;
			QString name;
			QString version;
		};

		Plugin(const QString & binary, QObject * instance, const cutehmi::base::Plugin::MetaData & metaData, QObject * parent = 0);

		const QString & binary() const;

		QObject * instance();

		const QString & id() const;

		const QString & name() const;

		const QString & version() const;

	private:
		struct Members
		{
			QString binary;
			QObject * instance;
			MetaData metaData;
		};

		std::unique_ptr<Members> m;
};

}
}

#endif
