#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // Send the byte '1' to the child process

    int res = fork();
    if (res != 0) {
        // Parent
    } else {
        // Child

    }
}
