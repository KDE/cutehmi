#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP

#include "internal/common.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-5.workaround target="Qt" cause="Qt5">

#include <cutehmi/workarounds/qt5compatibility/cutehmiQt6MocInclude.hpp>

namespace cutehmi {
namespace services {

class AbstractService;

}
}

CUTEHMI_QT6_MOC_INCLUDE("AbstractService.hpp")

//</CuteHMI.Workarounds.Qt5Compatibility-5.workaround>


#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

/**
 * Abstract service controller.
 *
 * In general service controller is an object that can do arbitrary things with a service that is managed by it. In practice
 * controller is typically responsible for calling appropriate service slots at particular events or at specific time. A controller
 * object is not bound to a single service, it can manage multiple services.
 */
class CUTEHMI_SERVICES_API AbstractServiceController:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractServiceController)
		QML_UNCREATABLE("AbstractServiceController is an abstract class")

	public:
		Q_INVOKABLE virtual void subscribe(cutehmi::services::AbstractService * service) = 0;

		Q_INVOKABLE virtual void unsubscribe(cutehmi::services::AbstractService * service) = 0;

	protected:
		explicit AbstractServiceController(QObject * parent = nullptr);
};

}
}

#endif

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
