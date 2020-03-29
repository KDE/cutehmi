#include <cutehmi/Singleton.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

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
};
//! [MySingleton class]

class snippet_Singleton:
	public QObject
{
		Q_OBJECT

	private slots:
		void saySomething();
};

void snippet_Singleton::saySomething()
{
	//! [Call singleton function]
	MySingleton::Instance().saySomething();
	//! [Call singleton function]
}

QTEST_MAIN(snippet_Singleton)
#include "snippet_Singleton.moc"

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
