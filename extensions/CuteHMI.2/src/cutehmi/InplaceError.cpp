#include <cutehmi/InplaceError.hpp>

namespace cutehmi {

InplaceError::InplaceError(const QString & p_message, const char * p_file, int p_line, const char * p_function, int p_code):
	Error(p_code),
	message(p_message),
	file(p_file),
	line(p_line),
	function(p_function)
{
}

QString InplaceError::str() const
{
	QStringList location;
	if (file)
		location << QString("file: ") + file;
	if (line)
		location << QString("line: ") + QString::number(line);
	if (function)
		location << QString("function: ") + function;

	QString result = message;
	if (!location.isEmpty())
		result += QString(" [") + location.join(' ') + "]";

	return result;
}

}
