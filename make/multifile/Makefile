.POSIX:

A := a
B := b

## Export

    # Export all variables to makefiles called from this one:

        export

    # Export only specific variables:

        # export A B

    # Preventin exporting specific variables:

        unexport B

    # Works even with variables that were explicitly previously exported.

.PHONY: all a

all:
	## MAKE variable

	# https://www.gnu.org/software/make/manual/html_node/MAKE-Variable.html#MAKE-Variable

	# Standard way to call on different directory:

		$(MAKE) -C d

	# -C: call make on a different directory

	# Always use the MAKE variable since this does good magic for you

	# Equivalent way:

		cd d && $(MAKE)

	# `-f`: use a given file as a makefile

		$(MAKE) -f makefile-other

	# `-f` does not change the current directory to the directory of the given file:

		$(MAKE) -f d/makefile

	@# include:

		@if [ ! "$(include_var)" = "include_var_val" ]; then exit 1; fi
