# Extensions directory

Extensions can act as [QML extensions](http://doc.qt.io/qt-5/qtqml-index.html), but they can be also used like standard libraries.


## Creating custom extensions

Extension [Templates.Skeleton](Templates/Skeleton.0/) can be used to boost the
process of creating custom extensions.


## Directories

Directory structure of extensions follows standard QML extensions scheme.
Directory name of the extension defines fully qualified extension __name__
denoted as __VendorName.ExtensionName.MajorVersion__. As a reference we can take
`Templates.Skeleton.0` extension.

Fully qualified __name__ consists of __base name__ (`Templates.Skeleton`) and
__major version suffix__ (`.0`). __Base name__ consists of two parts:
__vendor name__ (`Templates`) and __extension name__ (`Skeleton`). It is allowed
to omit __extension name__ for a single extension from a specific vendor.

Extension directories follow camel-case (PascalCase) rules in order to remain
consistent with QML extension naming convention used by Qt. On the other hand
following this convention within C++ would be inconvenient in many places, so
compromises have been made. Sometimes semantic members of extension directory
name are lowercased. To express such intention, a pattern
__VendorName.ExtensionName.MajorVersion__ will be transformed according to the
intention (i.e. __vendorname__ represents lowercased __VendorName__).

Typically each extension will have directory structure similar to this one.

- `include` - public header files (available to other modules).
    - __vendorname__ - for example `templates`.
        - __extensionname__ - for example `skeleton`.
            - `internal` - some headers need to be publicly available, but they
            are implementation detail. This directory is for such files.
- `src` - private header files and implementation.
    - __vendorname__ - for example `templates`.
        - __extensionname__ - for example `skeleton`.
            - `internal` - corresponds with `internal` subdirectory inside
            `include` directory.
- `tests` - Tests.
- `doc` - Documentation related files.
- `dev` - Development notes.

To keep things in order and avoid naming conflicts, C++ namespaces should
reflect above directory structure within `include` and `src` directories.

