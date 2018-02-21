.POSIX:

# Set a variable for a single target.

# TODO check: It is only possible to set one per line.

# TODO check: not possible to define on the same line
# as the actual rule to avoid repeating the target.
# But we could work around that by storing the target in a variable.

x := 0

.PHONY: a

a: x := 1
a:
	@[ '$x' = '1' ]

b:
	@[ '$x' = '0' ]
