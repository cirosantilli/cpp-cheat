// # Implicitly defined functions
//
// - https://stackoverflow.com/questions/3734247/what-are-all-the-member-functions-created-by-compiler-for-a-class-does-that-hap/53316960#53316960
// - https://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi/53315860#53315860
// - https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration/53317010#53317010
// - https://stackoverflow.com/questions/12340257/default-vs-implicit-constructor-in-c
// - https://blog.mozilla.org/nfroyd/2015/08/20/explicit-is-better-than-implicit-c-implicitly-defined-member-functions/
// - https://en.cppreference.com/w/cpp/language/copy_constructor
// - https://en.cppreference.com/w/cpp/language/move_constructor
// - https://en.cppreference.com/w/cpp/language/copy_assignment
// - https://en.cppreference.com/w/cpp/language/move_assignment

#include <cassert>
#include <string>

struct Default {
    int i;
    Default()                          = default;
    Default(const Default&)            = default;
    Default& operator=(Default&)       = default;
    Default& operator=(const Default&) = default;
    Default(Default&&)                 = default;
    Default& operator=(Default&&)      = default;
    ~Default()                         = default;
};

struct Instrument {
    int i;
    static std::string last_call;
    Instrument()                             { last_call = "ctor"; }
    Instrument(const Instrument&)            { last_call = "copy ctor"; }
    Instrument& operator=(Instrument&)       { last_call = "copy assign"; return *this; }
    Instrument& operator=(const Instrument&) { last_call = "copy assign const"; return *this; }
    Instrument(Instrument&&)                 { last_call = "move ctor";  }
    Instrument& operator=(Instrument&&)      { last_call = "move assign"; return *this; }
    ~Instrument()                            { last_call = "dtor"; }
};
std::string Instrument::last_call;

int main() {
    // See what the default constructors are doing.
    {
        // Default constructor.
        Default ctor;
        // i is uninitialized.
        // std::cout << ctor.i << std::endl;
        ctor.i = 1;

        // Copy constructor.
        Default copy_ctor(ctor);
        assert(copy_ctor.i = 1);

        // Copy assignment.
        Default copy_assign;
        copy_assign = ctor;
        assert(copy_assign.i = 1);

        // Copy assignment const.
        const Default const_ctor(ctor);
        Default copy_assign_const;
        copy_assign_const = const_ctor;
        assert(copy_assign_const.i == 1);

        // Move constructor.
        Default move_ctor(std::move(ctor));
        assert(move_ctor.i == 1);

        // Move assignment.
        Default move_assign;
        move_assign = std::move(ctor);
        assert(move_assign.i == 1);
    }

    // Check that the constructors are called by these calls.
    {
        // Default constructor.
        Instrument ctor;
        assert(Instrument::last_call == "ctor");

        // Copy constructor.
        Instrument copy_ctor(ctor);
        assert(Instrument::last_call == "copy ctor");

        // Copy assignment.
        copy_ctor = ctor;
        assert(Instrument::last_call == "copy assign");

        // Copy assignment const.
        const Instrument const_ctor(ctor);
        Instrument copy_assign_const;
        copy_assign_const = const_ctor;
        assert(Instrument::last_call == "copy assign const");

        // Move constructor.
        Instrument move_ctor(std::move(ctor));
        assert(Instrument::last_call == "move ctor");

        // Move assignment.
        Instrument move_assign;
        move_assign = std::move(ctor);
        assert(Instrument::last_call == "move assign");

        // Destructor.
        {
            Instrument dtor;
        }
        assert(Instrument::last_call == "dtor");
    }
}
