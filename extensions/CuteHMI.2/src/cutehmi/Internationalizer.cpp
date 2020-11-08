#include "../../include/cutehmi/Internationalizer.hpp"
#include "../../cutehmi.dirs.hpp"

#include <cutehmi/functions.hpp>

#include <QDir>
#include <QJsonArray>
#include <QLibraryInfo>

namespace cutehmi {

QString Internationalizer::uiLanguage() const
{
	return m->uiLanguage.name();
}

void Internationalizer::setUILanguage(const QString & uiLanguage)
{
	if (uiLanguage != m->uiLanguage.name()) {
		m->uiLanguage = QLocale(uiLanguage);
		CUTEHMI_DEBUG("Setting UI language to '" << uiLanguage << "'.");

		if (m->qtTranslator)
			updateQtTranslation(*m->qtTranslator);

		for (auto productTranslator = m->translators.begin(); productTranslator != m->translators.end(); ++productTranslator)
			updateTranslation(*productTranslator.value(), productTranslator.key(), translationDirectories());

		if (QCoreApplication::instance()) {
			QEvent event(QEvent::LanguageChange);
			QCoreApplication::sendEvent(QCoreApplication::instance(), & event);
		}

		emit uiLanguageChanged();
	}
}

void Internationalizer::loadQtTranslation()
{
	if (!m->qtTranslator) {
		m->qtTranslator = new QTranslator(this);
		updateQtTranslation(*m->qtTranslator);
		QCoreApplication::installTranslator(m->qtTranslator);
	} else
		CUTEHMI_WARNING("Qt translation already loaded.");
}

void Internationalizer::loadTranslation(const QString & product, bool dependencies)
{
	if (!m->translators.contains(product)) {
		QTranslator * translator = new QTranslator(this);
		m->translators.insert(product, translator);
		updateTranslation(*translator, product, translationDirectories());
		QCoreApplication::installTranslator(translator);
	} else
		CUTEHMI_DEBUG("Translation of product '" << product << "' already loaded.");

	if (dependencies) {
		QJsonArray dependenciesArray = metadata(product).value("dependencies").toArray();
		for (auto dependency : dependenciesArray) {
			QString dependencyName = dependency.toObject().value("name").toString();
			if (metadataExists(dependencyName))
				if (metadata(dependencyName).value("i18n").toBool())
					loadTranslation(dependencyName, dependencies);
		}
	}
}

QStringList Internationalizer::standardTranslationDirectories() const
{
	QStringList directories;
	QString translationsRelativeDir = QDir("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_TRANSLATIONS_INSTALL_SUBDIR);
	directories << QDir::cleanPath(QDir::currentPath() + "/" + translationsRelativeDir);

	QStringList uiLanguages = m->uiLanguage.uiLanguages();
	uiLanguages.replaceInStrings("-", "_");

	if (!qEnvironmentVariable("LOCPATH").isEmpty())
		for (auto lang : uiLanguages)
			directories << qEnvironmentVariable("LOCPATH") + lang + "/LC_MESSAGES";

	QStringList xdgDirectories = qEnvironmentVariable("XDG_DATA_HOME").split(':', QString::SkipEmptyParts);
	if (qEnvironmentVariable("XDG_DATA_HOME").isEmpty())
		xdgDirectories << qEnvironmentVariable("HOME") + "/.local/share";
	xdgDirectories << qEnvironmentVariable("XDG_DATA_DIRS").split(':', QString::SkipEmptyParts);
	if (qEnvironmentVariable("XDG_DATA_DIRS").isEmpty())
		xdgDirectories << "/usr/local/share/" << "/usr/share/";
	for (auto directory : xdgDirectories)
		for (auto lang : uiLanguages)
			directories << directory + "/locale/" + lang + "/LC_MESSAGES";

	directories << QLibraryInfo::location(QLibraryInfo::TranslationsPath);

	return directories;
}

QStringList Internationalizer::additionalTranslationDirectories() const
{
	return m->additionalTranslationDirectories;
}

void Internationalizer::setAdditionalTranslationDirectories(const QStringList & additionalDirectories)
{
	m->additionalTranslationDirectories = additionalDirectories;
}

Internationalizer::Internationalizer(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

bool Internationalizer::updateTranslation(QTranslator & translator, const QString & product, const QStringList & directories)
{
	for (auto directory : directories) {
		if (translator.load(m->uiLanguage, translationFileStem(product), ".", directory)
				// Handle files with lanugage part after underscore as well (Qbs Qt.core module does not handle files with dot-separated subextensions before '.ts' part).
				|| translator.load(m->uiLanguage, translationFileStem(product), "_", directory, ".qm")
				// Handle files with "_qt.qm" suffix (KDE internationalization framework convention).
				|| translator.load(m->uiLanguage, translationFileStem(product), "_", directory, "_qt.qm")) {
			CUTEHMI_DEBUG("Translation of product '" << product << "' loaded from '" << directory << "' directory.");
			return true;
		}
	}
	CUTEHMI_WARNING("Translation of product '" << product << "' not found.");
	return false;
}

bool Internationalizer::updateQtTranslation(QTranslator & translator)
{
	if (translator.load(m->uiLanguage, "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
		CUTEHMI_DEBUG("Loaded Qt translation.");
		return true;
	}

	CUTEHMI_WARNING("Could not load Qt translation.");
	return false;
}

QString Internationalizer::translationFileStem(const QString & product)
{
	return product.toLower().replace('.', '-');
}

QStringList Internationalizer::translationDirectories() const
{
	return additionalTranslationDirectories() + standardTranslationDirectories();
}

}
