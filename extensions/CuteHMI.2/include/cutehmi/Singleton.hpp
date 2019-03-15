#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_SINGLETON_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_SINGLETON_HPP

#include "NonCopyable.hpp"
#include "NonMovable.hpp"
#include "internal/common.hpp"
#include "internal/singleton.hpp"

#include <functional>
#include <memory>

namespace cutehmi {

/**
 * %Singleton template. It may be necessary to make derived class a friend of inheriting class to grant Singleton<C> access to its
 * constructor.
 */
template <class C>
class Singleton:
	public NonCopyable,
	public NonMovable
{
	public:
		/**
		 * Get instance. Returns a reference to the instance of the singleton class. Object is instantiated upon first call of this
		 * function.
		 * @return a reference to the instance of the singleton class.
		 *
		 * @warning because this class can be inherited by QObject, destroySingletonInstances() function should be used by front-end
		 * application to satisfy the requirement that QApplication has to be first created and last destroyed QObject.
		 *
		 * @warning if neither Destroy() function nor destroySingletonInstances() has been used, then destructor will be called on
		 * static de-initialization. Beware of using singleton instance in destructor of some other static object. If that's
		 * unavoidable, assure that singletons or any static objects are constructed in the reverse order they are going to be
		 * destructed.
		 */
		static C & Instance();

		/**
		 * Destroy instance. This function is provided to satisfy the requirement that QApplication has to be first created and last
		 * destroyed QObject. Once this function is called singleton becomes unusable.
		 *
		 * @note Only frontend applications, which instantiate QApplication should take care about this function.
		 *
		 * @note Typically it is better to use destroySingletonInstances() function, which destroys all singletons, that inherit
		 * after this class, at once.
		 *
		 * @assumption{cutehmi::Singleton-singleton_class_will_not_call_Destroy_from_destructor}
		 * Class that inherits after Singleton will not call Destroy() functions from its destructor (neither its own nor of another
		 * class).
		 *
		 * @see destroySingletonInstances().
		 */
		static void Destroy();

	protected:
		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a Singleton instance.
	
		/**
		 * Default constructor.
		 */
		Singleton();
	
		/**
		 * Destructor.
		 */
		virtual ~Singleton();

		/**
		 * Get instance pointer.
		 * @return instance pointer.
		 *
		 * @note This is provided as a workaround (CuteHMI-2.workaround).
		 */
		static std::unique_ptr<C> & InstancePtr();
};

/**
 * Destroy singleton instances. This function is provided to satisfy the requirement that QApplication has to be first created and
 * last destroyed QObject. It destroys all singletons that inherit after Singleton class template. Once this function is called
 * singletons become unusable.
 *
 * @note Only frontend applications, which instantiate QApplication should take care about this function.
 *
 * @principle{cutehmi::destroySingletonInstances-determined_destruction_order}
 * Singleton instances will be destroyed in reverse order as they were instantiated, that is singletons for which
 * Singleton::Instance() function has been called first will be destroyed last.
 */
CUTEHMI_API void destroySingletonInstances();


template <class C>
Singleton<C>::Singleton()
{
	internal::storeSingletonDestroyCallback(& Singleton<C>::Destroy);
}

template <class C>
Singleton<C>::~Singleton()
{
	internal::removeSingletonDestroyCallback(& Singleton<C>::Destroy);
}

template <class C>
C & Singleton<C>::Instance()
{
	//<CuteHMI-2.workaround target="std" cause="design">
	// Function std::unique_ptr::reset() sets internal pointer to nullptr and only after that it will delete its contents. This
	// causes error, when managed object still needs to be accessed through std::unique_ptr::get() function by members of managed
	// object during their destruction.  Workaround is to use additional raw pointer. In general this prevents std::unique_ptr from
	// being used in inconsistent state (calling std::unique_ptr::get() while inside std::unique_ptr::reset()).
	static C * instancePtr = InstancePtr().get();
	return *instancePtr;
	//</CuteHMI-2.workaround>
}

template <class C>
void Singleton<C>::Destroy()
{
	//<CuteHMI-2.workaround>
	// A bit paranoic, but if Instance() wasn't called before, it would point to nullptr. What if it is used by a dtor of one of the
	// members of managed object? After InstancePtr().reset(), std::unique_ptr::reset() first sets internal pointer to nullptr, then
	// calls destructor (hence Instance() would point to nullptr during destruction).
	Instance();
	//</CuteHMI-2.workaround>
	InstancePtr().reset();
}

template <class C>
std::unique_ptr<C> & Singleton<C>::InstancePtr()
{
	static std::unique_ptr<C> instance(new C);
	return instance;
}

}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
