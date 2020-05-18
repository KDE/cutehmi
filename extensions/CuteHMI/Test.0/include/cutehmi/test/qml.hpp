#ifndef QML_HPP
#define QML_HPP

#include "internal/common.hpp"

class QQmlEngine;

namespace cutehmi {
namespace test {

void CUTEHMI_TEST_API setupScreenshotDirs(const char * projectRelativePath, QQmlEngine * engine);

}
}

#endif // QML_HPP
