#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_QML_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_QML_HPP

#include "internal/common.hpp"

class QQmlEngine;

namespace cutehmi {
namespace test {

void CUTEHMI_TEST_API setupScreenshotDirs(const char * projectRelativePath, QQmlEngine * engine);

}
}

#endif
