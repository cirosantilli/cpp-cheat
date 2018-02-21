.POSIX:

## Automatic variables.

	# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

	## $@

		# Target.

	## $<

		# First dependency.

	## $^

		# All dependencies.

a: b c
	[ '$@' = 'a' ]
	[ '$<' = 'b' ]
	[ '$^' = 'b c' ]

b:

c:
