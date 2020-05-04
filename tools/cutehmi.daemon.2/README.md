# Daemon

Non-GUI program, which allows one to run QML project in the background.

Daemon mode is currently supported only on Linux. On Windows program can be run in application mode only (`--app` option).

Any extension that does not provide graphical UI QML component can be loaded as *cutehmi.daemon.2* project. Use `--extension`
command line argument to specify an extension. For example to run
[Count Daemon](../../../../extensions/CuteHMI/Examples/CountDaemon.2) example use following command.

```
cutehmi.daemon.2 --extension="CuteHMI.Examples.CountDaemon.2"
```
Read system logs to investigate whether daemon is running (e.g. `journalctl -n20` on a system with *systemd*).

One may use `--app` option to tell the program to work as a foreground process (this can be useful when testing projects).
For example following command runs [Count Daemon](../../../../extensions/CuteHMI/Examples/CountDaemon.2) in application mode.
```
cutehmi.daemon.2 --extension="CuteHMI.Examples.CountDaemon.2" --app
```

Default loader picks `Main.qml` as default QML component to load. Component can be specified with `--component` option. One can also
use `--init` option to replace default loader with custom one.

You can use `--help` command line argument to see the list of all possible command line options.

Setting empty path for PID file option (`--pidfile=`) disables creation of PID file.

Fore debug builds use `cutehmi.daemon.2.debug` instead of `cutehmi.daemon.2`.

## Linux

### Signals

Under Unix daemon will respond to signals in a following way.

- SIGTERM tells daemon to gracefully quit with exit code set to EXIT_SUCCESS (0 on almost all systems).
- SIGINT tells daemon to gracefully quit, but exit code will be set to 128 + signal code.
- SIGQUIT causes violent termination and exits via abort.
- SIGHUP attempts to reload the project as if daemon has been restarted.

### Forking

Daemon is a program, which is supposed to work as a background process. This could be achieved in many ways, but lots of traditional
UNIX daemons have been accomplishing it through techniques, which involve forking. Unfortunately this spots a controversy. It comes
out there are three conflicting schools on how many forks daemon should perform. According to these daemon should fork once, twice
or not fork at all... Detailed description on the topic is out of the scope of this document, but here are some major points.

#### Single forking daemon

Single fork is performed to exit the parent process and get rid of controlling terminal. After forking, daemon can become a new
session leader, so that when user logs out from the session, process is not killed along with processes associated with that
session. This is how [daemon()][3] function has been implemented.

#### Double forking daemon

After first fork process can still acquire controlling terminal if it opens tty according to System V rules [[1]]. Second fork
prevents this [[2]]. Unfortunately this approach heavily obscures process hierarchy, because daemon continues as orphaned process.

Notably *systemd* has troubles handling double-forking daemons as service units.
[Documentation](https://www.freedesktop.org/software/systemd/man/systemd.service.html#Type=) of *systemd* is explicit about expected
behaviour of daemon for forking service type.
```
If set to forking, it is expected that the process configured with ExecStart= will call fork() as part of its start-up. The parent
process is expected to exit when start-up is complete and all communication channels are set up. The child continues to run as the
main service process, and the service manager will consider the unit started when the parent process exits.
```
In double-forking approach the child won't continue as main service process, but rather its own child will do. This can deceive
*systemd* to think that daemon finished.

#### No forking

Many people advice to not fork at all, as it is a domain of the user to detrmine the way how the program shall be run. By this view
program should not daemonize itself. Instead it can be run as a background process (by putting `&` after the command) and tools such
as *screen* and *nohup* can be used to prevent process from being killed when user logs out [[4]].

---

There are some valid points in each of these views, so *cutehmi.daemon.2* allows you to pick number of forks by setting
`--nforks={number}` parameter. For *systemd* service pick `--nforks=1` and use `Type=forking` or `--nforks=0` with `Type=simple`.
Note that `--nforks=0` is not the same as application mode (`--app` option) - daemon uses system logging facility instead of
standard output, responds to signals, unlocks former working directory, creates PID file, closes file descriptors and resets its
umask.

____________________________________________________________________________________________________________________________________

References:
1. [Stephen A. Rago, W. Richard Stevens, "Advanced Programming in the UNIX® Environment: Second Edition", Chapter 13. Daemon Processes.][1]
2. [Andries Brouwer, "The Linux kernel".][2]
3. [Linux Programmer's Manual, DAEMON(3)][3]
4. [Department of Health Technology, "Processes; foreground and background, ps, top, kill, screen, nohup and daemons".][4]

[1]: https://learning.oreilly.com/library/view/advanced-programming-in/0201433079/
[2]: https://www.win.tue.nl/~aeb/linux/lk/lk-10.html
[3]: http://man7.org/linux/man-pages/man3/daemon.3.html
[4]: http://teaching.healthtech.dtu.dk/unix/index.php/Processes;_foreground_and_background,_ps,_top,_kill,_screen,_nohup_and_daemons
