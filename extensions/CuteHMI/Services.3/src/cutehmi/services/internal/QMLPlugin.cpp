#include "QMLPlugin.hpp" // IWYU pragma: keep

//<Doxygen-3.workaround target="Doxygen" cause="missing">
#ifdef DOXYGEN_WORKAROUND

namespace CuteHMI {
namespace Services {

/**
 * Exposes cutehmi::services::AbstractService to QML.
 */
class AbstractService: public cutehmi::services::AbstractService {};

/**
 * Exposes cutehmi::services::AbstractServiceController to QML.
 */
class AbstractServiceController: public cutehmi::services::AbstractServiceController {};

/**
 * Exposes cutehmi::services::SelfService to QML.
 */
class SelfService: public cutehmi::services::SelfService {};

/**
 * Exposes cutehmi::services::Service to QML.
 */
class Service: public cutehmi::services::Service {};

/**
 * Exposes cutehmi::services::ServiceAutoActivate to QML.
 */
class ServiceAutoActivate: public cutehmi::services::ServiceAutoActivate {};

/**
 * Exposes cutehmi::services::ServiceAutoRepair to QML.
 */
class ServiceAutoRepair: public cutehmi::services::ServiceAutoRepair {};

/**
 * Exposes cutehmi::services::ServiceAutoStart to QML.
 */
class ServiceAutoStart: public cutehmi::services::ServiceAutoStart {};

/**
 * Exposes cutehmi::services::ServiceDependency to QML.
 */
class ServiceDependency: public cutehmi::services::ServiceDependency {};

/**
 * Exposes cutehmi::services::ServiceGroup to QML.
 */
class ServiceGroup: public cutehmi::services::ServiceGroup {};

/**
 * Exposes cutehmi::services::ServiceGroupRule to QML.
 */
class ServiceGroupRule: public cutehmi::services::ServiceGroupRule {};

/**
 * Exposes cutehmi::services::StartedStateInterface to QML.
 */
class StartedStateInterface: public cutehmi::services::StartedStateInterface {};

/**
 * Exposes cutehmi::services::StateInterface to QML.
 */
class StateInterface: public cutehmi::services::StateInterface {};

}
}

#endif
//</Doxygen-3.workaround>

namespace cutehmi {
namespace services {
namespace internal {

}
}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
