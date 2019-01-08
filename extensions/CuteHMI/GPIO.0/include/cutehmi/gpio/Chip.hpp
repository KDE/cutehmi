#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIP_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIP_HPP

#include "internal/common.hpp"
#include "Line.hpp"

#include <gpiod.h>

#include <QObject>
#include <QQmlListProperty>
#include <QVector>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API Chip:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString label READ label NOTIFY labelChanged)
		Q_PROPERTY(QQmlListProperty<cutehmi::gpio::Line> lines READ lines NOTIFY linesChanged)

		explicit Chip(QObject * parent = nullptr);

		~Chip() override;

		QString name() const;

		void setName(const QString & name);

		QString label() const;

		const QQmlListProperty<Line> lines();

	public slots:
		void open();

		void close();

	signals:
		void nameChanged();

		void labelChanged();

		void linesChanged();

	private:
		typedef QVector<Line *> LinesDataContainer;

		static int LineCount(QQmlListProperty<Line> * property);

		static Line * LineAt(QQmlListProperty<Line> * property, int index);

		void setLabel(const QString & label);

		void resetLineData(int lineCount);

		void updateProperties();

		void clearProperties();

		struct Members
		{
			gpiod_chip * chip;
			QString name;
			QString label;
			LinesDataContainer linesData;
			QQmlListProperty<Line> lines;

			Members(Chip * p_parent):
				chip(nullptr),
				lines(p_parent, & linesData, & Chip::LineCount, & Chip::LineAt)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
