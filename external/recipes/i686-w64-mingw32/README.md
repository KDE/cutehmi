# Windows mingw32 recipes.

This directory contains Make recipes, which allow the software to be built from
sources on Windows with 32-bit MinGW.

Qt comes with MinGW as one of the officialy supported toolchains. Unfortunately,
MinGW shipped with Qt is not enough to build "external" libraries in most cases.
Many libraries rely on GNU Autotools as their build system, thus they demand 
shell access and stuff such as coreutils, AWK, or even Perl.

To satisfy these requirements MSYS has to be installed. Recipes are aware of
'mingw-get' program and they can use it to download missing packages. Minimal
MinGW instalation is sufficient. If 'mingw-get' can not be found, adequate
error message will be printed.

Some recipes may ask for CMake, so it also has to be installed.

To compile the libraries open command prompt, `cd` to CuteHMI top directory and 
execute commands.
```
set PATH=C:\Qt\Tools\mingw530_32\bin
mingw32-make ports
```
Modify PATH accordingly, if Qt/MinGW is installed to different location.

