MinGW port of [GNU gettext][gettext-www].

This port uses [gettext source code][gettext-ftp] as provided by GNU and patches
provided by [Michele Locati].

Autotools are extremally sensitive to timestamps, therefore patch
`cutehmi_0000-fix-0004-timestamps` has been applied to patch the patch 
`0004-fix-gl_cv_prog_as_underscore-test.patch` (which patches Autotools build
scripts) by modifying patch timestamps to UTC and setting timestamp values, so
that regeneration of build scripts can be avoided.

[Michele Locati]: https://github.com/mlocati/gettext-iconv-windows
[gettext-ftp]: ftp://ftp.gnu.org/pub/gnu/gettext/
[gettext-www]: https://www.gnu.org/software/gettext/

