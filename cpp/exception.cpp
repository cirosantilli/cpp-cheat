/*
# exception

# throw

#catch

    Great source: <http://www.cplusplus.com/doc/tutorial/exceptions/>

    Application: centralize error handling in a single place, even if outside executing functions.

    The application is similar to C's longjmp, but the implementation is different.
    TODO how are they implemented in assembly code? <http://stackoverflow.com/questions/490773/how-is-the-c-exception-handling-runtime-implemented>
    It is more magic than C longjmp as it does type checking.

    Anything can be thrown, but the most standard and extensible method is to throw subclasses of exception,
    so just do that always.

    There is no finally block: <http://stackoverflow.com/questions/161177/does-c-support-finally-blocks-and-whats-this-raii-i-keep-hearing-about>
    Deinitializations are left for destructors.

    # Standard exceptions.

        - exception         base class of all stdlib exceptions.
        - bad_alloc         thrown by new on allocation failure
        - bad_cast          thrown by dynamic_cast when fails with a referenced type
        - bad_exception     thrown when an exception type doesn't match any catch
        - bad_typeid        thrown by typeid
        - ios_base::failure thrown by functions in the iostream library

# exception safety

    Different levels of how much excpetion handlind a function does:

    <http://en.wikipedia.org/wiki/Exception_safety>
*/

#include "common.hpp"

void exception_func_int() {
    throw 1;
}

class myexception: public std::exception {
    virtual const char* what() const throw() {
        return "myexception::what()";
    }
};

// All exceptions are catchable (default):
void exception_func_all() { throw 0; }

#if __cplusplus < 201703L
// Only int exceptions are catchable
void exception_func_int_only(bool throw_int) throw (int) {
    if (throw_int)
        throw 1;
    else
        throw 'c';
}

// Only int and exception or derived excpetions are catchable:
void exception_func_int_exception_only(int which) throw (int, std::exception) {
    switch (which) {
        case 0: throw 0; break;
        case 1: throw myexception(); break;
        default: throw 'c'; break;
    }
}
#endif

// No exceptions are catchable
void exception_func_none() throw() {throw 1;}

void exception_func_none_wrapper() {
    exception_func_none();
}

// The destructor of this class throws an exception!!!
class ExceptionDestructor {
    public:
        ~ExceptionDestructor() { throw std::exception(); }
};

void ExceptionDestructorCaller() {
    ExceptionDestructor e;
}

int main() {
    /*
    Exceptions can jump out of functions.

    This is their main reason for existing!
    */
    {
        try {
            exception_func_int();
        } catch (int i) {
            assert(i == 1);
        }
    }

    /*
    # std::exception

        Anything can be thrown, including classes and base types.

        All stdlib exceptions inherit from `exception`, so it is a good idea to only throw
        things inherited from it.

        `std::exception` has limited use since its constructor does not take any arguments,
        so you cannot describe the error. Some stdlib derived class constructors do however.
    */
    {
        try {
            throw std::exception();
        } catch (std::exception e) {
        }
    }

    /*
    Catch blocks work like function overloads and catch by type.
    */
    try {
        throw 'c';
    } catch (int i) {
        assert(false);
    } catch (char c) {
    }

    /*
    `...` is the default case
    */
    try {
        throw 1.0;
    } catch (int i) {
        assert(false);
    } catch (char c) {
        assert(false);
    } catch (...) {
    }

    /*
    Derived classes.

    Just like for function overloading, base classes catch for derived classes.
    */
    {
        try {
            throw myexception();
        } catch (std::exception& ex) {
        }
        /*
        This compiles, but generates a warning, since the first catch will always catch instead of this one.
        */
        //catch (myexception& ex)       {assert(false);}
        catch (...)                     {assert(false);}

        /*
        this is a more common exception ordering, first derived then base.
        */
        {
            try {
                throw myexception();
            } catch (myexception& ex) {
            } catch (std::exception& ex) {
                assert(false);
            } catch (...) {
                assert(false);
            }
        }
    }

    /*
    # what

        Returns a string which contains information about the exception.

        Many stdlib exceptions simply return the error message given on the constructor.
    */
    {
        std::string msg = "custom message";
        std::ios_base::failure e(msg);
        // TODO worked in GCC 4.8, failed in GCC 5.1.
        //assert(e.what() == msg);
    }

    /*
    # uncaught exceptions

        Uncaught exceptions explose at top level and terminate the program.

        Check out the error messages generated by each exception.

        Classes that derive from exception and implement `what()` can print custom messages,
        which may contain useful debug info. This is a major point in favor of using exception
        classes instead of base types.
    */
    {
        //throw 1;
        //throw 'c';
        //throw 1.0;
        //throw myexception();
    }

#if __cplusplus < 201703L
    /*
    # exception specifications

        Functions can specify which exceptions are catchable with the following syntax.

        Deprecated since C++11, removed in C++17, noexcept is favored instead.

        https://stackoverflow.com/questions/47284705/c1z-dynamic-exception-specification-error
    */
    {
        try {
            exception_func_int_only(true);
        } catch (int i) {
        } catch (...) {
            assert(false);
        }

        try {
            //exception_func_int_only(false);
        } catch (...) {
            /* not even ... this can catch non int exceptions thrown by this function */
        }

        try {
            exception_func_int_exception_only(1);
        } catch (int i) {
        } catch (myexception& ex) {
        } catch (...) {
            assert(false);
        }

        try {
            //exception_func_none();
        } catch (...) {
            /* no exception thrown by this function is catchable */
        }

        try {
            //exception_func_none_wrapper();
        } catch (...) {
            /* the same goes if we wrap the function */
        }
    }
#endif

    /*
    # exception from destructor

        Never throw an exception from a destructor.

        Destructors are meant to clean up after exceptions, so if you throw exceptions from them,
        things get messy.

        C++ specifies that if this happens during stack unwinding, the program may terminate!

        What to do to avoid that: <http://stackoverflow.com/questions/130117/throwing-exceptions-out-of-a-destructor>

        The following code could lead to that.
    */
    if (0) {
        try {
            ExceptionDestructor e;
        } catch (...) {
        }

        try {
            ExceptionDestructorCaller();
        } catch (...) {
        }
    }

#if __cplusplus >= 201103L
    /*
    # noexcept

        Improved version of `throw` for functions.

        `throw` for functions becomes deprecated in C++11.

        TODO
    */
    {
    }
#endif
}
