# External libraries directory.

This directory is designated to keep "external" libraries used by some of the
extensions. "External" means any non-Qt, non-CuteHMI libraries. They are either
supplementing Qt with their own functionality, or they are required by some of
the Qt plugins (e.g., SQL drivers).

By default only Make recipes are kept in the repository. To build the libraries
one has to evaluate recipes with a suitable toolchain. Check out
[recipes](recipes/) directory for further details.

