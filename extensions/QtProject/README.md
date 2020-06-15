# QtProject

Pseudo-extension exploiting `QtProject` directory.

Qt looks at `QtProject` directory for files such as `qtlogging.ini`. This pseudo-extension installs `qtlogging.ini` in that
directory and therefore it can be used for convenient in-source customization of logging.
