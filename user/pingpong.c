#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[10];
    int p[2];
    // Pipe and fork seem to go together.
    pipe(p);

    if (fork() == 0) {
        // Child

        // Send byte to parent
        write(p[1], "a", 1);
        close(p[1]);

        // Now read from read-end of pipe. This waits until
        // data is written to the write-end of the pipe or
        // for all file descriptors (across all processes)
        // referring to the write-end of the pipe to be closed.

        int n = read(p[0], buf, 1);
        if (n > 0) printf("%d: received ping\n", getpid());
        exit(0);

    } else {
        // Parent
        write(p[1], "a", 1);
        close(p[1]);

        int n = read(p[0], buf, 1);
        if (n > 0) printf("%d: received pong\n", getpid());
        exit(0);
    }

}
