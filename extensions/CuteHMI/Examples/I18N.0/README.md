# Internationalization Example

Internationalization example. This example shows how to support multiple languages and how to use CuteHMI.Internationalizer
singleton.

To run the example use [cutehmi.view.4](../../../../tools/cutehmi.view.4/) tool.

```
cutehmi.view.4 CuteHMI.Examples.I18N.0
```

Option `--lang` can be used to specify the initial language.

```
cutehmi.view.4 CuteHMI.Examples.I18N.0 --lang eo
```


## Preparation

The necessary step to provide a multilingual user interface in Qt application is to prepare translation files. These files can be
in fact conveniently prepared with two toolchains: gettext + KDE internationalization framework or Qt internationalization tools.

The gettext + KDE approach is described [here](https://techbase.kde.org/Development/Tutorials/Localization/i18n_Build_Systems).
Don't forget to pass `--qt` option to `msgfmt` program, when using this method.

This examples uses Qt-based approach. Standard internationalization process with tools shipped by Qt is described
[here](https://doc.qt.io/qt/internationalization.html).

To signal that extension supports internationalization one should set `i18n` property to `true` in `project.qbs` file.

```
i18n: true
```

This is important, because CuteHMI.Internationalizer relies on product metadata, when loading translations of dependent products.

## Translation files

The example comes with two `.ts` files, which reside in `i18n` subdirectory. They provide translations for US English and Esperanto.
In order to generate such files one has to call `lupdate` program. Once `.ts` files are added to the project, `Qt.core` Qbs module
calls `lrelease` program to generate `.qm` files. These are installed to `translations` directory, which is formally defined by
`translationsInstallSubdir` property of `cutehmi.dirs` Qbs module.

To generate `.ts` files from Qbs, `cutehmi.i18n` Qbs module can be used. Unfortunately, because `Qt.core` Qbs module calls
`lrelease` on every `*.ts` file in the product and `lrelease` triggers error if these files are empty, you can't simply add empty
`.ts` files to the project. Instead, one has to use `additionalTranslations` property to generate new translation files. After they
are generated, they should be added to the project files. Again, this property should be used only when generating new
translations - do not use it for `.ts` files, which are already in the project files.

```
Depends { name: "cutehmi.i18n" }
cutehmi.i18n.update: true
cutehmi.i18n.additionalTranslations: [
        "i18n/cutehmi-examples-i18n-0_en_US.ts",
	"i18n/cutehmi-examples-i18n-0_eo.ts",
]
```

Properties can be also passed to Qbs from the command line, resulting in a bit lenghty command. Here's a command, which introduces
Russian translation:

```
qbs build project.buildBinaries:false modules.cutehmi.qmltypes.additionalProductTypes:[]
products.CuteHMI.Examples.I18N.0.cutehmi.i18n.additionalTranslations:[cutehmi-examples-i18n-0_ru.ts]
products.CuteHMI.Examples.I18N.0.cutehmi.i18n.update:true -f CuteHMI.qbs
```

Argument `project.buildBinaries:false` turns off generation of binaries and `modules.cutehmi.qmltypes.additionalProductTypes:[]`
prevents qmlplugindump being called on unbuilt products.

After `.ts` files are added to the project files, `cutehmi.i18n` Qbs module becomes unnecessary. It may significantly slow down
the compilation by repeatedly making costly `lupdate` calls. It is reasonable to comment out its entries and only occasionally run
Qbs with `cutehmi.i18n.update` set to `true` to update the translations.

### File names

Names of translation files consist of stem and suffix. Stem is constructed by lowercasing product name and replacing dots with
hyphens. In case of `CuteHMI.Examples.I18N.0` extension, stem is `cutehmi-examples-i18n-0`. The suffix part denotes a language in
a format described in Qt documentation on QLocale::QLocale(const QString &). Here we have `_en_US.ts` for US English and `_eo.ts`
for Esperanto. One can see that suffix has been separated from the stem by underscore, but in fact language can be specified in
many different ways. Supported translation suffixes and translation directory locations are listed in the documentation of
CuteHMI.Internationalizer.loadTranslation() function.

## The actual example

After all the prerequisites has been satisfied, using CuteHMI.Internationalizer from QML is pretty straightforward.

At first, we provide some translatable string.

\snippet View.qml Translation string

The combo box controls the language choice, so we set `currentIndex` to match the initial language.

\snippet View.qml Setting currentIndex

When user chooses another language, we simply reflect his choice by updating CuteHMI.Internationalizer.uiLanguage property.

\snippet View.qml Language activated

\example View.qml
Here is a complete listing of the example source file.
