#include "Daemon.hpp"
#include "logging.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>

namespace cutehmi {
namespace daemon {

static volatile sig_atomic_t sigHandled = 0;

void sigHandler(int signal)
{
	if (signal == SIGTERM) {
		CUTEHMI_INFO("Termination requested by SIGTERM signal.");
		sigHandled = signal;
	} else
		CUTEHMI_WARNING("Captured unhandled signal (" << signal << ").");
}

void Daemon::_init()
{
	pid_t pid, sid;

	// Detach from controlling tty (tty is given per session).
	// Note: when using std::exit() stack unwinding is not performed, which means destructors won't be called.

	// Fork and exit parent process to become a session leader.
	pid = fork();
	if (pid < 0) {
		CUTEHMI_WARNING("Daemon could not fork.");
		std::exit(EXIT_FAILURE);
	} else if (pid > 0)
		std::exit(EXIT_SUCCESS);	// tty session leader quits.

	// Now process may become a session leader and detach from parent session.
	sid = setsid();
	if (sid < 0)
		CUTEHMI_DIE("Failed to initialize daemon (could not create session).");

	// Second fork to become orphan and ensure that process will not acquire tty (see daemon(3)).
	pid = fork();
	if (pid < 0) {
		CUTEHMI_WARNING("Daemon could not fork.");
		std::exit(EXIT_FAILURE);
	} else if (pid > 0)
		std::exit(EXIT_SUCCESS); // Session leader quits.

	// Orphaned daemon process continues...

	umask(0);

	// This is mainly to avoid locking former working directory.
	if ((chdir("/")) < 0)
		CUTEHMI_DIE("Failed to change working directory.");

	// Close file descriptors.
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Install signal handler.
	struct sigaction sigAct;
	sigAct.sa_handler = sigHandler;
	sigemptyset(& sigAct.sa_mask);
	sigAct.sa_flags = 0;
	sigaction(SIGTERM, & sigAct, NULL);
}

void Daemon::_watch()
{
	if (sigHandled)
		terminate();
}

}
}
