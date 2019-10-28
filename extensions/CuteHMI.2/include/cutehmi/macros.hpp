#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MACROS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MACROS_HPP

#include "loggingMacros.hpp"

#ifdef Q_MOC_RUN
#define CUTEHMI_PRIVATE_SIGNALS_ACCESS_SPECIFIER Q_SIGNALS
#else
#define CUTEHMI_PRIVATE_SIGNALS_ACCESS_SPECIFIER private
#endif

#define CUTEHMI_PRIVATE_SIGNALS CUTEHMI_PRIVATE_SIGNALS_ACCESS_SPECIFIER

#ifdef Q_MOC_RUN
#define CUTEHMI_PROTECTED_SIGNALS_ACCESS_SPECIFIER Q_SIGNALS
#else
#define CUTEHMI_PROTECTED_SIGNALS_ACCESS_SPECIFIER protected
#endif

#define CUTEHMI_PROTECTED_SIGNALS CUTEHMI_PROTECTED_SIGNALS_ACCESS_SPECIFIER

#endif

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
