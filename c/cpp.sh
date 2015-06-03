#!/usr/bin/env bash

set -e

# Templates.
#[ "$(printf '\n' | cpp -P)" = '' ]
#[ "$(printf '#define M \nM\n' | cpp -P)" = '' ]
#[ "$(printf '#define M(x) \nM(a)\n' | cpp -P)" = '' ]

# Not specified by the C standard, but `cpp` collapses spaces.
[ "$(printf 'a  b\n' | cpp -P)" = 'a b' ]

## -P

  # Remove lines added by default:
  # http://stackoverflow.com/questions/2946898/how-to-remove-lines-added-by-default-by-the-c-preprocessor-to-the-top-of-the-out?lq=1

## # Operator

## Stringify

  # Macro parameters are not expanded inside quotes.

    [ "$(printf '#define M(x) "x"\nM(a)\n' | cpp -P)" = '"x"' ]

  # In ANSI C, the syntax says that strings are single preprocessor token.

  # Stringification `#x` is the solution,
  # together with compiler string auto concatenation "a" "b".

    [ "$(printf '#define M(x) #x\nM(a)\n' | cpp -P)" = '"a"' ]
