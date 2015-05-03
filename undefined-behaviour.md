# Undefined behaviour

<http://stackoverflow.com/questions/2397984/undefined-unspecified-and-implementation-defined-behavior>

Anything can happen while still complying to the standard: the program continues to execute, crashes, it deletes your hard disk, or make demons fly out of you nose <http://www.urbandictionary.com/define.php?term=nasal%20demons>

Bad stuff.

## Implementation-defined behaviour

Each implementation must document what it does but setting a fixed parameter.

E.g.: `sizeof(int)`

The standard may put constraints on what is conforming.

E.g.,

- `sizeof(int)` does not change value in the middle of the program. :)
- `sizeof(int) >= sizeof(short)`

## Unspecified behaviour

What happens exactly is not specified by the standard.

The standard however may put constraints on what may happen.

E.g.: argument order of evaluation `f1() * f2()`.

Unlike undefined behaviour, we are sure that this will not produce nasal deamons: there are only two valid outcomes: `f1()` runs before or after `f2()`.
