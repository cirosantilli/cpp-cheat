# Compilation passes

Compilation goes through several transformations phases of the original source until the assembly is generated:

- C source
- GENERIC
- GIMPLE
- RTL
- Machine code

## How to observe the internals

To observe all passes at once, use:

    gcc -fdump-tree-all -fdump-ipa-all -fdump-rtl-all

This generates several files with names of type:

    <original file>.<id><dump>.<extension>

e.g.:

    atomic.cpp.001t.tu
    atomic.cpp.002t.class
    atomic.cpp.166r.expand

where each one represents one pass.

- `<dump>` is one letter that depends on the dump type: `t` for `tree` and `r` for `rtl`

The most interesting stages are:

- `.gimple`:
- `.s.gkd`: `-fdump-final-insns`: the very last representation before conversion to assembly

Non obvious ones:

- `.tu`, from `-fdump-translation-unit`. The output is huge as it contains all includes.
- `.original`, from `-fdump-tree-original`
- `.omplower` and `.lower`, from TODO?
- `.eh`, TODO. Likely liked to the `eh_frame` sections.
- `.cfg`, control flow graph

## GIMPLE

Dump with `-fdump-tree-gimple` to a `.gimple` file.

### SSA TODO

Part of GIMPLE.

## RTL

### insns

Part of RTL.

- `-fdump-final-insns`: dump final representation after optimization was done
