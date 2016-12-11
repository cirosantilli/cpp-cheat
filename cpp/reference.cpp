/*
# Reference

# &

    Basically aliases, similar to `int* const` pointers or Java objects.

    Useful only for function arguments or / return values. In that case the pros are:

    - callers that have an object don't need to dereference it with `&`

    - it is self documenting on the code that the given reference always points to the same thing
        either to modify it or to pass it efficiently without copy.

    The cons are:

    - callers don't know without looking at the signature if they are passing references or copies,
        and whether they should expect that it is possible that the function modifies their object.

    - http://stackoverflow.com/questions/7058339/c-when-to-use-references-vs-pointers
*/

#include "common.hpp"

int getInt() { return 0; }

std::string getString() { return "abc"; }

/*
// WARN: reference to local var returned
int& getIntRef() {
    int i = 0;
    return i;
}
*/

/*
The returned i reference cannot be modified.
TODO use
*/
const int& getIntConstRef(int& i) {
    i++;
    return i;
}

class Class {

    public:

        int iPublic;

        int& getRefIPublic() {return this->iPublic;}

        /// Value cannot be changed.
        const int& getPrivateConstRef() const {return this->iPrivate;}

        // ERROR: const method cannot return noncosnt pointer!
        //int* getPrivateAddress() const {return &this->iPrivate;}

        const int* getPrivateAddressConst() const {return &this->iPrivate;}

        // Value can be changed
        int& getPrivateRef() { return this->iPrivate; }

        // ERROR: const method cannot return noncosnt reference!
        //int& getPrivateRef() const {return this->iPrivate;}

    private:

        int iPrivate;
};

// Pass by reference.

    //http://stackoverflow.com/questions/114180/pointer-vs-reference

    void byref(int& i) {i++;}
    void bypointer(int *i) {(*i)++;}

    void bypointerConst(const int*& ip, const int*& jp) {
        ip = jp;
    }

int main() {
    // Basic usage as function parameters that are return values.
    {
        int i = 0;
        byref(i);
        assert(i == 1);
    }

    /*
    References have the same address of the variables.

    Therefore:

    - if declared inside the same function as the value, no extra memory / dereferencing
        needs to be used for references, the compiler can figure everything out at compile time.

    - if declared as function arguments, references may be implemented as implicit pointers passing,
        sharing therefore the disadvantages of pointers.

        Therefore, if you want to be sure of efficiency, pass built-in types by value and not by reference.
    */
    {
        // They have the same address.
        {
            int i = 0;
            //int& ia = i;
            int& ia = i;
            ia = 1;
            assert(i == 1);
            assert(&i == &ia);
        }

        /*
        For the same reason, it is possible to initialize a reference from another reference.
        */
        {
            int i = 0;
            int& ia = i;
            int& ia2 = ia;
            ia2 = 2;
            assert(i == 2);
        }
    }

    /*
    ERROR: Must not initialize non-const ref with a rvalue.

    Can however do that for const references.

    The same goes for function parameters.
    */
    {
        //int& ia = 0;
        //std::string& s = getString();
        const std::string& s = getString();
        //byref(1);
    }

    /*
    ERROR: references must be initialized imediatelly
    otherwise, how can they be initalized in the future?

    For references in constructors, they must be initialized at the initialization list.
    */
    {
        //int& ia;
    }

    /*
    It is possible to get references from pointers.
    */
    {
        int i = 0;
        int* ip = &i;
        int& ia = *ip;
        ia = 1;
        assert(i == 1);

        // ERROR: & must get a variable/dereferenced pointer, not pointers themselves!
        {
            //int& ia = &i;
        }
    }

    /* It is not possible to make an array of references. */
    {
        int i = 1;
        int j = 2;

        // ERROR: array of references forbidden
        //int& is[2] = {i,i};
    }

    /*
    # const references

        References that do not allow one to modify the value of the variable.
    */
    {
        // It is possible to make a const reference from a non-const object.
        {
            int i = 1;
            const int& cia = i;

            // ERROR: const references cannot be modified
            //cia = 2;
        }

        // It is possible to make a const reference form a const object.
        {
            const int ci = 1;
            const int& cia = ci;

            // ERROR: const references cannot be modified
            //cia = 2;
        }

        // The rules imposed by the compiler make sure that it is hard
        // or impossible to cheat references by mistake.
        {
            int i = 1;
            const int& cia = i;

            // ERROR: invalid conversion
            //int& ia = cia;

            // ERROR: invalid conversion
            //int *ip = &cia;
        }

        /*
        const references can be initialized by rvalues!

        This cannot be wrong since they cannot be modified,
        so it is not possible to modify the non-existent variable.

        In this case what happens is that a simple copy takes place.

        One case in which this rule is very important is parameter passing to functions.

        For exapmle, the following would be bad:

            void f(int& i) {
                i++;
            }

            ...

            f(1);
                //does not compile

        and is impossible, but:

            void f(const int& i) {
                //i++;
                    //impossible
            }

            f(1);

        is ok, since it is impossible to change i in the function if it is const
        */
        {
            // Initialization from a literal.
            {
                const int& i = 1;
                assert(i == 1);
            }

            /*
            Initialization from a non-reference function return.

            Functions that return references return lvalues,
            so an example with such a function would not be meaningful.
            */
            {
                const int& i = getInt();
                assert(i == 0);
            }

            /*
            # Lifetime extension

                If you assign a const reference to the return of a function,
                it extends the lifetime of the returned object.

                Note that not every const reference extends lifetime, e.g. arguments don't.

                - http://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
                - http://stackoverflow.com/questions/2784262/does-a-const-reference-prolong-the-life-of-a-temporary
                - http://stackoverflow.com/questions/2615162/return-value-not-a-reference-from-the-function-bound-to-a-const-reference-in
            */
            {
                struct C {
                    static std::string f() {
                        return "abc";
                    }
                };
                const std::string& s = C::f();
                assert(s == "abc");
            }
        }
    }

    /*
    # Reference to pointer

        Like for other variable, references can be made to pointer variables.
    */
    {
        {
            int i = 0;
            int j = 1;
            int *ip = &i;
            int *jp = &j;
            int*& ipa = ip;
            int*& jpa = jp;

            jpa = ip;
                //now `jp` is the same as `ip`!

            *jp = 2;
            assert(i == 2);
                //therefore modifying what `jp` points to modifies `i`!

            // ERROR: makes no sense: cannot have a pointer to `int&`
            //int&* ipaBad = ip;

            // ERROR: `&i` is an rvalue. Cannot initialize a non const reference to it.
            //int&* ipaBad = &i;
        }

        /*
        # Reference to pointer and const

            Just like for pointers to pointers in C, the rules prevent `const` variables
            from being modified.
        */
        {
            /*
            Obviously, cannot remove const qualifiers, or it would be easy to modify constants.
            */
            {
                const int c = 0;
                const int *ip = &c;
                //int *&ipa = ip;
                //int *ipa = ip;
                //*ipa = 1;
            }

            /*
            `const int*& = int*` initialization fails for the same reason that `const int* = (int*)` fails in C:
            this would allow for constant modification.
            */
            {
                //If (1) were possible below, then it would be possible to change the value of the constant c.
                {
                    /*
                        int *ip = NULL;
                        const int*& ipa = ip;   // (1) THIS is not possible
                        const int c = 0;
                        ipa = &c;               // OK because ipa is const. `ip` points to `c`
                        *ip = 1;                // OK because ip  is not const
                    */
                }

                /*
                This is different without the reference, because in this case
                it would not be possible to change the const variable.

                Just like in C, the issues only show up in pointer dimensions > 1,
                and the reference behaves like a pointer.
                */
                {
                    int *ip = NULL;
                    const int* ipa = ip;   // (1) THIS is ok without the reference, a new pointer is created
                    const int c = 0;
                    ipa = &c;              // OK because ipa is const. ip still points to NULL
                    //*ip = 1;             // does not change the constant, ip still points to NULL
                }
            }
        }

        /*
        What to do if:

        -   a function modifies what pointers point to but not the object pointed to.

            It therefore takes

        -   we want to pass pointers to that function, modify what they point to,
            and then outside of the function modify the object being pointed to?

        Is this a valid use case for `const_cast`?
        */
        {
            // The motivation: functions.
            {
                int i = 0;
                int j = 1;
                int *ip = &i;
                int *jp = &j;

                // If those were const, the function call would work,
                // but not the `*ip = 2`;
                //const int *ip = &i;
                //const int *jp = &j;

                // Cannot initialize `const int*&` with `int*&`.
                //bypointerConst(ip, jp);

                *ip = 2;
                //assert(j == 2);
            }

            // Same problem simplified without functions.
            {
                int i = 0;
                int *ip = &i;

                // Possible.
                //int*& ipa = ip;

                // TODO why is this not possible.
                //const int*& ipa = ip;
            }

            // But this is possible?
            {
                int i = 0;
                const int& ia = i;
            }
        }
    }

    /*
    Single line initialization syntax.

    Like the pointer symbol `*`, the reference symbol `&` needs to be duplicated for each new reference variable.
    */
    {
        // OK: both ia and ja are references
        {
            int i = 1;
            int j = 2;
            int &ia = i, &ja = j;

            ia = -1;
            ja = -2;

            assert(i == -1);
            assert(j == -2);
        }

        // Bad: ja is a new int, not a reference
        {
            int i = 1;
            int j = 2;
            int& ia = i, ja = j;

            ia = -1;
            ja = -2;

            assert(i == -1);
            assert(j ==  2);
        }

        // With references to pointers it looks like this.
        {
            int i = 0;
            int j = 1;
            int *ip = &i;
            int *jp = &j;

            int *& ipa = ip, *& jpa = jp;

            jpa = ip;
            *jp = 2;
            assert(i == 2);
        }
    }

    /*
    # return reference from function

        Just like for pointers, you have to watch scope.
        If the original object dies, you get a dangling reference.

        - http://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil

        There is also some rule about const local references:

        - http://stackoverflow.com/questions/2784262/does-a-const-reference-prolong-the-life-of-a-temporary
    */
    {
        /*
        One simple case in which lifetime is simple to guarantee is
        returning members from objects which the callee owns. For example:
        */
        {
            Class c;
            int& ia = c.getRefIPublic();
            ia = 0;
            assert(c.iPublic == 0);
            ia = 1;
            assert(c.iPublic == 1);
        }

        // You can modify a private if you non-const reference to it
        {
            Class c;
            int& ia = c.getPrivateRef();
            ia = 0;
            assert(c.getPrivateRef() == 0);
            ia = 1;
            assert(c.getPrivateRef() == 1);
        }

        // If the reference is const it does not work anymore.
        {
            Class c;

            {
                const int& ia = c.getPrivateConstRef();
                //ia = 1;
            }

            // ERROR: invalid initialization
            {
                //int& ia = c.getPrivateConstRef();
            }
        }

        /*
        In C, all functions return rvalues, although if a function returns a pointer
        and that pointer is dereferenced it becomes an lvalue,
        so the following works:

            (*ret_int_ptr()) = 1;

        In C++, there is an exception: all functions that return references return lvalues directly.
        */
        {
            // OK the returned i reference is not local
            struct C {
                static int& f(int& i) {
                    i++;
                    return i;
                }
            };
            int i = 0;
            (C::f(i)) = 2;
            assert(i == 2);
        }
    }
}
