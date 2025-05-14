# xv6 and Unix Utilities

This repository will contain some completed lab assignments of the xv6 OS.
I will have personalized summaries of concepts learned from xv6 here. More can be found in the book 
of course.

## File Descriptors

are integers, and they are abstractions of files and file-like objects managed by the kernel. 
Each process has a table mapping file descriptors to file objects. By convention, 0 will map to
standard input, 1 to standard output, and 2 to standard error. This convention
makes it easy to implement I/O redirection and piping.

A process can obtain a file descriptor (the file table will have key `fd` and
its value will represent a file object) by calling `open` or `dup`. Can
read and write to a file descriptor by using the respective system calls.
Note that `read(fd, buffer, n_bytes)` and `write(fd, buffer, n_bytes)` have 'offsets' being updated behind-the-scenes
so that when we read/write to a file, we skip whatever we have read/write on the last call.

As an example, a command like `cat < input.txt` can be implemented by first obtaining a file descriptor
for the file with name 'input.txt', reassigning file descriptors so that 0 points to
the file object referred to by 'input.txt', and then calling execv with the program 'cat'.
'cat' will then run with the contents of 'input.txt' in its standard input.

When `fork` is called, the child also gets the same file descriptor table of the parent. The offsets
of the file-object are also shared between parent and child. That is, if the parent writes to fd,
and the child does after, the child's write will use the offset of the parent's write.

When `dup` is called, the offsets shared between the new file descriptor and the duplicated file descriptor
are shared. If we write to one file descriptor and then write to another file descriptor, the second
write will use the offset of the first write.


### Pipes

calling the system call `pipe(p)` on an `int p[2]` and then calling `fork()` allows the parent and
child process to communicate with eachother. One process can write to `p[1]` and
the other can read from `p[0]`. The read to `p[0]` blocks until data is written
on the write side or all file descriptors referring to the write side object
are closed.

Advantage of pipe is that it removes the need for intermediate files. Processes can 
theoretically transfer and process large amounts of data in an online fashion, without 
having to allocate space for all the data. Also some concurrency can be achieved by
having the read and write process work independently (think about the consumer producer problem).


### Files, File system, inodes

TODO. Not too important i think for my purposes.
