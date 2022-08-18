#include <QQmlEngine>

namespace cutehmi {
namespace workarounds {
namespace windeployqt {
namespace internal {

// Some symbols must be exported in order to create a dependency on Qt.Qml.
Q_DECL_EXPORT const QQmlEngine & dummy() {
	static const QQmlEngine e;
	return e;
}

}
}
}
}
