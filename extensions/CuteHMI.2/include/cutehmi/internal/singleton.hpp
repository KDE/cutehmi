#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace cutehmi {
namespace internal {

typedef void(*singletonDestroyCallback)();

void destroySingletonInstances();

void storeSingletonDestroyCallback(singletonDestroyCallback callback);

void removeSingletonDestroyCallback(singletonDestroyCallback callback);

}
}

#endif // SINGLETON_HPP
