#include "ErrorBox.hpp"

namespace cutehmi {
namespace widgets {

ErrorBox::ErrorBox(const QString & text, const QString & informativeText, const QString & detailedText, const QString & title):
	m_title(title),
	m_text(text),
	m_informativeText(informativeText),
	m_detailedText(detailedText)
{
}

QString ErrorBox::title() const
{
	return m_title;
}

void ErrorBox::setTitle(const QString & title)
{
	m_title = title;
}

QString ErrorBox::text() const
{
	return m_text;
}

void ErrorBox::setText(const QString & failText)
{
	m_text = failText;
}

QString ErrorBox::informativeText() const
{
	return m_informativeText;
}

void ErrorBox::setInformativeText(const QString & informativeText)
{
	m_informativeText = informativeText;
}

QString ErrorBox::detailedText() const
{
	return m_detailedText;
}

void ErrorBox::setDetailedText(const QString & detailedText)
{
	m_detailedText = detailedText;
}

void ErrorBox::execInfo(base::ErrorInfo errInfo)
{
	if (errInfo.code == base::Error::OK)
		return;

	//<unsolved id="AppFull-6" target="Qt" cause="design">
	// QMessageBox can not be made resizeable in a normal way.
	QMessageBox msgBox;
	//</unsolved>

	execCommon(msgBox, errInfo);

	if (!m_detailedText.isEmpty())
		msgBox.setDetailedText(m_detailedText);

	//<workaround id="AppFull-5" target="Qt" cause="bug">
	// QMessageBox does not make beep sound (at least on Windows XP) (Qt bug?).
	QApplication::beep();
	//</workaround>
	msgBox.exec();
}

void ErrorBox::execExtInfo(base::ExtErrorInfo extErrInfo)
{
	if (extErrInfo.code == base::Error::OK)
		return;

	//<unsolved id="AppFull-6" target="Qt" cause="design">
	// QMessageBox can not be made resizeable in a normal way.
	QMessageBox msgBox;
	//</unsolved>

	execCommon(msgBox, extErrInfo);

	QString detailedText = m_detailedText;
	if (!extErrInfo.details.isEmpty()) {
		if (!m_detailedText.isEmpty())
			detailedText.append("\n\n");
		detailedText.append(extErrInfo.details);
	}
	if (!detailedText.isEmpty())
		msgBox.setDetailedText(detailedText);

	//<workaround id="AppFull-5" target="Qt" cause="bug">
	// QMessageBox does not make beep sound (at least on Windows XP) (Qt bug?).
	QApplication::beep();
	//</workaround>
	msgBox.exec();
}

void ErrorBox::execCommon(QMessageBox & msgBox, base::ErrorInfo & errInfo)
{
	msgBox.setIcon(QMessageBox::Warning);

	QString informativeText = m_informativeText;
	if (!m_text.isEmpty()) {
		msgBox.setText(m_text);
		if (!informativeText.isEmpty())
			informativeText.append("\n\n");
		informativeText.append(errInfo.str);
	} else
		msgBox.setText(errInfo.str);
	if (!informativeText.isEmpty())
		informativeText.append("\n\n");
	informativeText.append(QObject::tr("Error class: %1\nError code: %2.").arg(errInfo.errClass).arg(errInfo.code));
	msgBox.setInformativeText(informativeText);
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
