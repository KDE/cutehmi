/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef H_EXTENSIONS_CUTEHMI_WORKAROUNDS_QT_LABS_SETTINGS_1_SRC_CUTEHMI_WORKAROUNDS_QT_LABS_SETTINGS_INTERNAL_QQMLSETTINGS_u_P_H
#define H_EXTENSIONS_CUTEHMI_WORKAROUNDS_QT_LABS_SETTINGS_1_SRC_CUTEHMI_WORKAROUNDS_QT_LABS_SETTINGS_INTERNAL_QQMLSETTINGS_u_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQml/qqml.h>
#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtQml/qqmlparserstatus.h>
#include <QQmlEngine>

namespace cutehmi {
namespace workarounds {
namespace qt {
namespace labs {
namespace settings {
namespace internal {

class QQmlSettingsPrivate;

class QQmlSettings : public QObject, public QQmlParserStatus
{
		Q_OBJECT
		Q_INTERFACES(QQmlParserStatus)
		QML_NAMED_ELEMENT(Settings)

		Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged FINAL)

		Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged FINAL)

	public:
		explicit QQmlSettings(QObject * parent = nullptr);
		~QQmlSettings() override;

		QString category() const;
		void setCategory(const QString & category);

		QString fileName() const;
		void setFileName(const QString & fileName);

		Q_INVOKABLE QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;
		Q_INVOKABLE void setValue(const QString & key, const QVariant & value);
		Q_INVOKABLE void sync();

		// CuteHMI extra methods:
		Q_INVOKABLE void remove(const QString & key);
		Q_INVOKABLE void clear();
		Q_INVOKABLE QVariant getOrSet(const QString & key, const QVariant & defaultValue);

	signals:
		void categoryChanged();

		void fileNameChanged();

	protected:
		void timerEvent(QTimerEvent * event) override;

		void classBegin() override;
		void componentComplete() override;

	private:
		Q_DISABLE_COPY(QQmlSettings)
		Q_DECLARE_PRIVATE(QQmlSettings)
		QScopedPointer<QQmlSettingsPrivate> d_ptr;
		Q_PRIVATE_SLOT(d_func(), void _q_propertyChanged())
};

}
}
}
}
}
}

QML_DECLARE_TYPE(cutehmi::workarounds::qt::labs::settings::internal::QQmlSettings)

#endif

//(c)C: Copyright © 2021-2023, Michał Policht <michal@policht.pl>, The Qt Company Ltd <sales@qt.io>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR GPL-2.0-or-later
//(c)C: CuteHMI.Workarounds.Qt.labs.settings.1 extension is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version approved by the KDE Free Qt Foundation.
//(c)C: This file is a part of CuteHMI.Workarounds.Qt.labs.settings.1 extension.
//(c)C: Additionally, this file is licensed under terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version approved by the KDE Free Qt Foundation.
//(c)C: CuteHMI.Workarounds.Qt.labs.settings.1 extension is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or GNU General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.Workarounds.Qt.labs.settings.1 extension. If not, see <https://www.gnu.org/licenses/>.
//(c)C: You should have received a copy of the GNU General Public License along with CuteHMI.Workarounds.Qt.labs.settings.1 extension. If not, see <https://www.gnu.org/licenses/>.
