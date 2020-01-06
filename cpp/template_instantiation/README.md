Template instantiation saves us from infinite compilation times because whenever you modify a header, the build system (correctly) rebuilds everything that includes that header.

They can also save object size (and likely a little bit of time) because templates are re-instantiated for each object file, unless users mark it as extern on every file, which they won't remember to do

* https://stackoverflow.com/questions/8130602/using-extern-template-c11/59614090#59614090
* https://stackoverflow.com/questions/2351148/explicit-instantiation-when-is-it-used
* https://en.cppreference.com/w/cpp/language/class_template#Explicit_instantiation

We can also confirm with `nm -C` that the `main.o` object file does not contain a definition of `MyClass`, in that case because `MyClass` is not a complete definition because `f` is not defined.
