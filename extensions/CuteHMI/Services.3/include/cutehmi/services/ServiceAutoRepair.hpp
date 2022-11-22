#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEAUTOREPAIR_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEAUTOREPAIR_HPP

#include "internal/common.hpp"

#include "AbstractServiceController.hpp"

#include <QHash>

#include <memory>

class QAbstractState;
class QTimer;

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceAutoRepair:
	public cutehmi::services::AbstractServiceController
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceAutoRepair)

	public:
		static constexpr int INITIAL_INITIAL_INTERVAL = 10000;

		static constexpr const char * INITIAL_INTERVAL_FUNCTION = "(function (previousInterval) { return previousInterval; })";

		Q_PROPERTY(int initialInterval READ initialInterval WRITE setInitialInterval NOTIFY initialIntervalChanged)

		Q_PROPERTY(QJSValue intervalFunction READ intervalFunction WRITE setIntervalFunction NOTIFY intervalFunctionChanged)

		explicit ServiceAutoRepair(QObject * parent = nullptr);

		~ServiceAutoRepair() override;

		QJSValue intervalFunction() const;

		int initialInterval() const;

		void setInitialInterval(int initialInterval);

		void setIntervalFunction(const QJSValue & intervalFunction);

		void setIntervalFunction(const QString & intervalFunction);

		void subscribe(AbstractService * service) override;

		void unsubscribe(AbstractService * service) override;

	signals:
		void initialIntervalChanged();

		void intervalFunctionChanged();

	private:
		struct ServiceEntry {
			QTimer * timer;
			QMetaObject::Connection startingEnteredConnection;
			QMetaObject::Connection startingChangedConnection;
			QMetaObject::Connection startedEnteredConnection;
			QMetaObject::Connection startedChangedConnection;
			QMetaObject::Connection repairingEnteredConnection;
			QMetaObject::Connection repairingChangedConnection;
			QMetaObject::Connection brokenEnteredConnection;
			QMetaObject::Connection brokenChangedConnection;
		};

		typedef QHash<AbstractService *, ServiceEntry *> ServiceDataContainer;

		// Helper engine to evaulate interval strings (QJSEngine related to QJSValue must available when QJSValue::call() is made).
		static QJSEngine & JSEngine();

		QMetaObject::Connection connectResetIntervalOnStateEntered(const QAbstractState * state, QTimer * timer);

		QMetaObject::Connection connectRepairingEntered(const AbstractService * service, QTimer * timer);

		QMetaObject::Connection connectBrokenEntered(const AbstractService * service, QTimer * timer);

		void clearServiceEntry(AbstractService * service);

		struct Members {
			int initialInterval;
			QJSValue intervalFunction;
			ServiceDataContainer serviceData;
		};

		MPtr<Members> m;
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
