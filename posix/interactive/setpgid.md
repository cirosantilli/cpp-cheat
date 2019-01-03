# setpgid

- https://stackoverflow.com/questions/6108953/how-does-ctrl-c-terminate-a-child-process/52042970#52042970
- https://unix.stackexchange.com/questions/149741/why-is-sigint-not-propagated-to-child-process-when-sent-to-its-parent-process/465112#465112
- https://stackoverflow.com/questions/1046933/posix-process-groups/53759402#53759402
- https://stackoverflow.com/questions/31907212/will-ctrlc-send-sigint-signals-to-both-parent-and-child-processes-in-linux/52042820#52042820

**`setpgid` POSIX C process group minimal example**

It might be easier to understand with a minimal runnable example of the underlying API.

This illustrates how the signal does get sent to the child, if the child didn't change its process group with `setpgid`.

Source: [setpgid.c](setpgid.c).

Compile with:

    gcc -ggdb3 -O0 -std=c99 -Wall -Wextra -Wpedantic -o setpgid setpgid.c

**Run without `setpgid`**

Without any CLI arguments, `setpgid` is not done:

    ./setpgid

Possible outcome:

    child pid, pgid = 28250, 28249
    parent pid, pgid = 28249, 28249
    sigint parent
    sigint child

and the program hangs.

As we can see, the pgid of both processes is the same, as it gets inherited across `fork`.

Then whenever you hit:

    Ctrl + C

It outputs again:

    sigint parent
    sigint child

This shows how:

- to send a signal to an entire process group with `kill(-pgid, SIGINT)`
- Ctrl + C on the terminal sends a kill to the entire process group by default

Quit the program by sending a different signal to both processes, e.g. SIGQUIT with `Ctrl + \`.

**Run with `setpgid`**

If you run with an argument, e.g.:

    ./setpgid 1

then the child changes its pgid, and now only a single sigint gets printed every time from the parent only:

    child pid, pgid = 16470, 16470
    parent pid, pgid = 16469, 16469
    sigint parent

And now, whenever you hit:

    Ctrl + C

only the parent receives the signal as well:

    sigint parent

You can still kill the parent as before with a SIGQUIT:

    Ctrl + \

however the child now has a different PGID, and does not receive that signal! This can seen from:

    ps aux | grep setpgid

You will have to kill it explicitly with:

    kill -9 16470

This makes it clear why signal groups exist: otherwise we would get a bunch of processes left over to be cleaned manually all the time.

Tested on Ubuntu 18.04.
