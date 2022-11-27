The best way to contribute to CuteHMI is through
[KDE Invent](https://invent.kde.org/) GitLab infrastructure. You will need [KDE
Identity](https://identity.kde.org/) to have anything more than view-only access
to the repositories. If you don't have KDE Identity you can
[register](https://identity.kde.org/index.php?r=registration/index) yourself.
Thereafter you simply open [new issue](https://invent.kde.org/kde/cutehmi/issues).
You can use GitLab issues to report any vulnerabilities, bugs, stories or feature
requests.

If you can't have KDE Identity for whatever reason, as a last resort, you can
open an issue on Michal's private GitHub
[mirror](https://github.com/michpolicht/CuteHMI/issues).

You may want to check [KDE contribution
guidelines](https://community.kde.org/Get_Involved).

It may also be helpful to read [extensions README](extensions/README.md).

CuteHMI uses [Artistic Style](http://astyle.sourceforge.net/) to format C++
code.

When it comes to coding conventions, [Qt Coding
Conventions](https://wiki.qt.io/Coding_Conventions) are used with few
exceptions.
- Exceptions are allowed.
- It is allowed to inherit from template classes (CuteHMI uses namespaces
  everywhere, so symbol clashes should not be a problem).
- Whether exact or fuzzy float comparisons should be performed depends on a case
  (sometimes exact comparisons are desired).
- It comes out acronyms in class names are not lowercased (CuteHMI, not
  CuteHmi).

You don't need to read it all in one go. Use provided links as an assist. If you
have any doubts you can ask on chat or mailing list.

BY CONTRIBUTING YOU MUST AGREE TO RELEASE YOUR WORK UNDER THE TERMS OF LGPL 3.0
LICENSE OR LATER, AND(!) MIT LICENSE.

Thank you for your interest in CuteHMI!

