# Call graph

## Manual symbol dump

The main goal is to make the call graph of a huge program like `cc1` (20k functions).

For timing measurements, I have tried:

    nm cc1 | awk '$1 == "T" {print "break *0x" $2 }' > t.gdb
    gdb -x t.gdb
    run

Sourcing `t.gdb` took around 2 minutes, but seemed to set all breakpoints.

But running `run` seemed took a very long time.

After it regains control, `continue` is responsive, but doing:

    while 1
      continue
      bt
    end

runs *very* slowly.
