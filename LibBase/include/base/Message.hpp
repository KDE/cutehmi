#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_MESSAGE_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_MESSAGE_HPP

#include "internal/common.hpp"
#include "ErrorInfo.hpp"

#include <memory>

#include <QObject>
#include <QAtomicInteger>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Message:
	public QObject
{
	Q_OBJECT

	public:
		enum button_t : qint32 {
			OK = 0x00000400,
			OPEN = 0x00002000,
			SAVE = 0x00000800,
			CANCEL = 0x00400000,
			CLOSE = 0x00200000,
			DISCARD = 0x00800000,
			APPLY = 0x02000000,
			RESET = 0x04000000,
			RESTORE_DEFAULTS = 0x08000000,
			HELP = 0x01000000,
			SAVE_ALL = 0x00001000,
			YES = 0x00004000,
			YES_TO_ALL = 0x00008000,
			NO = 0x00010000,
			NO_TO_ALL = 0x00020000,
			ABORT = 0x00040000,
			RETRY = 0x00080000,
			IGNORE = 0x00100000,
			NO_BUTTON = 0x00000000
		};
		Q_ENUM(button_t)

		enum type_t {
			NOTE,
			WARNING,
			QUESTION,
			ERROR,
			CRITICAL,
			FATAL
		};

		explicit Message(type_t type, const QString & text, button_t buttons = Message::NO_BUTTON, QObject * parent = 0);

		static button_t Note(const QString & text, button_t buttons = NO_BUTTON);

		static button_t Warning(const QString & text, button_t buttons = NO_BUTTON);

		static button_t Error(const QString & text, button_t buttons = OK);

		static button_t Error(const base::ErrorInfo & errorInfo, button_t buttons = OK);

		type_t type() const;

		void setType(type_t type);

		QString text() const;

		void setText(const QString & text);

		button_t buttons() const;

		void setButtons(button_t buttons);

	private:
		struct Members
		{
			type_t type;
			QString text;
			button_t buttons;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
