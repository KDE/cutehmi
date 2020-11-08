#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "internal/common.hpp"
#include "Singleton.hpp"

#include <QObject>
#include <QMap>
#include <QTranslator>

namespace cutehmi {

/**
 * Internationalization singleton.
 */
class CUTEHMI_API Internationalizer:
	public QObject,
	public Singleton<Internationalizer>
{
		Q_OBJECT

		friend class Singleton<Internationalizer>;
		friend class test_Internationalizer;

	public:
		/**
		  User interface language.
		  */
		Q_PROPERTY(QString uiLanguage READ uiLanguage WRITE setUILanguage NOTIFY uiLanguageChanged)

		/**
		 * Get user interface language.
		 * @return currently used user interface language.
		 */
		QString uiLanguage() const;

		/**
		 * Set user interface language.
		 * @param uiLanguage language to be currently used.
		 */
		void setUILanguage(const QString & uiLanguage);

		/**
		 * Load Qt translation.
		 */
		Q_INVOKABLE void loadQtTranslation();

		/**
		 * Load translation of %CuteHMI product. Typically product is an extension, but the function can be also used to load
		 * translation of a tool or even a test.
		 *
		 * In order to load a translation function looks at various directories as returned by standardTranslationDirectories()
		 * function. The directories are searched in the same order as they appear in the list. Additional directories can be
		 * specified by setAdditionalTranslationDirectories() function. Additional directories take precedence over standard ones.
		 *
		 * To obtain the stem of the translation file, product name is lowercased and all the dots are replaced with hyphens, thus
		 * for example @p CuteHMI.2 becomes @p cutehmi-2. After that several file suffixes are tested in each of the translation
		 * directories as specified by QTranslator::load() function and "_qt.qm" suffix is used to satisfy KDE internationalization
		 * framework convention. For example, for @p CuteHMI.2 product any of the following translation files will match @p en-US
		 * translation: @p cutehmi-2.qm, @p cutehmi-2_en.qm, @p cutehmi-2_en_US.qm, @p cutehmi-2.en.qm, @p cutehmi-2.en_US.qm,
		 * @p cutehmi-2_qt.qm, @p cutehmi-2_en_qt.qm, @p cutehmi-2_en_US_qt.qm, @p cutehmi-2.en_qt.qm, @p cutehmi-2.en_US_qt.qm.
		 *
		 * @param product product name.
		 * @param dependencies denotes if translations of product dependencies should be loaded as well. Dependency information is
		 * retrieved from metadata, so it is important to specify appropriate dependencies in Qbs file.
		 */
		Q_INVOKABLE void loadTranslation(const QString & product, bool dependencies = true);

		/**
		 * Get standard translation directories. The list is composed of following entries:
		 * - CuteHMI-specific "translations" subdirectory.
		 * - In an attempt to satisfy gettext convention, path specified by LOCPATH environmental variable followed by
		 * <tt>{langdir}/LC_MESSAGES</tt> is used. The @p {langdir} subdirectory is obtained from \ref uiLanguage passed through
		 * QLocale::uiLanguages() function. Hyphens are replaced by underscores, so that <tt>en-US</tt> becomes <tt>en_US</tt>.
		 * - In an attempt to satisfy gettext convention, directories specified by XDG_DATA_HOME environmental variable followed by
		 * <tt>/locale/{langdir}/LC_MESSAGES</tt> are used. If XDG_DATA_HOME has not been set,
		 * <tt>HOME/.local/share</tt> is being used. The @p {langdir} subdirectory is obtained in the same way as above.
		 * - In an attempt to satisfy gettext convention, directories specified by XDG_DATA_DIRS environmental variable followed by
		 * <tt>/locale/{langdir}/LC_MESSAGES</tt> are used. If XDG_DATA_DIRS has not been set, <tt>usr/local/share/</tt> and
		 * <tt>/usr/share/</tt> are used. The {langdir} subdirectory is obtained in the same way as above.
		 * @return list of standard translation directories.
		 *
		 * @see additionalTranslationDirectories().
		 */
		Q_INVOKABLE QStringList standardTranslationDirectories() const;

		/**
		 * Get additional translation directories.
		 * @return list of additional translation directories. By default this list is empty.
		 *
		 * @see setAdditionalTranslationDirectories().
		 */
		Q_INVOKABLE QStringList additionalTranslationDirectories() const;

		/**
		 * Set additional translation directories.
		 * @param additionalDirectories additional directories, where translation files may reside.
		 *
		 * @see additionalTranslationDirectories(), standardTranslationDirectories().
		 */
		Q_INVOKABLE void setAdditionalTranslationDirectories(const QStringList & additionalDirectories);

	signals:
		/**
		 * User interface language has changed.
		 */
		void uiLanguageChanged();

	private:
		typedef QMap<QString, QTranslator *> TranslatorsContainer;

		/**
		 * Default constructor.
		 * @param parent parent object.
		 */
		explicit Internationalizer(QObject * parent = nullptr);

		bool updateTranslation(QTranslator & translator, const QString & product, const QStringList & directories);

		bool updateQtTranslation(QTranslator & translator);

		QString translationFileStem(const QString & product);

		QStringList translationDirectories() const;

		struct Members
		{
			QLocale uiLanguage;
			TranslatorsContainer translators;
			QTranslator * qtTranslator = nullptr;
			QStringList additionalTranslationDirectories;
		};

		MPtr<Members> m;
};

}

#endif
