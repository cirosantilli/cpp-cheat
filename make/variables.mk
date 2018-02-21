.POSIX:

## Identifiers

    # Things which can be part of the identifier:

    # A variable name may be any sequence of characters not containing ‘:’, ‘#’, ‘=’, or whitespace.

    # Variable names can even start with things that have normally other meanings in a Makefile, like `+` and `-`.

    +plus := a
    -minus := a

## := vs =

## Lazy evaluation

    colon_rval := a

    # Without colon, variable expands here as in c:

    colon := $(colon_rval)

    # Without the colon, expansion takes the value of $(a) at the time of usage:

    nocolon = $(colon_rval)
    colon_rval := b

    # Summary: always use colon unless you have a very good reason not to do so,
    # non colon equals is confusing and harder to decide!

    ## eval and =

        # lazy eval also works with eval built-in

        nocolon_eval_rvar := a
        nocolon_eval = $(nocolon_eval_rvar)

## +=

    # evaluates immediately like `:=` if lvar was first defined with `:=`
    # and later if it was first defined with `=` or `?=`

    colon_plus_rval := c

    colon_plus := a
    colon_plus += b
    colon_plus += $(colon_plus_rval)

    nocolon_plus = a
    nocolon_plus += b
    nocolon_plus += $(colon_plus_rval)

    colon_plus_rval := d

## ?=

    # Define variable only if it is not defined.

    question_var := a
    question_var ?= b

    # Empty variables are still defined.

    # Evaluation is defferred like in `=` (unlike `:=`)

    question_rval_defer := a
    question_var_defer ?= $(question_rval_defer)
    question_rval_defer := b

## Where variables can be used

    # You can use variables:

    # - to give other variable names
    # - to define rules
    # - to define recipes

    # Name a variable with another variable:

    varname := avarname
    $(varname) := avarname_val

    varname2 := varname

    # TODO why does this not work:

    # vardef := vardef_name := vardef_val
    # $(vardef)

    # Write a rule with a variable:

    rule := varrule: all

## Predefined variables

    # Variables that are automatically set, either at startup of MAKE or inside of rules
    # depending on the rule such as $@ or $?

    # some automatic variables can be defined in makefiles and have an effect

    ## MAKE

        # Should be used to call other makefiles recursively.

        # Major difference from literal `make`: uses the same interpreter,
        # e.g. `/usr/bin/mycustom/make`.

    ### MAKECMDGOALS

        # Contains all targets given at commandline invocation.

        # The default target if any does not count.

    ## MAKEFLAGS

        # Flags given at invocation, e.g. `make A=b`.

    ## MAKELEVEL

        # recursion level of make (how many makes called other makes)

        # starts at 0

    ## MAKEFILES

        # Input environment variable:
        # https://www.gnu.org/software/make/manual/html_node/MAKEFILES-Variable.html

    ## SHELL

        # Interpreter used to read each line.

    ## SUFFIXES

        # List of suffixes for which make automatically defines rules

    ## VPATH

        # Directories where to look for prerequisite files not found in current dir.
        #

## Substitution variables

## Replace extensions

    subst_var := a.c b.c c.c

## Substitution variables

.PHONY: all sh makecmdgoals

all:
	@[ '$(+plus)' = 'a' ]
	@[ '$(-minus)' = 'a' ]
	@[ '$(colon)' = 'a' ]
	@[ '$(nocolon)' = 'b' ]
	$(eval nocolon_eval_rvar := b)
	@[ '$(nocolon_eval)' = 'b' ]
	@[ '$(colon_plus)' = 'a b c' ]
	@[ '$(nocolon_plus)' = 'a b d' ]
	@[ '$(avarname)' = 'avarname_val' ]
	@[ '$(question_var)' = 'a' ]
	@[ '$(question_var_defer)' = 'b' ]
	@# You can use variables inside variables: varname2 -> avarname -> avarname:
	@[ '$($(varname2))' = 'avarname' ]
	@# if [ ! "$(vardef_name)" = "vardef_val" ]; then exit 1; fi
	$(multiline)
	@echo 'CURDIR       = $(CURDIR)'
	@echo 'MAKE         = $(MAKE)'
	@echo 'MAKECMDGOALS = $(MAKECMDGOALS)'
	@echo 'MAKEFLAGS    = $(MAKEFLAGS)'
	@echo 'MAKEFILES    = $(MAKEFILES)'
	@echo 'MAKELEVEL    = $(MAKELEVEL)'
	@echo 'SHELL        = $(SHELL)'
	@echo 'SUFFIXES     = $(SUFFIXES)'
	@echo 'VPATH        = $(VPATH)'
	@[ '$(subst_var:.c=.o)' = 'a.o b.o c.o' ]

$(rule)
	@echo varrule

# You can also use built-ins anywhere just like variables.
# Try this with `make sh`:
$(shell echo sh):
	@echo sh

makecmdgoals:
	@#
