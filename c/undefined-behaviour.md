# Undefined behaviour

<http://stackoverflow.com/questions/2397984/undefined-unspecified-and-implementation-defined-behavior>

Anything can happen while still complying to the standard: the program continues to execute, crashes, it deletes your hard disk, or make demons fly out of you nose <http://www.urbandictionary.com/define.php?term=nasal%20demons>

Bad stuff.

Examples:

- use an uninitialized local variable: <http://stackoverflow.com/questions/11962457/why-is-using-an-uninitialized-variable-undefined-behavior-in-c>
- negative shift `1 << -1`: <http://stackoverflow.com/questions/4945703/left-shifting-with-a-negative-shift-count>
- access object after its lifetime: `int *ip = 0; {int i = 1; ip = &i;} *ip++;`
- modify `const` variable with pointer cast that removes `const`

### Why the spec ever use undefined behaviour instead of implementation defined behaviour?

Undefined behaviour is much more drastic than implementation defined behaviour and should never be run.

But why then does it exist at all?

There seems to be two reasons for that:

- some important CPU raises an exception, and there is no CPU exception handling in C
- optimization opportunities that come from excluding that case

Examples that explain both:

- <http://stackoverflow.com/questions/11962457/why-is-using-an-uninitialized-variable-undefined-behavior-in-c>
- <http://stackoverflow.com/questions/3948479/integer-overflow-and-undefined-behavior>

## Implementation-defined behaviour

Each implementation must document what it does but setting a fixed parameter.

E.g.: `sizeof(int)`

The standard may put constraints on what is conforming.

E.g.,

- `sizeof(int)` does not change value in the middle of the program. :)
- `sizeof(int) >= sizeof(short)`

### Implementation defined signal

One particularly severe implementation defined effect are signals.

For example:

    (char)UMAX_CHAR

does results according to C99 6.3.1.3/3 "Signed and unsigned integers":

> the new type is signed and the value cannot be represented in it; either the result is implementation-defined or an implementation-defined signal is raised.

## Unspecified behaviour

What happens exactly is not specified by the standard.

The standard however may put constraints on what may happen.

E.g.: argument order of evaluation `f1() * f2()`.

Unlike undefined behaviour, we are sure that this will not produce nasal deamons: there are only two valid outcomes: `f1()` runs before or after `f2()`.
