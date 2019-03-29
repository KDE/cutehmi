# CuteHMI - Daemon

Non-GUI program, which allows one to run QML project in the background.

Currently only Linux is supported.

Use `--project` command line option to specify the QML project file to open.
For example to run *CountDaemon* example use following command.

```
cutehmi_daemon --project="examples/cutehmi_daemon/CountDaemon/Main.qml"
```
Fore debug builds use `cutehmi_daemon_debug` instead of `cutehmi_daemon`. Read system logs to investigate whether daemon is running
(e.g. `journalctl -n20` on a system with *systemd*).

One may use `--app` option to tell the program to work as a foreground process (this can be useful when testing projects).

```
cutehmi_daemon --project="examples/cutehmi_daemon/CountDaemon/Main.qml" --app
```

Running this example should result in printing following lines.

```
qml: Hello from counting daemon!
qml: I can count to 1
qml: I can count to 2
qml: I can count to 3
qml: I can count to 4
qml: I can count to 5
qml: I can count to 6
qml: I can count to 7
qml: I can count to 8
qml: I can count to 9
qml: I can count to 10
```

You can use `--help` command line argument to see the list of all possible command line options.


## Signals

Under Unix daemon will respond to signals in a following way.

- SIGTERM tells daemon to gracefully quit with exit code set to EXIT_SUCCESS (0 on almost all systems).
- SIGINT tells daemon to gracefully quit, but exit code will be set to 128 + signal code.
- SIGQUIT causes violent termination and exits via abort.
- SIGHUP attempts to reload the project as if daemon has been restarted.
