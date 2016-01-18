#!/usr/bin/env bash

set -e

function cpp_opts { cpp -P -pedantic-errors -std=c11 -Wall; }

# Templates.
#[ "$(printf '\n' | cpp_opts)" = '' ]
#[ "$(printf '#define M \nM\n' | cpp_opts)" = '' ]
#[ "$(printf '#define M(x) \nM(a)\n' | cpp_opts)" = '' ]

# Not specified by the C standard, but `cpp` collapses spaces.
[ "$(printf 'a  b\n' | cpp_opts)" = 'a b' ]

## Comments

  # It is the preprocessor that removes comments.

    [ -z "$(printf '/* */' | cpp_opts)" ]

## -P

  # Remove lines added by default:
  # http://stackoverflow.com/questions/2946898/how-to-remove-lines-added-by-default-by-the-c-preprocessor-to-the-top-of-the-out?lq=1

  # What the default lines mean:
  # http://stackoverflow.com/questions/5370539/what-is-the-meaning-of-lines-starting-with-a-hash-sign-and-number-like-1-a-c

## # Operator

## Stringify

  # Macro parameters are not expanded inside quotes.

    [ "$(printf '#define M(x) "x"\nM(a)\n' | cpp_opts)" = '"x"' ]

  # In ANSI C, the syntax says that strings are single preprocessor token.

  # Stringification `#x` is the solution,
  # together with compiler string auto concatenation "a" "b".

## Recursive expansion

    # The standard explicitly says that if a macro calls itself, then it should not expand.

    # What happens when two macros invoke each other is not well specified,
    # but likely standard writers would want to forbid that.

    # http://stackoverflow.com/questions/12447557/can-we-have-recursive-macros

      [ "$(printf '#define M M\nM\n' | cpp_opts)" = 'M' ]
      [ "$(printf '#define M(x) M(x)\nM(a)\n' | cpp_opts)" = 'M(a)' ]
