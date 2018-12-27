# CuteHMI - Daemon

Non-GUI program, which allows one to run QML project in the background.

Use `--project` command line option to specify the QML project file to open.
For example to run *CountDaemon* example use following command.

```
cutehmi_daemon --project="examples/CountDaemon/Main.qml"
```
Read system logs to investigate whether daemon is running (e.g. `journalctl -n20` on a system with *systemd*).

One may use `--app` option to tell the program to work as a foreground process (this can be useful when testing projects).

```
cutehmi_daemon --project="examples/CountDaemon/Main.qml" --app
```

You can use `--help` command line argument to see the list of all possible command line options.


## Signals

Under Unix daemon will respond to signals in a following way.

- SIGTERM tells daemon to gracefully quit with exit code set to EXIT_SUCCESS (0 on almost all systems).
- SIGINT tells daemon to gracefully quit, but exit code will be set to 128 + signal code.
- SIGQUIT causes violent termination and exits via abort.
- SIGHUP attempts to reload the project as if daemon has been restarted.
