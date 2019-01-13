# Bison

Main Bison cheat.

It is hard to test Bison without Flex, so they are used together.

Information on Flex is not given here.

## What the it does

This generates a simple C-like calculator which supports:

- `print` statement
- `+` `-` `*` `/`
- `<` `>` `<=` `>=` `==` `!=`
- variables
- `if`, `while`

The program takes output from stdin, and outputs printed results to stdout.

Sample input:

    i = 0;
    while (i < 3) {
        print i;
        i = i + 1;
    }

Output:

    0
    1
    2

Many input examples can be found in the [test](test) file.

Possible outputs:

- interpreter
- assembler
- visual ASCII syntax tree

Missing features:

- integers arithmetic only
- functions
- strings

## cudos

This was  taken this from a very good intro source:

[Tom Niemann - Lex & Yacc Tutorial](http://epaperpress.com/lexandyacc/)

and only minor modifications were made, mostly annotations to explain what lines are doing.
