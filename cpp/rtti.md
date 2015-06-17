# RTTI

Run time type information.

Any function that gets class information explicitly at runtime:

- `typeid`
- `dynamic_cast`

Google style 3.26 discourages this, since if you really need it your design is probably flawed.

Also using `typeid` on variables means that extra meta data must be kept about those variables.
