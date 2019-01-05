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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
