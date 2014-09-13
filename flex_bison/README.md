# Flex and Bison

Parser generators.

Flex and Bison are GNU open source clones of Lex and Yacc respectively.

## Flex

Tokenizer: splits input with regexes.

Why it works well with bison:

- this step is `O(n)`.
- the Bison naive algorithm is `O(n^3)`. Theoretical bounds are linked to matrix multiplication at O(n^2.40) and falling, but Bison is likely to 

## Bison

Parses deterministic context free languages, AKA deterministic LR.

Subset of context-free, superset of regex.

## Sources

Very good intro source: [Tom Niemann - Lex & Yacc Tutorial](http://epaperpress.com/lexandyacc/)
