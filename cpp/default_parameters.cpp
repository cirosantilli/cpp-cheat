/*
# Default parameters

    Does not use name mangling: caller just chooses a value for missing arguments.

# Default arguments for references

    There seems to be no standard way of doing that without using extra memory / verbosity.

    http://stackoverflow.com/questions/2816293/passing-optional-parameter-by-reference-in-c
*/

#include "common.hpp"

int defaultArg(int i, int j = 0) { return i + j; }

// ERROR: this overload would make calls to the above ambiguous.
//int defaultArg(int i) { return i; }

int defaultArgDeclaration(int, int = 0);
int defaultArgDeclaration(int i, int j) { return i + j; }

int defaultArgDefinition(int, int);
int defaultArgDefinition(int i, int j = 0) { return i + j; }

// ERROR
//int defaultArgDefinitionAndDeclaration(int, int = 0);
//int defaultArgDefinitionAndDeclaration(int i, int j = 0) { return i + j; }

// ERROR
//int defaultToAnotherArg(int i, int j = i) { return i + j; }

int main() {
    // Basic examples.
    assert(defaultArg(1)    == 1);
    assert(defaultArg(1, 1) == 2);

    /*
    Definition vs declaration:
    http://stackoverflow.com/questions/4989483/where-to-put-default-parameter-value-in-c

    Within a single compilation unit, both work.

    But put it always only on the declaration, which is what includers will see.
    */
    {
        assert(defaultArgDeclaration(1)    == 1);
        assert(defaultArgDeclaration(1, 1) == 2);

        assert(defaultArgDefinition(1)    == 1);
        assert(defaultArgDefinition(1, 1) == 2);

        // Not possible in both.
        //defaultArgDefinitionAndDeclaration(1);
    }

    // Cannot default one parameter to another:
    // http://stackoverflow.com/questions/1880866/c-c-default-argument-set-as-a-previous-argument
    //defaultToAnotherArg(1);
}
