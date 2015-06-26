# gprof

Profile C and other compiled language program.

Part of Binutils.

    gcc -pg main.c
    # Run it to generate a gmon.out file.
    ./a.out arg0 arg1
    # No need to pass the arguments again: profile times have already been generated.
    gprof a.out

## Run multiple times

<http://stackoverflow.com/questions/20948012/combining-multiple-gprof-result-files-into-a-single-file>

## Alternatives

Major:

- `perf`
- `valgrind`
- `gperftools`

Reviews:

- <http://rhaas.blogspot.fr/2012/06/perf-good-bad-ugly.html>
- <http://gernotklingler.com/blog/gprof-valgrind-gperftools-evaluation-tools-application-level-cpu-profiling-linux/>
