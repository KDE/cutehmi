#ifndef CUTEHMI_APPFULL_SRC_ERRORHANDLER_HPP
#define CUTEHMI_APPFULL_SRC_ERRORHANDLER_HPP

#include <utils/Singleton.hpp>
#include <base/Error.hpp>

#include <QString>
#include <QMessageBox>
#include <QApplication>

#include <typeinfo>

/**
 * Error handler.
 *
 * @todo for cleaner API provide something like "prepareBox()" function(s) and use box(ERROR error) (extBox(EXTERROR) for idea 2.0) instead of messy failBox().
 *
 * @todo probably it'll be better to provide own MessageBox and ExtMessageBox classes with templated exec(ERROR)/exec(EXTERROR).
 */
class ErrorHandler:
	public utils::Singleton<ErrorHandler>
{
	friend class utils::Singleton<ErrorHandler>;

	public:
		/**
		 * Show failure box. Shows message box on failure, that is when error code has a value different than
		 * @p base::Error::OK.
		 * @param error error object. Must be derived from base::Error.
		 * @param failText if not empty it will appear in message box above error string.
		 * Error string will become informative text.
		 * @param details detailed text.
		 * @return @p true if message box has been show, @p false otherwise.
		 */
		template <typename ERROR>
		bool failBox(ERROR error, const QString & failText = QString(), const QString & details = QString()) const;

	private:
		ErrorHandler() = default;

		~ErrorHandler() override = default;


};

template <typename ERROR>
bool ErrorHandler::failBox(ERROR error, const QString & failText, const QString & details) const
{
	if (error == base::Error::OK)
		return false;

	//<unsolved id="AppFull-6" target="Qt" cause="design">
	// QMessageBox can not be made resizeable in a normal way.
	QMessageBox msgBox;
	//</unsolved>

	msgBox.setIcon(QMessageBox::Warning);

	if (!failText.isEmpty()) {
		msgBox.setText(failText);
		msgBox.setInformativeText(error.str());
	} else
		msgBox.setText(error.str());

	QString detailedText(QObject::tr("Error class: %1, code: %2.").arg(typeid(ERROR).name()).arg(error.code()));
	if (!details.isEmpty())
		detailedText.append("\n").append(details);
	msgBox.setDetailedText(detailedText);

	//<workaround id="AppFull-5" target="Qt" cause="bug">
	// QMessageBox does not make beep sound (at least on Windows XP) (Qt bug?).
	QApplication::beep();
	//</workaround>
	msgBox.exec();

	return true;
}

#endif
