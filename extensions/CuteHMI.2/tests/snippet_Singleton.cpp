#include <cutehmi/Singleton.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QSignalSpy>

//! [MySingleton class]
class MySingleton:
	public cutehmi::Singleton<MySingleton>
{
		friend class cutehmi::Singleton<MySingleton>;

	public:
		void saySomething()
		{
			qInfo() << "I am not married!";
		}

	protected:
		MySingleton() = default;
};
//! [MySingleton class]

//! [QObject singleton]
class QObjectSingleton:
	public QObject,
	public cutehmi::Singleton<QObjectSingleton>
{
		Q_OBJECT

		friend class cutehmi::Singleton<QObjectSingleton>;

	public:
		void sayQObject()
		{
			qInfo() << "QObject!";
			emit qobjectSaid();
		}

	signals:
		void qobjectSaid();

	protected:
		QObjectSingleton() = default;
};
//! [QObject singleton]

class snippet_Singleton:
	public QObject
{
		Q_OBJECT

	private slots:
		void saySomething();

		void sayQObject();
};

void snippet_Singleton::saySomething()
{
	//! [Call singleton function]
	MySingleton::Instance().saySomething();
	//! [Call singleton function]
}

void snippet_Singleton::sayQObject()
{
	QSignalSpy qobjectSaidSpy(& QObjectSingleton::Instance(), & QObjectSingleton::qobjectSaid);
	QObjectSingleton::Instance().sayQObject();
	QCOMPARE(qobjectSaidSpy.count(), 1);
}


QTEST_MAIN(snippet_Singleton)
#include "snippet_Singleton.moc"

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
