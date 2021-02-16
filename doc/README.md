# Documentation directory

This directory keeps files used to build the documentation.

You can build documentation by executing Make command from top level project
directory, providing that you have all necessary tools.
```
make doc
```
You have to build the project beforehand as Qbs module is responsible for
generation of documentation artifacts!

To generate documentation artifacts without building the binaries execute the command below.
```
qbs project.buildBinaries:false modules.cutehmi.qmltypes.additionalProductTypes:[] --check-outputs -f CuteHMI.qbs
```

Tools required to build the documentation include:
- dirname
- doxygen
- doxyqml
- find (findutils)
- python
- qbs
- sed
- sh
- sort
- xargs.

You can also view [documentation online](https://cutehmi.kde.org/docs/).

