#include "../../../include/cutehmi/internal/singleton.hpp"

#include <QList>

namespace  {
	class SingletonDestroyWrapper
	{
		public:
			SingletonDestroyWrapper(cutehmi::internal::singletonDestroyCallback callback):
				m_callback(callback)
			{
			}

			[[gnu::unused]]
			bool operator ==(const SingletonDestroyWrapper & other) const
			{
				return m_callback == other.m_callback;
			}

			void call()
			{
				m_callback();
			}

			operator uintptr_t() const
			{
				return reinterpret_cast<uintptr_t>(m_callback);
			}

		private:
			cutehmi::internal::singletonDestroyCallback m_callback;
	};

	[[gnu::unused]]
	uint qHash(const SingletonDestroyWrapper & key)
	{
		return ::qHash(static_cast<uintptr_t>(key));
	}

	//<cutehmi::destroySingletonInstances-determined_destruction_order.principle>
	// Container should prserve order in which elements were added, so that singletons can be destroyed in reverse order as they
	// were added. This disqualifies QSet.

	typedef QList<SingletonDestroyWrapper> SingletonDestroyFunctionsContainer;

	// Elements are prpeneded to this list (see storeSingletonDestroyCallback()).
	SingletonDestroyFunctionsContainer singletonDestroyFunctions;

	//</cutehmi::destroySingletonInstances-determined_destruction_order.principle>
}

namespace cutehmi {
namespace internal {

void destroySingletonInstances()
{
	//<cutehmi::destroySingletonInstances-determined_destruction_order.principle>
	SingletonDestroyFunctionsContainer copy = singletonDestroyFunctions;
	//<cutehmi::Singleton-singleton_class_will_not_call_Destroy_from_destructor.assumption>
	// If Singleton called Destroy() it would invalidate copy and its iterators.
	for (auto it = copy.begin(); it != copy.end(); ++it)
		it->call();		// Call Singleton::Destroy(), which will remove callback from original singletonDestroyFunctions.
	//</cutehmi::Singleton-singleton_class_will_not_call_Destroy_from_destructor.assumption>
	//</cutehmi::destroySingletonInstances-determined_destruction_order.principle>
}

void storeSingletonDestroyCallback(singletonDestroyCallback callback)
{
	//<cutehmi::destroySingletonInstances-determined_destruction_order.principle>
	// Callbacks should be removed in reverse order as they were added.	With prepending removeSingletonDestroyCallback() should be
	// able to remove callbacks pretty fast, if accessed through destroySingletonInstances(), because QList::removeOne() will find
	// each removed callback at the beginning of the list.
	singletonDestroyFunctions.prepend(callback);
	//</cutehmi::destroySingletonInstances-determined_destruction_order.principle>
}

void removeSingletonDestroyCallback(singletonDestroyCallback callback)
{
	singletonDestroyFunctions.removeOne(callback);
}

}
}

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
