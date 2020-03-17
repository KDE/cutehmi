# Extensions directory

Extensions can act as [QML extensions](http://doc.qt.io/qt-5/qtqml-index.html),
but they can be also used like standard libraries.

## Directories

Directory structure of extensions follows standard QML extensions scheme.
According to [QML identified module rules][1] path of an extension relative
to `extensions` directory defines module identifier, which is also extension
__name__ denoted as __BaseName.MajorVersion__. Typically __BaseName__ consists
of dot-separated _VendorName.ExtensionName_ parts, but this is a convention
rather than a requirement. Extension name must only contain __base name__ and
__major version__ suffix. Base name parts have no special meaning.

As a reference we can take `Templates.CppSkeleton.0` extension. Fully qualified
__name__ consists of __base name__ (`Templates.CppSkeleton`) and __major version__
suffix (`0`). __Base name__ consists of two parts: _vendor name_ (`Templates`)
and _extension name_ (`CppSkeleton`). It is allowed to omit _extension name_ for a
single extension from a specific vendor. It is also allowed to provide
dot-separated _extension name_ (e.g. `Examples.CppSkeleton`); or do the same with
_vendor_ (e.g. `org.nokia`).

Extension directories follow camel-case (PascalCase) rules in order to remain
consistent with QML extension naming convention used by Qt. On the other hand
following this convention within C++ would be inconvenient in many places, so
compromises have been made. Sometimes semantic members of extension directory
name are lowercased. To express such intention, a pattern
_VendorName.ExtensionName.MajorVersion_ will be transformed according to the
intention (i.e. _vendorname_ represents lowercased _VendorName_).

Typically each extension will have directory structure similar to this one.

- `include` - public header files (available to other modules).
    - _vendorname_ - for example `templates`.
        - _extensionname_ - for example `cppskeleton`.
            - `internal` - some headers need to be publicly available, but they
              are implementation detail. This directory is for such files.
- `src` - private header files and implementation.
    - _vendorname_ - for example `templates`.
        - _extensionname_ - for example `cppskeleton`.
            - `internal` - corresponds with `internal` subdirectory inside
              `include` directory.
- `tests` - Tests.
- `doc` - Documentation related files.
- `dev` - Development notes.

To keep things in order and avoid naming conflicts, C++ namespaces should
reflect above directory structure within `include` and `src` directories.

## Creating custom extensions

CuteHMI uses Qbs as build system, therefore each extension starts its life in
dedicated Qbs file. Extensions tend to produce many by-products (like tests for
example), so commonly they are defined within
[Project](https://doc.qt.io/qbs/qml-qbslanguageitems-project.html) Qbs item.

Project item allows one to put inside a collection of
[products](https://doc.qt.io/qbs/qml-qbslanguageitems-product.html) or reference
subprojects. What products are placed inside project item depends on type of
extension. CuteHMI provides customized Product items and a bunch of helper Qbs
modules for fast and convenient extension setup.

Every CuteHMI product item requires one to provide some basic metadata, such as
vendor name, description or domain. This information can be extracted by
`cutehmi.metadata` Qbs module and exported to JSON or header file.

Extensions can be divided into two major categories:
- pure QML extensions
- extensions that use C++ code

### QML extensions

Pure QML extensions are easy to deal with. In their roots they only need
`qmldir` file to work. Such extensions should be defined with
`cutehmi.Extension` product item, which takes care about things such as
intalling files to correct directories.

If you would like to provide a QML extension, then you should refer to
documentation on [qmldir] files. You can either create [qmldir] by hand or use
`cutehmi.qmldir` Qbs module dependency to generate it automatically.  You can
also use `cutehmi.qmltypes` Qbs module dependency to generate `plugins.qmltypes`
file (though it is rather needed by C++ QML plugins).

### C++ extensions

Extensions that use C++ code are more sophisticated than QML extensions. In
order to create C++ extension one should use `cutehmi.CppExtension` product
item. It hides unpleasant C++ aspects, so extension creator may just provide
metadata and add C++ or QML files (`cutehmi.CppExtension` extends
`cutehmi.Extension`). To boost the process of creating C++ extension even
further one may use `cutehmi.skeleton.cpp` module by adding it as product
dependency.

```
Depends { name: "cutehmi.skeleton.cpp" }
```

This module will create skeletal header and source files commonly found in all
C++ extensions. In fact it will create minimal operational C++ extension, which
can be then provided with some custom code to do something useful. Files
generated by `cutehmi.skeleton.cpp` extension are not treated as artifacts,
which means they can be modified (although this is not recommended, because at
some point one may want to regenerate those files with newer version of the
module). To recreate the files, they must be deleted.

C++ extensions can act as libraries, QML plugins or they can be a mix of both.

To create an extension that behaves like a library (i.e. other extensions can be
linked against it) you should refer to Qt documentation on
[Creating Shared Libraries](https://doc.qt.io/qt-5/sharedlibrary.html).
Note that mentioned `MYSHAREDLIB_EXPORT` macros are defined within
`platform.hpp` generated by `cutehmi.skeleton.cpp` module, according to the
pattern `VENDORNAME_EXTENSIONNAME_API`.

To make an extension that acts as a QML extension, but uses C++ code, you may
refer to [Creating C++ Plugins for QML](https://doc.qt.io/qt-5/qtqml-modules-cppplugins.html).
You can ignore the creation of `.pro` files and simply add files to Qbs project.
Key concepts to focus on is a class that extends `QQmlExtensionPlugin`,
`qmlRegisterType` function template that exposes `QObject` derived classes and
entries in `qmldir` file. You may also check out the tutorial
[Writing QML Extensions with C++](https://doc.qt.io/qt-5/qtqml-tutorials-extending-qml-example.html).

C++ extensions, which act as QML plugins must provide QML plugin class. By
convention in CuteHMI this class is called `QMLPlugin` and must be inside
extension's `internal` namespace. Sticking to this convention allows one to
rely on defaults, when using other Qbs helper modules such as `cutehmi.qmldir`
for example.

All CuteHMI naming conventions have been defined in `cutehmi.conventions` Qbs
module, which can be referenced by other Qbs modules. Among them there is
mentioned QML plugin class name (`qmlPluginClassName` property). All properties
can be printed to the console by setting `debugOutput` property to `true`. From
command line this can be done as follows.

```
qbs resolve -f CuteHMI.qbs modules.cutehmi.conventions.debugOutput:true
```

To print naming conentions for specific extension replace `modules` with
`products.Vendor.Extension.MajorVersion.cutehmi.conventions.debugOutput:true`.

As stated - sticking to naming conventions is not hard requirement, but it helps
avoid setting property values of various Qbs modules explicitly.

Following extensions can be used as a reference for creating custom extensions:
- [Templates.QMLSkeleton](Templates/QMLSkeleton.0/) - pure QML extension
- [Templates.CppSkeleton](Templates/CppSkeleton.0/) - C++ extension
- [Templates.CppPluginSkeleton](Templates/CppPluginSkeleton.0/) - C++ extension with QML plugin

[1]: https://doc.qt.io/qt-5/qtqml-modules-identifiedmodules.html#semantics-of-identified-modules
[qmldir]: https://doc.qt.io/qt-5/qtqml-modules-qmldir.html

