#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNAL_SINGLETON_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNAL_SINGLETON_HPP

namespace cutehmi {
namespace internal {

typedef void(*singletonDestroyCallback)();

void destroySingletonInstances();

void storeSingletonDestroyCallback(singletonDestroyCallback callback);

void removeSingletonDestroyCallback(singletonDestroyCallback callback);

}
}

#endif
