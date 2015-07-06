# perf

Depends on a kernel module. So every time your kernel updates, it breaks :-)

    sudo apt-get install linux-tools-generic

    sudo perf record ./a.out
    sudo perf report

Opens a curses interface.
