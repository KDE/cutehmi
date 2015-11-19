#ifndef CUTEHMI_LIBBASE_SRC_UTILS_SINGLETON_HPP
#define CUTEHMI_LIBBASE_SRC_UTILS_SINGLETON_HPP

#include "NonCopyable.hpp"
#include "NonMovable.hpp"

namespace utils {

/**
 * Singleton template. It may be necessary to make derived class a friend of
 * inheriting class to grant Singleton<C> access to its constructor.
 */
template <class C>
class Singleton:
		public NonCopyable,
		public NonMovable
{
	public:
		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * @return a reference to the instance of the singleton class.
		 *
		 * @warning destructor will be called on static de-initialization. Beware of
		 * using singleton instance in destructor of some other static object. If
		 * that's unavoidable, assure that singletons or any static objects are
		 * constructed in the reverse order they are going to be destructed.
		 */
		static C & Instance()
		{
			static C instance;
			return instance;
		}

	protected:
		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a Singleton instance.
	
		/**
		 * Default constructor.
		 */
		Singleton() = default;
	
		/**
		 * Destructor.
		 */
		virtual ~Singleton() = default;
};

}

#endif
