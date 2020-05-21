# CuteHMI

<!-- CUT HERE -->
<!-- TravisCI badge hack that kills Doxygen (1.8.14) warning "Unexpected html tag <img> found within <a href=...> context". -->
<div class="doxygen_github_hack" style="font-size: 0px">

[//]: # (\htmlonly)

[![License: LGPL 3.0](https://img.shields.io/badge/license-LGPL%203.0-blue.svg)](https://opensource.org/licenses/LGPL-3.0)
[![Build Status](https://invent.kde.org/kde/cutehmi/badges/3/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20988/badge.svg)](https://scan.coverity.com/projects/cutehmi)

[//]: # (\endhtmlonly)
</div>
<!-- CUT HERE -->

CuteHMI is an open-source HMI (Human Machine Interface) software written in C++
and QML, using Qt libraries as a framework.

![Qt Designer](doc/images/design_mode.png)
![Demo](doc/images/demo.png)

Note: While most of the project uses GNU Lesser General Public License version
3, some files are distributed under different licenses.

## Branches

Branch "master" is a development branch. Development branch may contain source
code that is undergoing deep changes, rendering it unusable. Consecutive branch
numbers denote successive iterations of the project. Iteration of the project
is related to build framework (repository layout and Qbs items). Extensions and
tools are versioned independently and they have their own development status.
Hence "perpetual beta" is desired development status of each branch.

<!-- CUT HERE -->
<!-- TravisCI badge hack that kills Doxygen (1.8.14) warning "Unexpected html tag <img> found within <a href=...> context". -->
<div class="doxygen_github_hack" style="font-size: 0px">

[//]: # (\htmlonly)

| Branch                                         | Build status                                                                                                                   | Development status |
|------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|--------------------|
| [master](https://invent.kde.org/kde/cutehmi)   | [![Build Status](https://invent.kde.org/kde/cutehmi/badges/master/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines) | pre-alpha          |
| [3](https://invent.kde.org/kde/cutehmi)        | [![Build Status](https://invent.kde.org/kde/cutehmi/badges/3/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines)      | alpha              |
| [2](https://invent.kde.org/kde/cutehmi)        | [![Build Status](https://invent.kde.org/kde/cutehmi/badges/2/pipeline.svg)](https://invent.kde.org/kde/cutehmi/pipelines)      | perpetual beta     |
| [1](https://invent.kde.org/kde/cutehmi/tree/1) | [![Build Status](https://travis-ci.org/michpolicht/CuteHMI.svg?branch=1)](https://travis-ci.org/michpolicht/CuteHMI/branches)  | alpha              |

[//]: # (\endhtmlonly)
</div>
<!-- CUT HERE -->


## Compiling

1. Get the Qt toolkit. Open-source and commercial editions can be obtained from
https://www.qt.io/. Qt can also be shipped with Linux distribution.

2. Open `CuteHMI.qbs` file with QtCreator and simply build it.

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

### Building only specified products

By default Qbs will compile all the products (tools and extension), even if they
are not needed for a project. To build only specific product use
`--products | -p` [build option](https://doc.qt.io/qbs/cli-build.html#op-op-op-op-products-op-op-op-op-p-op-lt-op-name-op-gt-op-op-op-op-op-op-lt-op-name-op-gt-op-op-op-op-op-op-op-op-op).
For example following command will build only `CuteHMI.Examples.SimpleView.1`
extension and its dependencies, using default configuration.

```
qbs -f CuteHMI.qbs -p CuteHMI.Examples.SimpleView.1
```

Find out more about build options on
[Qbs documentation website](https://doc.qt.io/qbs/index.html).

## Getting started

For an introduction you may want to run one of the existing examples. In CuteHMI
everything is either a tool or an extension, therefore examples are also provided
as extensions. Their names start with "CuteHMI.Examples" prefix. The most basic
example `CuteHMI.Examples.SimpleView.1` can be run with `cutehmi.view.3` tool by
issuing following command.

```
cutehmi.view.3 --extension="CuteHMI.Examples.SimpleView.1"
```

To create your own project you can simply copy one of the examples to your own
subdirectory in `extensions` directory (e.g. `Me/MyExtension.0`), rename `qbs` file
accordingly to match extension name (e.g. `MyExtension.0.qbs`), then edit `qbs`
file and change `name` property to match extension name
(e.g. `name:  "Me.MyExtension.0"`)

After that you can use `--force-probe-execution` Qbs option or delete build
directory and rebuild whole project. Your extension should be installed and it
can be run with `cutehmi.view.3` tool.

```
cutehmi.view.3 --extension="Me.MyExtension.0"
```

More methodical approach is to use one of the templates. The process of creating
custom extensions is described in more detail [here](extensions/).

Examples are listed in the documentation along with other extensions.


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

