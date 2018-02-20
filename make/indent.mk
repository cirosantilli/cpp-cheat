.POSIX:
# This is to terminate the .POSIX: target,
# or else following tab indented commands would be put inside it.
a := b

# It you put a command that is not a valid make statment, you get `"commands commence before first target"`.
# http://stackoverflow.com/questions/4713663/gnu-make-yields-commands-commence-before-first-target-error
# So just use spaces always.

# ERROR:

#	echo a

# Valid Make commands however are interpreted:

	a := c

# The Linux kernel currently has a mixture of 2, 4, and 8 spaces for non-rule Makefile indentation,
# so don't look at it for style guidance!

a:
	[ '$a' = 'c' ]
