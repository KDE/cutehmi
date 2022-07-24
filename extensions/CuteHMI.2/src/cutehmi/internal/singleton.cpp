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

// Elements are prepended to this list (see storeSingletonDestroyCallback()).
SingletonDestroyFunctionsContainer & singletonDestroyFunctions() {
	static SingletonDestroyFunctionsContainer container;
	return container;
}
//</cutehmi::destroySingletonInstances-determined_destruction_order.principle>

}

namespace cutehmi {
namespace internal {

void destroySingletonInstances()
{
	//<cutehmi::destroySingletonInstances-determined_destruction_order.principle>
	SingletonDestroyFunctionsContainer copy = singletonDestroyFunctions();
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
	singletonDestroyFunctions().prepend(callback);
	//</cutehmi::destroySingletonInstances-determined_destruction_order.principle>
}

void removeSingletonDestroyCallback(singletonDestroyCallback callback)
{
	singletonDestroyFunctions().removeOne(callback);
}

}
}

//(c)C: Copyright © 2019-2022, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
