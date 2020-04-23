#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLENAMETRAITS_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLENAMETRAITS_HPP

#include <QString>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

template <typename T>
struct TableNameTraits
{
	static QString Affixed(const QString & name);
};

template <>
struct TableNameTraits<double>
{
	static QString Affixed(const QString & name) {
		return name + "_real";
	}
};

template <>
struct TableNameTraits<int>
{
	static QString Affixed(const QString & name) {
		return name + "_int";
	}
};

template <>
struct TableNameTraits<bool>
{
	static QString Affixed(const QString & name) {
		return name + "_bool";
	}
};

}
}
}

#endif
