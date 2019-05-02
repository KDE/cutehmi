# Documentation directory

This directory keeps files used to build the documentation. Documentation itself
is built by Doxygen and it is kept in separate git submodule.

You can initialize this submodule by issuing following commands.
```sh
git submodule init
git submodule update
```

Alternatively you can build documentation by executing Make command from top
level project directory, providing that you have all necessary tools.
```
make doc
```
You have to build the project beforehand as Qbs module is responsible for
generation of documentation artifacts!

You can also view [documentation online](https://cutehmi.kde.org/docs/).

