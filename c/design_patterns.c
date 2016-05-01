/*
# Design patterns

    A good way to learn is to look at existing libraries:

    - https://github.com/libgit2/libgit2
*/

#include "common.h"

int main(void) {
    /*
    # Objects

        Prefix every function that acts on an object with the name of the object.

        The first non return parameter of the function
        should be a pointer to the struct, AKA self in many languages.

        E.g., libgit 2 repository methods are all of the type:

            git_repository_X(git_repository* repo, ...);
    */

    /*
    # Private struct fields

        Opaque structs and expose public fields through getter and setter methods.
    */

    /*
    # Static fields

        Static.

        For private, don't include on header.
    */

    /*
    # Namespaces like in C++

        Prefix everything public in your entire libray with a single identifier.

        E.g., in libgit2, every public identifier starts with `git_`.

        Of course, with this it is not possible to omit the namespace like in C++,
        but many C++ coding styles don't allow that either because it becomes confusing what is what.
    */

    /*
    # Inheritance

        The closest substitution to inheritance is struct inclusion / composition:

            typedef struct derived {
                struct base* base;
            }

        The difference is that you cannot automatically give base methods to the inheriting class.

        But even in C++, object composition is considered a more flexible approach than
        inheritance and is used in some cases.
    */

    return EXIT_SUCCESS;
}
