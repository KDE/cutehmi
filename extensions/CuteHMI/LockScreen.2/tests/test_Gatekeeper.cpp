#include <cutehmi/lockscreen/Gatekeeper.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace lockscreen {

class test_Gatekeeper:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void pickNumberOfHashes();

		void authenticate();

	private:
		std::unique_ptr<Gatekeeper> m_gatekeeper;
};

void test_Gatekeeper::initTestCase()
{
	m_gatekeeper = std::make_unique<Gatekeeper>();
}

void test_Gatekeeper::pickNumberOfHashes()
{
	int low = cutehmi::test::rand<int>();
	int high = cutehmi::test::rand<int>();

	CUTEHMI_INFO("Warnings are OK, if random number is out of range. Gatekeeper should sanitize wrong values.");
	m_gatekeeper->setHashesLow(low);
	m_gatekeeper->setHashesHigh(high);

	int numberOfHashes = m_gatekeeper->pickNumberOfHashes();

	QVERIFY2(numberOfHashes >= m_gatekeeper->hashesLow(), qPrintable(QString("returned value: %1, given lower bound: %2").arg(numberOfHashes).arg(m_gatekeeper->hashesLow())));
	QVERIFY2(numberOfHashes <= m_gatekeeper->hashesHigh(), qPrintable(QString("returned value: %1, given upper bound: %2").arg(numberOfHashes).arg(m_gatekeeper->hashesHigh())));
}

void test_Gatekeeper::authenticate()
{
	// Pick some reasonable amount of hashes.
	int low = cutehmi::test::rand<int>(1000, 10000);
	int high = cutehmi::test::rand<int>(low, 10000);

	m_gatekeeper->setHashesLow(low);
	m_gatekeeper->setHashesHigh(high);

	m_gatekeeper->setSecret(QByteArray());
	QVERIFY(m_gatekeeper->authenticate());

	QString password = cutehmi::test::rand<QString>();
	m_gatekeeper->setPassword(password);
	QByteArray secret = m_gatekeeper->makeSecret(password);
	m_gatekeeper->setSecret(secret);
	QVERIFY(m_gatekeeper->authenticate());

	// Get rid of improbable, but possible collision.
	do {
		password = cutehmi::test::rand<QString>();
	} while (m_gatekeeper->makeSecret(password) == m_gatekeeper->secret());
	m_gatekeeper->setPassword(password);
	QVERIFY(!m_gatekeeper->authenticate());
}

}
}

QTEST_MAIN(cutehmi::lockscreen::test_Gatekeeper)
#include "test_Gatekeeper.moc"

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
