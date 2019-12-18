# CuteHMI

<!-- CUT HERE -->
<!-- TravisCI badge hack that kills Doxygen (1.8.14) warning "Unexpected html tag <img> found within <a href=...> context". -->
<div class="doxygen_github_hack" style="font-size: 0px">

[//]: # (\htmlonly)

[![License: LGPL 3.0](https://img.shields.io/badge/license-LGPL%203.0-blue.svg)](https://opensource.org/licenses/LGPL-3.0)
[![Build Status](https://invent.kde.org/kde/cutehmi/badges/master/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines)

[//]: # (\endhtmlonly)
</div>
<!-- CUT HERE -->

CuteHMI is an open-source HMI (Human Machine Interface) software written in C++
and QML, using Qt libraries as a framework.

Note: While most of the project uses GNU Lesser General Public License version
3, some files are distributed under different licenses.

## Branches

Branch "master" is a development branch. Development branch may contain source
code that is undergoing deep changes, rendering it unusable. Consecutive branch
numbers denote successive iterations of the project.

<!-- CUT HERE -->
<!-- TravisCI badge hack that kills Doxygen (1.8.14) warning "Unexpected html tag <img> found within <a href=...> context". -->
<div class="doxygen_github_hack" style="font-size: 0px">

[//]: # (\htmlonly)

| Branch                                         | Build status                                                                                                                   | Development status |
|------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|--------------------|
| [master](https://invent.kde.org/kde/cutehmi)   | [![Build Status](https://invent.kde.org/kde/cutehmi/badges/master/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines) | pre-alpha          |
| [1](https://invent.kde.org/kde/cutehmi/tree/1) | [![Build Status](https://travis-ci.org/michpolicht/CuteHMI.svg?branch=1)](https://travis-ci.org/michpolicht/CuteHMI/branches)  | alpha              |

[//]: # (\endhtmlonly)
</div>
<!-- CUT HERE -->


## Compiling

1. Get the Qt toolkit. Open-source and commercial editions can be obtained from
https://www.qt.io/. Qt can also be shipped with Linux distribution.

2. Open `CuteHMI.qbs` file with *QtCreator* and simply build it.

3. All extensions dependent on external libraries will be disabled, if these
libraries could not be found. To make the process of finding the libraries
and installing them under Windows easier, a set of Makefiles is provided, which
allows the libraries to be build from sources. Check out
[external](external/) libraries for more details. Each extension may
provide individual documentation on how to build it.

Remember that Qbs caches [Probe](http://doc.qt.io/qbs/qml-qbslanguageitems-probe.html)
items' results, so if the library is installed after the project has been
configured with Qbs, it will not show up. You can use `--force-probe-execution`
option to force Qbs to not use cached results.


## Examples

Refer to documentation of each individual
[tool](https://cutehmi.kde.org/docs/tools_list.html) on how to run some basic
examples.


## Internals

Directory structure of the project is organized as follows.

- *_sass*, *_layouts* - directories used by GitHub Pages.
- *awkgward* - code maintanance scripts (don't bother).
- *dev* - development notes (irrelevant).
- [doc](doc/) - a place where documentation shall be.
- [extensions](extensions/) - libraries and QML extensions.
- [external](external/) - directory containing "external" libraries.
- *extra* - various stuff related to the project, such as T-shirts.
- *qbs* - Qbs modules and imports.
- [tools](tools/) - executable programs.

![Dependencies between tools, extensions and external libraries](doc/images/general_dependencies.svg)

Two most important directories are [extensions](extensions/) and
[tools](tools/). Extensions combine functionality of QML extensions and
standard libraries. They can be utilized by end-user applications, but they can
be also linked with each other. Some extensions may depend on
[external](external/) libraries.

## Quick links

- [Repository](https://invent.kde.org/kde/cutehmi)
- [Website](https://cutehmi.kde.org/)
- [Documentation](https://cutehmi.kde.org/docs/)

