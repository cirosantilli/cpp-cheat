"""
## Value

Let's explore Value objects.

They are returned by:

- gdb.parse_and_eval
- gdb.read_var
"""

gdb.execute('set $a = 12')
gdb.execute('set $b = 3.4')

# Returned by parse_and_eval
a = gdb.parse_and_eval('$a')
b = gdb.parse_and_eval('$b')

# Return Value objects.
print(type(a))
print(type(b))

print(a.type)
print(b.type)

# str is defined
print(a)
print(b)

# Conversion to scalars are defined.
print(a + 1)
print(b + 1.0)
