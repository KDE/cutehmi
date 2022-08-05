#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNATIONALIZER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNATIONALIZER_HPP

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
		//<CuteHMI.Workarounds.Qt5Compatibility-4.workaround target="Qt" cause="Qt5.15-QML_SINGLETON">
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
		QML_NAMED_ELEMENT(Internationalizer)
		QML_UNCREATABLE("Internationalizer is a singleton")
		QML_SINGLETON
#endif
		//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

		friend class Singleton<Internationalizer>;
		friend class test_Internationalizer;

	public:
		/**
		  User interface language.
		  */
		Q_PROPERTY(QString uiLanguage READ uiLanguage WRITE setUILanguage NOTIFY uiLanguageChanged)

		/**
		 * Create intance.
		 * @param qmlEngine QML engine instance.
		 * @param jsEngine JavaScript engine instance.
		 * @return instance.
		 *
		 * @note this method is used by QQmlEngine when class is annotated with QML_SINGLETON macro.
		 */
		static Internationalizer * create(QQmlEngine * qmlEngine, QJSEngine * jsEngine);

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
		 * Unload Qt translation.
		 */
		Q_INVOKABLE void unloadQtTranslation();

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
		 * Unload translations of a specific product.
		 * @param product product name.
		 */
		Q_INVOKABLE void unloadTranslation(const QString & product);

		/**
		 * Unload loaded translations. Function unloads any previously loaded translation of a product and optionally Qt
		 * translation.
		 * @param qt whether to unload Qt translation. If set to @p true, Qt translation will be unloaded.
		 */
		Q_INVOKABLE void unloadTranslations(bool qt = true);

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
		 * <tt>/usr/share/</tt> are used. The @p {langdir} subdirectory is obtained in the same way as above.
		 * @return list of standard translation directories.
		 * - Directories returned by QLibraryInfo::location(QLibraryInfo::TranslationsPath) are used.
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

		void loadTranslation(QStringList & skippedProducts, const QString & product, bool dependencies);

		void updateTranslation(QTranslator & translator, const QString & product, const QStringList & directories);

		void updateQtTranslation(QTranslator & translator);

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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
