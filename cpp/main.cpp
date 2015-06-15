/*
C++ cheatsheat.

Features which are identical to C will not be described.
*/

/*
# Linux specifics

    The main c++ lib on linux is the GNU Standard C++ Library.

    Shared object name: `libstdc++.so`.

    Website: <http://gcc.gnu.org/libstdc++/>

    Get source code: seems to be on the same tree as gcc?

        git clone git://gcc.gnu.org/git/gcc.git

    -   the so is usually located at

            /usr/lib/i386-linux-gnu/libstdc++.so.X

        If it is not there then

            locate libstdc++

    -   std headers are usually located at

            /usr/include/c++/4.X/`.

        If not, try:

            locate /iostream

    -   the Ubuntu package is called `libstdc++6.X`. `dpkg -l | grep libstd`

    With `g++` the C++ standard library is linked against automatically.
    This does not happen when compiling with `gcc`, and is one of the many reasons why you should use `g++`
    whenever compiling C++ instead of `gcc`.
*/

#include "common.hpp"

class Class {};

// struct

    template<class T>
    struct BaseStruct {
        T i;
        BaseStruct(T i) : i(i) {}

        protected:
            int iProtected;

        private:
            int iPrivate;
    };

    struct DerivedStruct : BaseStruct<int> {
        DerivedStruct(int i) : BaseStruct(i) {
            iProtected = i;
        }
    };


// # global scope

    int global = 0;

    // Differently from C, expressions can be evaluated to initialize globals.

        int global2 = global + 1;
        int ret1() {
            callStack.push_back("before main!");
            return 1;
        }
        int global3 = ret1();

    // ERROR: only single expressions that initialize a global are allowed however.

        //global = 1;
        //if (1){}
        //callStack.push_back("global");

// #preprocessor

    // The C++ preprocessor it Turing complete by mistake.
    //
    // This leads to the concept of Template Metaprogramming,
    // which allows you to write code that is ultra DRY / runs fast but is very large.
    // TODO confirm.

// string

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

//File IO

    void ios_write_fail(std::string path) {
        throw std::ios_base::failure("Error: Could not write to file: " + path);
    }

    void ios_read_fail(std::string path) {
        throw std::ios_base::failure("Error: Could not read file: " + path);
    }

    /**
    Read entire file into a string at once.
    */
    void read_file(std::ifstream &ifs, std::string &data_read) {
        ifs.seekg(0, std::ios::end);
        size_t size = ifs.tellg();
        data_read.resize(size);
        ifs.seekg(0);
        ifs.read(&data_read[0], size);
        ifs.close();
    }

//to_str

    template <class K, class V>
    std::string map_to_str(std::map<K,V> map) {
        std::stringstream result;
        for (auto& pair : map) {
            result << pair.first << ":" << pair.second << ", ";
        }
        return result.str();
    }

// Attributes.

    void noreturn_func [[ noreturn ]] () { throw 1; }

// Misc

    bool odd(int i){ return (i % 2) == 1; }

/*
# main

    # main signature

        - http://stackoverflow.com/questions/4207134/what-is-the-proper-declaration-of-main
        - http://stackoverflow.com/questions/1621574/can-the-arguments-of-mains-signature-in-c-have-the-unsiged-and-const-qualifie

        Much like in C, only:

            int main();
            int main(int, char*[]);

        are required to work, but more likely work as well.

    # Call main from the program

        In C++, cannot be called from anywherelse in the program, including recursively:
        http://stackoverflow.com/questions/2128321/can-main-function-call-itself-in-c

        This restriction does not seem to exist in C.
*/
int main() {

    // # Scope
    {
        /*
        # typedef struct

        # typedef class

            # struct keyword omission

                Unlike in C, struct tags and variable names live in the same namespace.

                In C++ you can normally omit `struct`
                `struct s` is called an #elaborated-type-specifier.
                http://stackoverflow.com/a/14261176/895245

                But if there is ambiguity, the only way to refer to the struct
                is by appending `struct`.
        */
        {
            int s = 1;
            struct s {int i;};
            assert(s == 1);
            // ERROR
            //s t = {1};
            struct s t = {1};
            assert(t.i == 1);

            int c = 1;
            class c { public: int i; };
            assert(c == 1);
            // ERROR
            //c u = {1};
            class c u = {1};
            assert(u.i == 1);
        }
    }

    /*
    # assign operator

        Unlike in C, C++ assign operator returns lvalues!

        TODO rationale. Related to return refs from functions?
    */
    {
        int i = 0, j = 1, k = 2;

          (i = j) = k;
        /*^^^^^^^^^
          |
          returns a lvalue pointing to `i`

          Therefore is the same as:

          i = j;
          i = k;
        */

        assert(i == 2);
        assert(j == 1);
        assert(k == 2);

        // ERROR: as in C, most other operators do not return lvalues
        //(i + j) = k;
    }

    /*
    # constant expressions at compile time

        http://en.cppreference.com/w/cpp/language/constant_expression

        Constant expressions at compile time can be used in contexts where non constants cannont:

        - array lengths at array declaration
        - numeric template parameters

        The compiler is able to determine which expressions are constant recursively.

        Note that variables with the keyword `const` may or may not be constant expressions.
        depending on how they are initialized.

        Those defined with the keyword constexpr however are ensured by the compiler to be
        compile time constants.
    */

    /*
    Get array length, find array length: <http://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array>

    Besides the C sizeof method which does not work for pointers and has lots of duplication, C++ offers:
    */
    {
        // Vector class. Has overhead, but probably the best option given its flexibility.

        // #array class. No overhead. Fixed size. Template based.
        {
            // WARN: double brackets required TODO why
            //std::array<int, 3> a{0, 1, 2};

            std::array<int, 3> a{{0, 1, 2}};
            assert(a.size() == 3);
        }

        // Method which I don't understand.
        {
            //template<class T, size_t N>
            //size_t size(T (&)[N]) { return N; }
        }
    }

    /*
    # array size from variables

        In C++, any constant expression at compile time can be used as an array size.

        This includes in particular intetegers declared as `const` and initialized by a constant expression,
        and in C++11 all `constexpr` variables.
    */
    {
        std::srand(time(NULL));

        {
            int i = 1;
            i = std::rand();
            // ERROR: the size would not be fixed
            //int is[i];
        }

        {
            // Compile time constant since the literal 1 is a constant expression.
            const int ci = 1;
            // Cannot do that, so the size is fixed!
            //ci = 2;
            int is[ci];
        }

        // ERROR: the compiler is able to see that ci is not a compile time constant
        {
            const int ci = std::rand();
            //int is[ci];
        }
    }

    /*
    # vla

        called variable length array VLS

        C99 supports this

        compiler implementation:
        must increment/decrement stack pointer at each array
        meaning, one extra multiplication and sum for every VLA declared

    */
    {
        {
            //cin >> i;
            //int is4[i];
        }

        {
            // ERROR: may not be initialized
            //cin >> i;
            //int is4[i] = {1, 2};
        }
    }

    // # enum
    {
        // Unlike C, already does typedef, no need to write enum all the time.
        {
            enum E {A, B, C};
            E e = A;
        }

#if __cplusplus >= 201103L
        // Set storage size.
        {
            enum E : char {A, B, C};
            assert(sizeof(E) == sizeof(char));
        }
#endif
    }

    // # for
    {

        //you can define i inside the for scope only
        int is[] = {0, 1, 2};
        for (int i=0; i<3; i++)
        {
            assert(i == is[i]);
            // ERROR: already declared in this scope
            //int i;
        }
    }

#if __cplusplus >= 201103L

#endif

    /*
    # struct

        Structs in C++ are very similar to classes: support access modifiers,
        inheritance, constructors, templates, etc.

        The major difference between them is that the default access modifier for structs
        is public, while for classes it is private.

        This is why structs are used on many simple short language examples:
        no public line is needed.

        The Google C++ style guide recommends using struct only if there is no constructors,
        and classes otherwise.

        <http://stackoverflow.com/questions/2750270/c-c-struct-vs-class>
    */
    {
        struct DerivedStruct s(1);
        assert(s.i == 1);
    }

    /*
    # RTTI

        Run time type information.

        Any function that gets class information explicitly at runtime:

        - `typeid`
        - `dynamic_cast`

        Google style 3.26 discourages this, since if you really need it your design is probably flawed.

        Also using typeid on variables means that extra meta data must be kept about those variables.
    */

    /*
    # typeid

        Get type of variables.

        Can be done for both types and variables of the type.

        Returns objects of `type_info`

    # type_info

        Type returned by `typeid`.
    */
    {
        /*
        typeid returns `type_info`.

        However copy and assign for type_info are private,
        so the following fails.
        */
        {
            //std::type_info t = typeid(int);
            //std::type_info t(typeid(int));
        }

        // type_info implements `==` and `!=`.
        //
        // typeid's of different types are always different.
        {
            int i, i1;
            int& ia = i;
            Class c;

            assert(typeid(i)  == typeid(int) );
            assert(typeid(ia) == typeid(int&));
            assert(typeid(i)  == typeid(i1)  );
            assert(typeid(i)  != typeid(c)   );
        }

        /*
        `name`: return a string representation of the type.

        The exact string is implementation defined.

        `name()` is implementation defined.

        On GCC, you can demangle with `__cxa_demangle`:
        http://stackoverflow.com/questions/4465872/why-typeid-name-returns-weird-characters-using-gcc
        */
        {
            std::cout << "typeid(int).name() = " << typeid(int).name() << std::endl;
        }

        // before: <http://stackoverflow.com/questions/8682582/what-is-type-infobefore-useful-for>
        // hash_code: return a size_t hash of the type
    }

    /*
    # type_index

        Wrapper around type_info that allows copy and assign.
    */
    {
        std::type_index t = typeid(int);
    }

    /*
    # type_traits

        <http://www.cplusplus.com/reference/type_traits/>
    */
    {
    }

    // # stdlib
    //
    // # Standard library
    {
        // # string
        {
            // Initialize from string literal.
            {
                std::string s = "abc";
            }

            // cout works as expected.
            {
                std::string s = "abc";
                std::stringstream oss;
                oss << s;
                assert(oss.str() == "abc");
            }

            /*
            # + for strings

            # cat

            # concatenate.

                Creates a new string.

                The only way to do inline this without creating a new string seems to be by using stringstream.
                http://stackoverflow.com/questions/662918/how-do-i-concatenate-multiple-c-strings-on-one-line
            */
            {
                std::string s = "ab";
                std::string s1 = "cd";
                assert(s + s1   == "abcd");
                assert(s + "cd" == "abcd");
                assert("cd" + s == "cdab");
            }

            // length
            {
                std::string s = "abc";
                assert(s.length() == 3);
            }

            {
                std::string s = "abc";
                s[0] = 'A';
                assert(s == "Abc");

                // BAD: no born check! Compiles.
                //s[3] = 'd';
            }

            /*
            # lowercase

                http://stackoverflow.com/questions/313970/stl-string-to-lower-case
            */
            {
                // Best stdlib way with transform:
                std::string s = "AbCd1_";
                std::transform(s.begin(), s.end(), s.begin(), ::tolower);
                assert(s == "abcd1_");

                //Boost has a single function: boost::algorithm::to_lower(str);
            }

            /*
            # c_str

                Convert std::string to C null terminated char* string.
            */
            {
                std::string s = "abc";
                assert((std::strcmp(s.c_str(), "abc")) == 0);
            }

            // # substring
            {
                std::string s = "abcde";
                assert(s.substr(1, 3) == "bcd");
            }

            // # Split at a character into array of strings.
            {
                // Best stdlib solution for any character: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
                // There are shorters sstream solutions that split at whitespace.
                // For Boost it's a one liner.
                {
                    assert((split("01:23::45", ':') == std::vector<std::string>{"01", "23", "", "45"}));

                    std::vector<std::string> v;
                    split("01:23::45", ':', v);
                    assert((v == std::vector<std::string>{"01", "23", "", "45"}));
                }
            }

            /*
            # strip

            # chomp

            # trim

                Exact same techniques as removing elements from vectors but for characters.

                It's just that those operations are so common on strings...

                http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
            */
            {
                // A single character: remove and erase idiom.
                // Single remove_all call in Boost.
                {
                    std::string s = "a bc d";
                    auto end = s.end();
                    s.erase(std::remove(s.begin(), end, ' '), end);
                    assert((s == "abcd"));
                }

                // Any character in a string: remove_if + custom function. std::ispunct is a typical choice.
                // Single liner with boost::remove_if + is_any_of.
                {
                    std::string s = "a,bc. d";
                    auto end = s.end();
                    // stdc ispunct:
                    s.erase(std::remove_if(s.begin(), end, ::ispunct), end);
                    // stdlib ispunct. Fails without the cast.
                    //s.erase(std::remove_if(s.begin(), end, (int(*)(int))std::ispunct), end);
                    assert((s == "abc d"));
                }
            }

            /*
            # getline

                Read istream until a any given character, by default newline, and store chars read into a string.

                The other major method of getting data from streams is `operator<<`,
                which generaly speaking reads until whitespace. getline is generaly saner.

                Returns the stream itself, which allows to:

                - chain calls
                - do while(getline) combos, as streams can be converted to bool via the `void*()`
                    operator which returns a pointer type which is then converted to a boolean.
            */
            {
                // Up to newline.
                {
                    std::stringstream ss;
                    std::string s;
                    ss << "ab\n\nc";

                    // The delim is removed from the string.
                    assert(std::getline(ss, s));
                    assert(s == "ab");

                    // Empty
                    assert(std::getline(ss, s));
                    assert(s == "");

                    // No problem if end of stream.
                    assert(std::getline(ss, s));
                    assert(s == "c");

                    // Stream over.
                    assert(!std::getline(ss, s));
                }

                // The stream itself is returned.
                {
                    std::stringstream ss;
                    std::string s;
                    std::string s2;
                    ss << "ab\n\nc";
                    std::getline(std::getline(ss, s), s2);
                    assert(s == "ab");
                    assert(s2 == "");
                }

                // Up to custom char.
                {
                    std::stringstream ss;
                    std::string s;
                    ss << "ab::f";
                    std::getline(ss, s, ':');
                    assert(s == "ab");
                }

                // Read stream line-wise.
                {
                    std::stringstream ss;
                    std::string line;
                    std::vector<std::string> lines;
                    ss << "ab\n\nc";
                    while (getline(ss, line))
                        lines.push_back(line);
                    assert((lines == std::vector<std::string>{"ab", "", "c"}));
                }
            }

            /*
            # stringstream

            # basic_stringstream

                An iostream String backed implementation.

                The following is defined:

                    typedef basic_stringstream<char> stringstream;

                    typedef basic_stringstream<char>

                Very useful to test streams without creating files / stdin.
            */
            {
                std::stringstream oss("abcd");

                // str does not clear the std::stringstream object
                assert(oss.str() == "abcd");

                // To clear it you could do: http://stackoverflow.com/questions/20731/in-c-how-do-you-clear-a-stringstream-variable
                // Set to empty:
                oss.str("");
                // Clear flags. Very important, not only for error indicators but also for end of stream.
                oss.clear();
                assert(oss.str() == "");

                // ERROR: use of deleted function because the constructor is =delete.
                //oss = std::stringstream();
            }

            // Possible application: build up a huge string step by step.
            // May be more efficient than concatenations which always generates new objects.
            {
                std::stringstream oss;
                oss << "ab";
                oss << "cd";
                assert(oss.str() == "abcd");
            }

            /*
            # int to string

                There are a few standard alternatives.

                <http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c>
            */
            {
                /*
                C++11 solves the question once and for all with a robust one-liner for base types.

                It is not intended however for class input.
                */
#if __cplusplus >= 201103L
                assert(std::to_string(123) == "123");
#endif

                /*
                std::stringstream seems to be the best pre C++11 solution.

                It also has the advantage of working for any class that implements `operator<<`.
                */
                {
                    std::stringstream oss;
                    oss << 123;
                    assert(oss.str() == "123");
                }

                /*
                C sprintf

                Works, but uses too many conversion operations.
                */
                {
                    char cs[16];
                    std::sprintf(cs, "%d", 123);
                    std::string s = (cs);
                    assert(s == "123");
                }
            }

            // #int to string
            // http://stackoverflow.com/questions/7663709/convert-string-to-int-c
            {
                // Best C++11 error checking option: stoi
#if __cplusplus >= 201103L
                assert(std::stoi("123") == 123);
#endif
            }
        }

        /*
        # io

            See cppref now: http://en.cppreference.com/w/cpp/io

            Take a good look at the inheritance tree.

            The following are defined:

                extern  istream  cin;   //standard input (stdin)
                extern wistream wcin;
                extern  ostream  cout;  //standard output (stdout)
                extern wostream wcout;
                extern  ostream  cerr;  //standard error (stderr)
                extern wostream wcerr;
                extern  ostream  clog;  //standard log (stdlog)
                extern wostream wclog;

            # istream #ostream

                Istream and ostream are IO interfaces.

                They have many implementations, backed by different types of data:

                - files
                - strings in memory

                The main methods of getting data out of streams are:

                - getline for linewise operations
                - operator << for word wise operations
                - read(char*, size_t). Reads a fixed number of characters into an array.

            # endl

                System dependent newline.

        */
        {
            /*
            # cout

                stdout.

                `ostream` object.

                For tests, std::stringstream shall be used as the results can then be tested,
                and the behaviour is identical to cout.

                `<<` is very magic. You need to understand:

                - operator overload
                - function template argument deduction
                - namespaces adl

                before really understanding why it works.

            # cerr

                Cout for stderr

            # clog

                By default also points to stderr, but can be redirected with TODO.
            */
            {
                std::cout << "cout" << std::endl;
                std::cerr << "cerr" << std::endl;
                std::clog << "clog" << std::endl;
            }

            /*
            # cin #stdin

                `istream` object.

                Avoid using it for similar reasons as scanf:

                - hard to handle invalid inputs
                - difficult to predict behaviour

                getline is the best option.
            */
            {
                //std::cout << "Enter an integer:" << endl;
                //std::cin >> i;
                //std::cout << i << std::endl;
            }

            // This is how a very explicit usage of `<<` would look like
            {
                std::stringstream ss;

                //TODO0 how to get his working?
                //std::operator<<<std::ostream,std::string>(ss, "explicit");

                std::operator<<(std::operator<<(ss, "explicit "), "call");
            }

            // #<< left shift overload
            {
            }

            // #>> right shift overload istream
            // Get input out of streams into string.
            // Overloaded for many different types of inputs: <http://www.cplusplus.com/reference/istream/istream/operator%3E%3E/>
            {
                // char*, std::string
                // - skip whitespace as defined by `isspace`.
                // - read until first whitespace found
                {
                    std::stringstream ss("ab cd\tef  \t\ngh i.;)j");
                    std::string s;
                    ss >> s;
                    assert(s == "ab");
                    ss >> s;
                    assert(s == "cd");
                    ss >> s;
                    assert(s == "ef");
                    ss >> s;
                    assert(s == "gh");
                    ss >> s;
                    assert(s == "i.;)j");
                }

                // Numeric types: int, float.
                // - skip whitespace as defined by `isspace`.
                // - read until cannot be part of the type anymore (TODO what does that mean exactly?)
                {
                    std::stringstream ss("1.0 2 \n \t 3.0f 4a a");
                    float f;
                    std::string s;
                    ss >> f;
                    assert(f == 1.0f);
                    ss >> f;
                    assert(f == 2.0f);
                    ss >> f;
                    assert(f == 3.0f);

                    // f suffix is not part of floats
                    ss >> s;
                    assert(s == "f");

                    ss >> f;
                    // TODO what happens? Error checking.
                }

                // Since `>>` returns the istream, it is possible to chain calls:
                {
                    std::stringstream ss("1 1.5 2");
                    int i, j;
                    float f;
                    ss >> i >> f >> j;
                    assert(i == 1);
                    assert(f == 1.5);
                    assert(j == 2);
                }
            }

            /*
            # printf format strings

                In C++ there is no more printf formatting strings: must use the C libs for that.

                It is possible however to obtain some level of formatting control with manipulators.

            # manipulators

                Allow to control the output format.
            */
            {
                /*
                # boolalpha

                    Control the format of boolean printing.

                    - on: print `true` or `false`
                    - no: print `1`    or `0` (default)

                    Mnemonic: if true use alpha chars. Else, use numeric chars.
                */
                {
                    std::stringstream ss;

                    ss << std::boolalpha << true;
                    assert(ss.str() == "true");
                    ss.str("");

                    ss << std::noboolalpha << true;
                    assert(ss.str() == "1");
                    ss.str("");

                    //default is noboolalpha
                    ss << true;
                    assert(ss.str() == "1");
                    ss.str("");
                }

                /*
                Once an options is eaten by the ostream, it stays as the default option.
                */
                {
                    std::stringstream ss;

                    ss << std::boolalpha;

                    ss << true;
                    assert(ss.str() == "true");
                    ss.str("");
                        //does not clear earlier passed options

                    ss << true;
                    assert(ss.str() == "true");
                    ss.str("");

                    ss << std::noboolalpha;

                    ss << true;
                    assert(ss.str() == "1");
                    ss.str("");
                }

                /*
                # width

                    Minimum number of chars to output.

                    If not enough, complete with fill.

                # fill

                    See width.

                # left right internal
                */
                {
                    std::stringstream ss;
                    int i = 12;

                    ss.width(4);
                    ss.fill(' ');

                    ss << std::left << i;
                    assert(ss.str() == "12  ");
                    ss.str("");

                    ss << std::right << i;
                    //assert(ss.str() == "  12");
                        //why fails?
                    ss.str("");
                }

                /*
                # dec #hex #oct

                    Control how integers are printed.
                */
                {
                    std::stringstream ss;

                    ss << std::hex << 10;
                    assert(ss.str() == "a");
                    ss.str("");

                    ss << std::oct << 10;
                    assert(ss.str() == "12");
                    ss.str("");

                    ss << std::dec << 10;
                    assert(ss.str() == "10");
                    ss.str("");

                    ss << 10;
                    assert(ss.str() == "10");
                    ss.str("");
                }

                /*
                # scientific fixed none

                # precision

                    Controls number of digits to print.
                */
                {
                    std::stringstream ss;
                    ss.precision(3);
                    float f = 1.2345;

                    //none is the default
                    ss << f;
                    assert(ss.str() == "1.23");
                    ss.str("");

                    ss << std::fixed << f;
                    assert(ss.str() == "1.235");
                    ss.str("");

                    ss << std::scientific << f;
                    assert(ss.str() == "1.235e+00");
                    ss.str("");

                    /*
                    None can only be set via `unsetf(ios_base::floatfield)`.
                    */
                    {
                        ss.unsetf(std::ios_base::floatfield);
                        ss << f;
                        assert(ss.str() == "1.23");
                        ss.str("");
                    }
                }
            }

            /*
            # file io

            # ifstream

            # ofstream

            # fstream
            */
            {
                std::string path("fileio.tmp");
                std::string data("ab\n\nc\n");

                // Write to file.
                {
                    std::ofstream ofs(path);
                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }
                }

                // #Read entire file at once: stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
                // Best way seems to be to get file size, allocate, and read manually.
                {
                    std::ifstream ifs(path);
                    if (ifs) {
                        std::string data_read;
                        read_file(ifs, data_read);
                        assert(data_read == data);
                    } else {
                        ios_read_fail(path);
                    }
                }

                // #Copy file to another. #cp
                // #rdbuf http://stackoverflow.com/questions/2141749/what-does-ifstreamrdbuf-actually-do
                {
                    std::string data = "abc\ndef\n";
                    std::string src_path = "src.tmp";
                    std::string dst_path = "dst.tmp";
                    // Create input file.
                    {
                        std::ofstream src(src_path, std::ios::binary);
                        src << data;
                        // 2 times 4 Gb.
                        //for (int i = 0; i < 2; i++) {
                            //for (int j = 0; j < 0xFFFFFFFF; j++) {
                                //src << std::hex << j;
                            //}
                        //}
                        src.close();
                    }
                    // Copy.
                    std::ifstream src(src_path, std::ios::binary);
                    std::ofstream dst(dst_path,   std::ios::binary);
                    dst << src.rdbuf();
                    src.close();
                    dst.close();
                    // Check copy.
                    {
                        std::ifstream dst(dst_path, std::ios::binary);
                        std::string data_read;
                        read_file(dst, data_read);
                        assert(data_read == data);
                        src.close();
                    }
                }

                // #Compare two files larger than memory.
                // TODO is there an easier way than reading each?
                {
                }

                // #Append to file.
                {
                    std::ofstream ofs(path);

                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }

                    // #open #Reopen
                    // Can be used to reopen ofstream with new properties.
                    // Also consider clearing error flags if there can be any.
                    //ofs.clear()
                    ofs.open(path, std::ios::app);
                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }

                    std::ifstream ifs(path);
                    if (ifs) {
                        std::string data_read;
                        read_file(ifs, data_read);
                        assert(data_read == data + data);
                    } else {
                        ios_read_fail(path);
                    }
                }

                /*
                # binary io

                    Use ios::binary, and the binary functions write and read.
                */
                {
                    // TODO
                    //std::string path("binary.tmp");
                    //std::vector<int> data{0x123, 0x456};
                    //std::vector<int>::size_type size = data.size();
                    //std::vector<int> data_read(size);
                    //std::ofstream ofs(path, std::ios::binary);
                    //if (ofs) {
                        //ofs.write(&data[0], size);
                        //ofs.close();
                    //} else {
                        //ios_write_fail(path);
                    //}

                    //std::ifstream ifs(path);
                    //if (ifs) {
                        //std::string data_read;
                        //read_file(ifs, data_read);
                        //assert(data_read == data);
                    //} else {
                        //ios_read_fail(path);
                    //}
                }

                /*
                # error handling

                    # is_open vs bool cast

                        `is_open` false implies `operator bool()` false, but the converse is false: `operator bool()` is more strict.

                        <http://stackoverflow.com/questions/14920457/c-difference-between-casting-ifstream-to-bool-and-using-ifstreamis-open>

                    IO functions do not raise exceptions by default, but may be turned on.

                    The best standard exception to raise is probably `std::ios_base::failure`.

                    Relevant standard exceptions:

                        http://en.cppreference.com/w/cpp/io/ios_base/failure

                    SO thread:

                        http://stackoverflow.com/questions/9670396/exception-handling-and-opening-a-file
                */
                {
                    std::string path("i_dont_exist.tmp");
                    std::ifstream ifs(path);
                    if (ifs) {
                    } else {
                        try {
                            throw std::ios_base::failure("Error: Could not write to file: " + path);
                        } catch (std::ios_base::failure e) {
                            std::clog << e.what() << std::endl;
                        }

                    }
                }

                // # ios::in: flag automatically set for ifstream, but not fstream
                //http://stackoverflow.com/questions/7463410/is-iosin-needed-for-ifstreams-opened-in-binary-mode
            }
        }

        /*
        # path #directory #join

            Like in C, no system independant path or directory operations (for the love of God...)

            Boost does have a system independant path separator.

            Some Boost fs features were proposed on TR2.
        */

#if __cplusplus >= 201103L
        /*
        # static_assert

            Make assertions at compile time.

            In this way you don't waste time compiling large programs,
            or do potentially dangerous runtime operations to test your program.

            Probably became possible on C++11 because of features such as `constexpr`,
            which allow to better manage compile time constantness.

            <http://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for>
        */
        {
            static_assert(0 < 1, "msg");

            // ERROR: static assertion failed
            //static_assert(0 > 1, "msg");

            std::srand(time(NULL));
            // ERROR: needs to be a constexpr
            //static_assert(std::rand() >= 0);
        }
#endif

        /*
        # utility

            Lots of miscelaneous utilities.

            <http://en.cppreference.com/w/cpp/utility>
        */
        {

#if __cplusplus >= 201103L
            /*
            # tuple

                Hold a ordered collection of elements.

                Each element can be of a different type.

                The length is always fixed.
            */
            {
                //create
                {
                    //constructor
                    {
                        std::tuple<int,char,std::string> t0(0, 'a', "a");
                    }

                    /*
                    # make_tuple

                        forwards arguments to tuple constructor.

                        The advantage over the constructor is that since it is a function
                        template argument deduction can be done, so we don't need to type in
                        template arguments.

                        Remember that template argument deduction cannot be done for constructors.
                    */
                    {
                        std::tuple<int,char,std::string> t;

                        //without make_tuple
                        t = std::make_tuple(0, 'a', "a");
                        t = std::tuple<int,char,std::string>(0, 'a', "a");

                        //with make_tuple
                    }

                    //tuple from pair
                    {
                        std::tuple<int,char> t2( std::pair<int,char>(0, 'a'));
                    }

                    //uniform initialization
                    {
                        std::tuple<int,char,std::string> t{0, 'a', "a"};
                    }

                    // Fails because the tuple constructor are is `explicit`!
                    // TODO Rationale? <http://stackoverflow.com/questions/14961809/returning-a-tuple-from-a-function-using-uniform-initialization-syntax>
                    {
                        //std::tuple<int, int> t = {0, 1};
                        //std::tuple<int, int> t[]{{0, 1}};
                    }
                }

                /*
                # get

                    Get single element from tuple.

                    Returns references, so it is possible to modify the tuples with them.

                    Copies are made from input elements
                */
                {
                    std::tuple<int,std::string> t0(0, "abc");

                    assert(std::get<0>(t0) == 0);
                    assert(std::get<1>(t0) == "abc");

                    std::get<0>(t0) = 1;
                    assert(std::get<0>(t0) == 1);

                    std::get<1>(t0)[0] = '0';
                    assert(std::get<1>(t0) == "0bc");
                }

                /*
                # tie

                    Unpack a tuple.

                    Unpack by reference seems not to be possible: <http://stackoverflow.com/questions/16571883/unpacking-a-std-tuple-into-pointers>

                # ignore

                    Magic that exists only to ignore one of tie outputs.
                */
                {
                    int i;
                    std::string s;
                    std::tuple<int,float,std::string> t(1, 1.5, "abc");
                    std::tie(i, std::ignore, s) = t;
                    assert(i == 1);
                    assert(s == "abc");

                    // Clearly copies are made.
                    i = 2;
                    assert(std::get<0>(t) == 1);
                }

                /*
                Relational operators operations are implemented

                <http://www.cplusplus.com/reference/tuple/tuple/operators/>

                `<` family is lexicographical.
                */
                {
                    std::tuple<int,char> t0(0, 'a');
                    std::tuple<int,char> t1(0, 'a');
                    std::tuple<int,char> t2(1, 'b');
                    std::tuple<int,char> t3(-1, 'b');
                    std::tuple<int,char> t4(0, 'b');

                    assert(t0 == t1);
                    assert(t0 != t2);
                    assert(t0 < t2);
                    assert(t0 > t3); //-1 counts
                    assert(t0 < t4); //0 ties, 'a' < 'b'
                }

                //swap contents of two tuples of same type
                {
                    std::tuple<int,char> t0(0, 'a');
                    std::tuple<int,char> t1(1, 'b');

                    std::tuple<int,char> old_t0 = t0;
                    std::tuple<int,char> old_t1 = t1;

                    t0.swap(t1);

                    assert(t0 == old_t1);
                    assert(t1 == old_t0);
                }
            }
#endif

            /*
            # pair

                Particular case of tuple for two elements

                Methods which also exist for tuple will not be discussed.

                Specially important because of `map`.
            */
            {
                //access: can also be done via `.first` and `.second` in addition to tuple `get`.
                {
                    std::pair<int,char> p(0, 'a');
                    assert(std::get<0>(p) == p.first);
                    assert(std::get<1>(p) == p.second);
                }
            }

            /*
            # forward

                TODO
            */
            {
            }
        }

        /*
        # containers

            The stdlib furnishes several containers.

            It is a very important part of an algorithm to choose the right container for the task.

            As of C++11, most containers are abstract, that is, only specify which operations it supports.

            For example, a `UnorderedMap` could be implemented both as a hash map or a RB tree concrete data structures,
            but is always supports the same operations: insert, remove, and so on.

            The major data structures which you must know about in order of decreasing usefulness are:

            - std::vector
            - set
            - map
            - list
            - deque
            - heap and priority queue
        */

        /*
        # vector

            Array backed conatiner that grows / shrinks as necessary.

            $O(1)$ random access.

            $O(n)$ element removal from interior

            $O(1)$ element append to end (amortized, $O(n)$ worst case)

            All methods that work for several SLT containers shall only be cheated here once.
        */
        {
            // Create
            {
                // Empty
                {
                    std::vector<int> v;
                    // C++11 initializer lists:
                    std::vector<int> v1{};
                    assert(v == v1);
                }

                /*
                Fill constructor.

                Make a `std::vector` with n copies of a single value.
                */
                {
                    //copies of given object
                    {
                        assert(std::vector<int>(3, 2) == std::vector<int>({2, 2, 2}));
                    }

                    //default constructed objects. int = 0.
                    {
                        assert(std::vector<int>(3) == std::vector<int>({0, 0, 0}));
                    }
                }

                // Range copy.
                {
                    std::vector<int> v{0, 1, 2};
                    std::vector<int> v1(v.begin(), v.end());
                    assert(v == v1);
                }

                // From existing array.
                {
                    int myints[]{0, 1, 2};
                    std::vector<int> v(myints, myints + sizeof(myints) / sizeof(int));
                    std::vector<int> v1 = {0, 1, 2};
                    assert(v == v1);
                }
            }

            // Vectors have order.
            {
                std::vector<int> v{0, 1, 2};
                std::vector<int> v1{2, 1, 0};
                assert(v != v1);
            }

            /*
            # Contigous storage

            # Data

                Storage is required to be contiguous by TR1:
                http://stackoverflow.com/questions/849168/are-stdvector-elements-guaranteed-to-be-contiguous

                C++11 introduces the `data()` method which returns a pointer to the first element.
                It works even if the vector is empty.
                http://stackoverflow.com/questions/6485496/how-to-get-stdvector-pointer-to-the-raw-data

                Before C++11, `&v[0]` works for non-empty vectors.

                `vector<bool>` as usual is an exception.
            */
            {
                std::vector<int> v{0, 1, 2};
                assert(&v[0] == v.data());
                // True because contiguous:
                assert(v.data()[1] == v[1]);
            }

            // size methods
            {
                /*
                # size

                # length of vector

                # size_type

                    Number of elements in std::vector.

                    This has type std::vector<X>::size_type
                */
                {
                    std::vector<int> v;
                    assert(v.size() == 0);
                    v.push_back(0);
                    assert(v.size() == 1);
                }

                /*
                # resize

                    If larger than current size, append given element at end.

                    If smaller than current size, remove elements from end.
                */
                {
                    // Reduce size
                    {
                        std::vector<int> v{0, 1};
                        v.resize(1);
                        assert((v == std::vector<int>{0}));
                    }

                    // Increase size
                    {

                        // Using default constructor objects.
                        {
                            std::vector<int> v{1};
                            v.resize(3);
                            assert((v == std::vector<int>{1, 0, 0}));
                        }

                        // Using copies of given object.
                        {
                            std::vector<int> v{1};
                            v.resize(3, 2);
                            assert((v == std::vector<int>{1, 2, 2}));
                        }
                    }
                }
            }

            // Capacity methods.
            {
                /*
                # capacity

                    Get currently allocated size.

                    Different from size, which is the number of elements in the std::vector!

                    At least as large as size.

                    Likely to be a power of 2 on most implementations.
                */
                {
                    std::vector<int> v;
                    v.push_back(0);
                    v.push_back(1);
                    v.push_back(2);
                    assert(v.capacity() >= 3);
                    std::cout << "capacity = " << v.capacity() << std::endl;
                }

                // # max_size: estimative of what your OS allows you to allocate
                {
                    std::cout << "max_size (MiB) = " << std::vector<int>().max_size() / (1 << 20) << std::endl;
                }

                // # reserve: increase allocated size if larger than current size.
                {
                    std::vector<int> v;
                    v.reserve(3);
                    assert(v.capacity() >= 3);
                    // size() is untouched
                    assert(v.empty());
                }

#if __cplusplus >= 201103L
                // # shrink_to_fit
                {
                    std::vector<int> v{0, 1};
                    v.reserve(4);
                    v.shrink_to_fit();
                    assert(v.capacity() == 2);
                }
#endif
            }

            // `std::vector` stores copies of elements, not references.
            {
                std::string s = "abc";
                std::vector<std::string> v{s};
                v[0][0] = '0';
                assert(v[0] == "0bc");
                assert(s    == "abc");
            }

            // Modify.
            {
                {
                    std::vector<int> v;
                    v = {0};
                    v = {0, 1};
                    assert((v == std::vector<int>{0, 1}));
                }

                /*
                # push_back

                # append

                    Push to the end of the std::vector.

                    Amortized time O(1), but may ocassionaly make the std::vector grow,
                    which may required a full data copy to a new location if the
                    current backing array cannot grow.

                # push_front

                    Does not exist for std::vector, as it would always be too costly (requires to move
                    each element forward.) Use deque if you need that.
                */
                {
                    std::vector<int> v;
                    std::vector<int> v1;

                    v.push_back(0);
                    v1 = {0};
                    assert(v == v1);

                    v.push_back(1);
                    v1 = {0, 1};
                    assert(v == v1);

                    /*
                    push_back makes copies with assign `=`

                    If you want references, use pointers, or even better, auto_ptr.
                    */
                    {
                        std::vector<std::string> v;
                        std::string s = "abc";

                        v.push_back(s);
                        v[0][0] = '0';
                        assert(v[0] == "0bc");

                        //s was not changed
                        assert(s == "abc");
                    }
                }

                /*
                # pop_back

                    Remove last element from std::vector.

                    No return val. Rationale: <http://stackoverflow.com/questions/12600330/pop-back-return-value>
                */
                {
                    std::vector<int> v{0, 1};

                    v.pop_back();
                    assert(v == std::vector<int>{0});

                    v.pop_back();
                    assert(v == std::vector<int>{});
                }

                /*
                # insert

                    This operation is inneficient for `std::vector` if it is not done at the end.

                # concatenate

                    The range form of insert can be used to append one vector to anoter.
                */
                {
                    // Single element form.
                    {
                        std::vector<int> v = {0,1};
                        std::vector<int> v1;

                        v.insert(v.begin(), -1);
                        v1 = {-1, 0, 1};
                        assert(v == v1);

                        v.insert(v.end(), 2);
                        v1 = {-1, 0, 1, 2};
                        assert(v == v1);
                    }

                    // Range form.
                    {
                        std::vector<int> v = {0,1};
                        std::vector<int> v1 = {2,3};

                        v.insert(v.end(), v1.begin(), v1.end());
                        assert((v == std::vector<int>{0, 1, 2, 3}));
                    }
                }

                /*
                # erase

                    Remove given elements from container given iterators to those elements.

                    This operation is inneficient for std::vectors,
                    since it may mean reallocation and therefore up to $O(n)$ operations.

                    Returns a pointer to the new location of the element next to the last removed element.
                */
                {
                    // Single element
                    {
                        std::vector<int> v{0, 1, 2};
                        auto it = v.erase(v.begin() + 1);
                        assert((v == std::vector<int>{0, 2}));
                        assert(*it == 2);
                    }

                    // Range
                    {
                        std::vector<int> v{0, 1, 2, 3};
                        auto it = v.erase(v.begin() + 1, v.end() - 1);
                        assert((v == std::vector<int>{0, 3}));
                        assert(*it == 3);
                    }
                }

                /*
                # remove

                    Helper to remove all elements that compare equal to a value from container.

                    Does not actually remove the elements: only ensures that the beginning of the range
                    does not contain the item to be removed.

                    Ex:

                        0, 1, 0, 2, 0, 1

                    Value to remove: `0`

                    Range to remove from:

                        0, 1, 0, 2, 0, 1
                        ----------

                    After the remove:

                        1, 2, X, Y, 0, 1
                        ----------

                    where `X` and `Y` are trash, and not necessarily 0!

                    To actually remove the items, an `erase` is needed after remove
                    because `remove` is not a class method and thus cannot remove items from a container.

                    This is called the erase and remove idiom.

                    After a remove the container becomes:

                        1, 2, 0, 1

                # erase and remove idiom

                # remove and erase idiom

                    See remove.
                */
                {
                    // Verbose version
                    {
                        std::vector<int> v{0, 1, 0, 2, 0, 1};
                        auto end = std::next(v.end(), -2);
                        auto firstTrashIt = std::remove(v.begin(), end, 0);
                        // Unpredictable result:
                        std::cout << "remove:";
                        for (auto& i : v) std::cout << " " << i;
                        std::cout << std::endl;
                        v.erase(firstTrashIt, end);
                        assert((v == std::vector<int>{1, 2, 0, 1}));
                    }

                    // Compact version
                    {
                        std::vector<int> v{0, 1, 0, 2, 0, 1};
                        auto end = std::next(v.end(), -2);
                        v.erase(std::remove(v.begin(), end, 0), end);
                        assert((v == std::vector<int>{1, 2, 0, 1}));
                    }
                }

                // # remove_if # filter
                // Algorithm. Remove if a given function evaluates to true on an element.
                {
                    std::vector<int> v{0, 1, 2, 3, 4};
                    auto end = v.end();
                    v.erase(std::remove_if(v.begin(), end, odd), end);
                    assert((v == std::vector<int>{0, 2, 4}));

                    // Common combo with lambdas
                    {
                        std::vector<int> v{0, 1, 2, 3, 4};
                        auto end = v.end();
                        v.erase(std::remove_if(v.begin(), end,
                            [](int i) {return i % 2 == 1;}), end);
                        assert((v == std::vector<int>{0, 2, 4}));
                    }
                }

                // # transform
                // Algorithm. Replace elements by output of a function.
                {
                    std::vector<int> v{0, 1, 2};
                    std::transform(v.begin(), v.end(), v.begin(),
                            [](int i) {return i * i;});
                    assert((v == std::vector<int>{0, 1, 4}));
                }

                // # clear
                {
                    std::vector<int> v{0, 1, 2};
                    v.clear();
                    assert(v.size() == 0);
                }

                /*
                # print vector

                # vector to string

                    No built-in way.

                    http://stackoverflow.com/questions/4850473/pretty-print-c-stl-containers
                    190 votes on question, 30 on top answer! Come on C++!

                    http://stackoverflow.com/questions/1430757/c-vector-to-string?lq=1
                */
                // ERROR: no default operator `<<`.
                //cout << v;
            }

            // Random access is O(1) since array backed
            {

                std::vector<int> v{0, 1, 2};

                // First element:

                    assert(v.front() == 0);
                    assert(v.front() == v[0]);

                // Last element:

                    assert(v.back() == 2);

                // Nth element:

                    v[0] = 1;
                    assert(v[0] == 1);

                /*
                BAD: just like array overflow will not change std::vector size,
                and is unlikelly to give an error
                */
                {
                    //v1[2] = 2;
                }

                // #back  Get reference to last  element in vector.
                // #front Get reference to first element in vector.
                // #at    Like `[]`, but does bound checking and throws `out_of_range` in case of overflow.
                {
                    std::vector<int> v{0, 1, 2};
                    assert(v.front() == 0);
                    assert(v.at(1)   == 1);
                    assert(v.back()  == 2);
                    try {
                        assert(v.at(3) == 0);
                    } catch (std::out_of_range& e) {
                    } catch (...) {
                        assert(false);
                    }
                }
            }

            /*
            # bool std::vector

                *bool std::vectors are evil!*

                The standard requires `vector` to have an specialization for bool which packs bits efficiently.

                While efficient, in order to work this specialization breaks common std::vector interfaces
                that require taking addresses only in the case of this specialization, since it does not
                make sense to takes addresses anymore.

                Alternatives to `vector<bool>`: <http://stackoverflow.com/questions/670308/alternative-to-vectorbool>

                A good alternative seem to be deque<bool>, which behaves as intended.
            */
            {
                // Works fine and dandy as expected.
                {
                    std::vector<int> v{1, 0};
                    int& i(v[0]);
                }

                // Does not compile!!!
                {
                    std::vector<bool> v{true, false};
                    //bool& b(v[0]);
                }

                // It was not a problem with bool, the problem really is `vector<bool>`.
                {
                    bool b[]{true, false};
                    bool& b2(b[0]);
                }
            }
        }

        /*
        # deque

            Double ended queue.

            Random access.

            Very similar interface to std::vector, except that:

            - insertion to front is O(1)
            - there is no guarantee of inner storage contiguity

            Discussion on when to use deque or std::vector:
            <http://stackoverflow.com/questions/5345152/why-would-i-prefer-using-vector-to-deque>

            It is controversial if one should use deque or std::vector as the main generic container.
        */

        /*
        # set

            - unique elements: inserting twice does nothing

            - always ordered: $O(log)$ find / insert

            - immutable elements: it is not possible to modify an object,
                one must first remove it and resinsert.

                This is so because modification may mean reordering.
        */
        {
            // C++11 initializer list
            {
                {
                    std::set<int> s{1, 2, 0, 1};
                    std::set<int> s2{0, 1, 2};
                    assert(s == s2);
                }

                {
                    std::set<std::string> s = {"a", "c", "b", "a"};
                    std::set<std::string> s1 = {"a","b", "c"};
                    assert(s == s1);
                }
            }

            // You can modify objects if you store pointers.
            {
                int i = 0;
                std::set<int*> s;
                s.insert(&i);
                std::set<int*>::iterator it = s.find(&i);
                *(*it) = 1;
                assert(i == 1);
            }

            /*
            # insert

                Like for std::vector, insert makes copies.

                Return is a pair conatining:

                - if the item was not present, an iterator to the item inserted and true
                - if the item was     present, an iterator to the existing item inserted and false
            */
            {
                std::pair<std::set<int,std::string>::iterator,bool> ret;
                std::set<int> s;

                ret = s.insert(1);
                assert(ret.first == s.find(1));
                assert(ret.second == true);

                ret = s.insert(2);
                assert(ret.first == s.find(2));
                assert(ret.second == true);

                ret = s.insert(0);
                assert(ret.first == s.find(0));
                assert(ret.second == true);

                //item already present:
                //nothing is done and returns false on the pair
                ret = s.insert(1);
                assert(ret.first == s.find(1));
                assert(ret.second == false);

                std::set<int> s1 = {0, 1, 2};
                assert(s == s1);
            }

            /*
            # erase

                Remove element from set.

                Returns number of elements removed.
            */
            {
                std::set<int> s = {0, 1, 2};

                assert(s.erase(1) == 1);
                std::set<int> s2 = {0, 2};
                assert(s == s2);

                assert(s.erase(1) == 0);
            }

            // ERROR no random access since it uses bidirection iterator.
            {
                //cout << s[0] << endl;
            }

            //size
            {
                std::set<int> s;
                assert(s.size() == 0);
                s.insert(0);
                assert(s.size() == 1);
            }

            /*
            iterate

                Biderectional iterator.

                Always sorted.
            */

            /*
            find

                If found, returns an iterator pointing to the element.
                Else, returns `map::end()`

                find is `log n` time since the container is ordered.

                log n time complexity since always sorted
            */
            {
                std::set<int> s = {0, 1, 2};
                std::set<int>::iterator it;

                it = s.find(1);
                assert(*it == 1);

                it = s.find(3);
                assert(it == s.end());
            }

            /*
            count

                Count how many times an item is in the set.

                Can only return 1 or 0.

                Equivalent to doing a find.
            */
            {
                std::set<int> s = {1, 2, 0, 1};
                assert(s.count(1) == 1);
                assert(s.count(3) == 0);
            }
        }

        /*
        # hashmap

            There seems to be no explicit hashmap container, only a generic map interface,

            See map.

            Nonstandard `hash_map` already provided with gcc and msvc++.
            It is placed in the `std::` namespace, but it is *not* ISO.

        # map

            <http://www.cplusplus.com/reference/map/map/>

            Also comes in an unordered version `unordered_map`.

            Ordered.

            Also comes in an multiple value input version `multimap`.

            Does not require a hash function. Usually implemented as a self balancing tree such as a rb tree.

        # unordered_map

            TODO complexity comparison to map.
        */
        {
            /*
            The initializer list constructor makes things very easy.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                    {2, "two"},
                };
            }

            /*
            emplace

                put a value pair into the map without creating the pair explicitly

                needs gcc 4.8: <http://stackoverflow.com/questions/15812276/stdset-has-no-member-emplace>
            */
            {
                //std::map<int,std::string> m;
                //m.emplace(0, "zero");
                //m.emplace(1, "one");
                //m.emplace(2, "two");
            }

            /*
            # insert

                Insert pair into map.

                The return value is similar to that of a set insertion with respec to the key.
            */
            {
                std::map<int,std::string> m;
                std::pair<std::map<int,std::string>::iterator,bool> ret;

                ret = m.insert(std::pair<int,std::string>(0, "zero"));
                assert(ret.first == m.find(0));
                assert(ret.second == true);

                ret = m.insert(std::pair<int,std::string>(1, "one"));
                assert(ret.first == m.find(1));
                assert(ret.second == true);

                //key already present
                ret = m.insert(std::pair<int,std::string>(1, "one2"));
                assert(m[1] == "one");
                assert(ret.first == m.find(1));
                assert(ret.second == false);
            }

            /*
            iterate

                Map is ordered.

                It is iterated in key `<` order.

                Iteration returns key value pairs.
            */
            {
                std::map<int,std::string> m{
                    {1, "one"},
                    {0, "zero"},
                };

                int i = 0;
                int is[] = {0, 1};
                for (auto& im : m) {
                    assert(im.first == is[i]);
                    //cout << im->second << endl;
                    ++i;
                }
                assert(i == 2);
                assert(map_to_str(m) == "0:zero, 1:one, ");
            }

            /*
            [] operator

                get value from a given key

                WARNING: if the key does not exist, it is inserted with a value with default constructor.

                This can be avoided by using `find` instead of `[]`.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                assert(m[0] == "zero");
                assert(m[1] == "one");

                //inserts `(3,"")` because `""` is the value for the default string constructor
                assert(m[2] == "");
                assert(m.size() == 3);
            }

            /*
            # find #check if in map

                Similar to `std::set` find with respect to the keys:
                returns an iterator pointing to the pair which has given key, not the value.

                If not found, returns `map::end()`

                This is perferrable to `[]` since it does not insert non-existent elements.
            */
            {
                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                assert(m.find(0)->second == "zero");
                assert(m.find(1)->second == "one");

                assert(m.find(2) == m.end());
                assert(m.size() == 2);
            }

            /*
            erase

                Remove element from map.

                Returns number of elements removed.
            */
            {
                int ret;

                std::map<int,std::string> m{
                    {0, "zero"},
                    {1, "one"},
                };

                std::map<int,std::string> m2;
                m2.insert(std::pair<int,std::string>(0, "zero"));

                ret = m.erase(1);
                assert(ret = 1);

                assert(m == m2);

                ret = m.erase(1);
                assert(ret == 0);
            }
        }

        /*
        # list

            Doubly linked list.

            Advantages over std::vector: fast inservion and removal from middle.

            Unless you really need those operations fast, don't use this data structure.

            No random access.

        # forward_list

            Like list, but singly linked, and therefore not backwards interable.
        */
        {
            //initializer list constructor
            {
                std::list<int> l{0, 1};
            }

            // # emplace
            {
                std::list<int> l{0, 1};
                l.emplace(++l.begin(), 2);
                assert(l == std::list<int>({0, 2, 1}));
            }

            // # remove: remove all elements with a given value from list
            {
                std::list<int> l{0, 1, 0, 2};
                l.remove(0);
                assert(l == std::list<int>({1, 2}));
            }

            // # splice: transfer elements from one list to another
            {
                std::list<int> l{0, 1};
                std::list<int> l2{2, 3};
                l.splice(++l.begin(), l2);
                assert(l == std::list<int>({0, 2, 3, 1}));
                assert(l2 == std::list<int>());
            }
        }

        /*
        # iterator

            Iteration could be done with random access in certain data structures with a for i loop.

            Iterators are better becase you can also use them for structures without random access,
            so if you decide to change structures in the future the job will be much easier.

            # iterator categories

                Iterators are categorized depending on the operations they can do:

                    <http://www.cplusplus.com/reference/iterator/>

                The clases are (from least to most versatile):

                - Input Output
                - Forward
                - Bidirectional
                - Random Access

                The most versatile iterators (random access) behave much like pointers,
                and overload most pointer operations such as integer increment `it + 1` and
                pointer dereference `*it` in a similar way to pointers.

                Those classes are not language enforced via inheritance like in Java,
                but could be used by programmers to implement typedefs that explain
                the types of operations permitted. So if you are going to use a typedef
                solution not to tie yourself to a given container, consider naming the
                typdefed as one of the classes to indicate the operationt can do:

                    typedef random_it std::vector<int>::iterator;

                It is possible to retreive the class of an interator via `std::iterator_traits<ITER>::interator_category`.
        */
        {
            // Before C++11: begin and end were the only way to use iterators.
            // After C++11; the range based syntax is the best way to use them.
            {
                /*
                # forward iteration

                    Can be done on all containers.

                    # begin

                        Returns an iterator to the first element.

                    # end

                        Returns an iterator to the first element *after* the last.
                */
                {
                    std::vector<int> v{1, 2, 0};
                    int i = 0;
                    int is[]{1, 2, 0};

                    for (auto it = v.begin(); it != v.end(); ++it) {
                        assert(*it == is[i]);
                        ++i;
                    }
                }

                /*
                # backwards iteration

                    Can only be done on biderectional containers.

                    # rbegin

                        Reversed begin.

                        Returns a `reverse_iterator` that points to the last emlement.

                        ++ on reversed iterators decreases them.

                    # rend

                        Returns a reversed iterator to the element before the first.
                */
                {
                    std::vector<int> v{1, 2, 0};
                    int i;
                    int is[]{1, 2, 0};

                    i = 2;
                    for (auto it = v.rbegin(); it != v.rend(); ++it) {
                        assert(*it == is[i]);
                        //cout << *it << endl;
                        --i;
                    }
                }
            }

            /*
            # range based for loop #foreach

                C++11

                Like python foreach or Java improved-for loop.

                This is the best way to iterate a container with C++11.

                Much easier to write or read.

                Also have the advantage that you don't need to specify iterator type!

                Behind the scenes, this method is still based on iterators,
                and the class to be iterated needs to implement:

                - begin()
                - end()

                And the iterator returned must implement:

                - operator++()
                - operator!=()
                - operator*()
            */
            {
#if __cplusplus >= 201103L
                //forward
                {
                    // If `int&` is used, no useless copies are made.
                    // and the vector can be modified directly.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (int& iv : v) {
                            assert(iv == is[i]);
                            //cout << iv << endl;
                            iv++;
                            i++;
                        }
                        assert((v == std::vector<int>{2, 3, 1}));
                    }

                    // Without `&`, makes copies of each element.
                    // Usually not what we want.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (int iv : v) {
                            assert(iv == is[i]);
                            //cout << iv << endl;
                            iv++;
                            i++;
                        }
                        assert((v == std::vector<int>{1, 2, 0}));
                    }

                    // Less code duplication with auto.
                    // This is the best way to do it.
                    {
                        std::vector<int> v{1, 2, 0};
                        int is[]{1, 2, 0};
                        int i = 0;
                        for (auto& iv : v) {
                            assert(iv == is[i]);
                            //cout << *it << endl;
                            i++;
                        }
                    }
                }

                /*
                # range based for loop for arrays

                    Also works for bare arrays for which the size is known at compile time!
                */
                {
                    {
                        int is[]{1, 2};
                        for (int& i : is) {
                            i *= 2;
                        }
                        assert(is[0] == 2);
                        assert(is[1] == 4);
                    }

                    /*
                    does not work for dynamic memory since
                    there would be no way to know the array size at compile time
                    */
                    {
                        //int *is = new int[2];
                        //is[0] = 1;
                        //is[0] = 2;
                        //for (int &i : is) {
                        //    i *= 2;
                        //}
                        //delete[] is;
                    }
                }
#endif
                /*
                backwards

                    TODO possible? Seems not out of the C++11 box: <http://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop>

                    Auto is a lifesaver here to avoid typing the iterator type.
                */
                {
                    std::vector<int> v = {1, 2, 0};
                    int i;
                    int is[] = {1, 2, 0};

                    //forward
                    {
                        i = 2;
                        for (auto it = v.rbegin(); it != v.rend(); ++it) {
                            assert(*it == is[i]);
                            //cout << *it << endl;
                            i--;
                        }
                    }
                }
            }

            /*
            # generic containers

                There is no standard iterator independent from container.

                This can be done via type erasure techinques.

                But would mean loss of performance because of lots of polymorphic calls
                and stdlib is obssessed with performance.

                The best solution seems to use typedefs:

                    typedef it_t std::vector<int>::iterator;

                And then if ever your container changes all you have to do is modify one single typedef:

                    typedef it_t set<int>::iterator;

                TODO isnt auto and range based for a better solution in c++11?
            */
            {
                std::vector<int> v{1, 2};
                std::set<int> s{1, 2};
                std::vector<int>::iterator itVec(v.begin());
                std::set<int>::iterator itSeti(s.begin());

                // Does not exist:

                    //iterator<int> itVec = v.begin();
                    //iterator<int> itSeti = s.begin();

                // Best workaround is using auto:

                    auto vit(v.begin());
                    auto sit(v.begin());
            }

            // No born checking is done
            {
                std::vector<int> v{1, 2};

                // Last element.
                *(v.end() - 1);

                // After last element no born check.
                *(v.end());

                // No such method.
                //(v.end().hasNext());
            }

            /*
            Base pointers and arrays can be used anywhere iterators can.

            The stdlib functions have specializations for pointers.

            <http://stackoverflow.com/questions/713309/c-stl-can-arrays-be-used-transparently-with-stl-functions>
            */
            {
                int is[]{2, 0, 1};
                int j = 0;
                for (auto& i : is) {
                    assert(i == is[j]);
                    j++;
                }
            }

            /*
            # size_t for slt containers

                See size_type.

            # size_type

                Random access containers such as std::vectors, strings, etc have a `size_type` member typedef
                that represents a type large enough to hold its indexes.

                For arrays, this type is exactly the C `size_t`.

                For a std::vector, it will also probably be `size_t`, since std::vectors are array backed,
                but using `size_type` gives more generality.

                This type is returned by methods such as `size()`.
            */
            {
                std::vector<int> v{2, 0, 1};
                std::vector<int>::size_type i(1);
                v[i] = 1;
            }

            /*
            # iterator_traits

                Contain information about iterators.

                This allows to create template functions that take generic iterators independent of the
                exact container type as is the case for many function sunder `<algorithm>`.
            */
            {
                //value_type
                //pointer
                //reference
                {
                    typedef std::iterator_traits<std::vector<int>::iterator>::value_type ValueType;
                    typedef std::iterator_traits<std::vector<int>::iterator>::pointer    Pointer;
                    typedef std::iterator_traits<std::vector<int>::iterator>::reference  Reference;
                    assert(typeid(ValueType) == typeid(int));
                    assert(typeid(Pointer)   == typeid(int*));
                    assert(typeid(Reference) == typeid(int&));
                }

                /*
                # difference_type

                    The type returned on a difference between two pointers.

                    Unlike size_type, this value is signed, since the difference may well be negative.
                */
                {
                    typedef typename std::iterator_traits<std::vector<int>::iterator>::difference_type DifferenceType;
                    std::vector<int> v{0, 1};
                    assert(typeid(v.end() - v.begin()) == typeid(DifferenceType));
                }

                /*
                # iterator_category

                    iterator_category is a struct *type*, not a value.

                    Therefore, in order to compare it one must use `typeid`.
                */
                {
                    assert(typeid(std::iterator_traits<std::vector<int>::iterator>::iterator_category)
                            == typeid(std::random_access_iterator_tag));
                }
            }
        }

        /*
        # valarray

            Array of values. Wors much like a mathematical vector.

            Container that overloads many mathematical operations in a similar way to what Fortran does,
            which may be more efficient and convenient.

            Very obscure, for several reasons:

            - other techniques achieve what it achieves
            - low compiler support

            Downsides compared to vectors:

            - not resizable, so no push_back

            <http://stackoverflow.com/questions/1602451/c-valarray-vs-vector>
        */
        {
            std::valarray<int> v;
            std::valarray<int> v0{0, 1, 2};
            std::valarray<int> v1{3, 4, 5};

            assert(v0.sum() == 3);
            assert(v0.min() == 0);
            assert(v0.max() == 2);

            /*
            v = v0;
            v.cshift(1);
            assert((v == std::valarray<int>{1, 2, 0}).min());
            */

            // == is elementwise equality.
            //
            // For equality of all elements, do `.min() == true`
            {
                std::valarray<int> v0{0, 1, 2};
                std::valarray<int> v1{0, 2, 2};
                assert(((v0 == v1) == std::valarray<bool>{true, false, true}).min());

            }

            // +, -, *, /, etc are overloaded elementwise.
            //
            // They are also overloaded for contained data type.
            {
                assert((v0 + v1 == std::valarray<int>{3, 5, 7}).min());
                assert((v0 +  1 == std::valarray<int>{1, 2, 3}).min());
            }

            // Basic cmath functions are overloaded for valarray elementwise.
            {
                assert((abs(std::valarray<int>{-1, 0, 1})    == std::valarray<int>{1, 0, 1}).min());
                assert((pow(std::valarray<int>{-2, 0, 2}, 2) == std::valarray<int>{4, 0, 4}).min());
            }
        }

        // # algorithm
        {
            {
                assert(std::min(0.1, 0.2) == 0.1);
                assert(std::max(0.1, 0.2) == 0.2);
            }

            // # sort
            {
                std::vector<int> v{2, 0, 1};
                std::sort(v.begin(), v.end());
                std::vector<int> v1 = {0, 1, 2};
                assert((v == std::vector<int>{0, 1, 2}));
            }

            // # reverse
            {
                std::vector<int> v{2, 0, 1};
                std::reverse(v.begin(), v.end());
                assert((v == std::vector<int>{1, 0, 2}));
            }

            /*
            # swap

                Does things equivalent to:

                    template <class T> void swap (T& a, T& b)
                    {
                        T c(a); a=b; b=c;
                    }

                However stdlib can specialize it to do operations more efficiently.

                Some stdlib classes implement swap as a method.

                Particularly important because of the copy and swap idiom.
            */

            // # randomize
            {
                std::vector<int> v{2, 0, 1};
                std::random_shuffle(v.begin(), v.end());
            }

            // # copy
            {
                std::vector<int> v{2, 0, 1};
                std::vector<int> v2(5, 3);
                std::copy(v.begin(), v.end(), v2.begin() + 1);
                assert(v2 == std::vector<int>({3, 2, 0, 1, 3}));
            }

            /*
            # equal

                Compares ranges of two containers.
            */
            {
                std::vector<int> v {0, 1, 2   };
                std::vector<int> v2{   1, 2, 3};
                assert(std::equal(v.begin() + 1, v.end(), v2.begin()));
            }

            /*
            # accumulate

                Sum over range.

                Also has functional versions <http://www.cplusplus.com/reference/numeric/accumulate/>
            */
            {
                std::vector<int> v{2, 0, 1};
                assert(std::accumulate(v.begin(), v.end(), 0)     == 3);
                assert(std::accumulate(v.begin(), v.end(), 10)    == 13);
            }

            /*
            # find

                Return iterator to first found element.
            */
            {
                std::vector<int> v{2,0,1};
                unsigned int pos;

                pos = std::find(v.begin(), v.end(), 0) - v.begin();
                assert(pos == 1);

                pos = std::find(v.begin(), v.end(), 1) - v.begin();
                assert(pos == 2);

                pos = std::find(v.begin(), v.end(), 2) - v.begin();
                assert(pos == 0);

                pos = std::find(v.begin(), v.end(), 3) - v.begin(); //end() returned
                assert(pos == v.size());
            }

            /*
            # find_if

                Like find, but using an arbitrary condition on each element instead of equality.

                Consider usage with C++11 lambdas and functional.
            */
            {
                std::vector<int> v{2, 0, 1};
                assert(std::find_if (v.begin(), v.end(), odd) == --v.end());
            }

            /*
            # binary_search

                Container must be already sorted.

                Log complexity.

                Only states if the element is present or not, but does not get its position.

                If you want to get the position of those items, use `equal_range`, `lower_bound` or `upper_bound`.
            */
            {

                std::vector<int> v{0, 1, 2};
                assert(std::binary_search(v.begin(), v.end(),     1) == true);
                assert(std::binary_search(v.begin(), v.end(),     3) == false);
                assert(std::binary_search(v.begin(), v.end() - 1, 2) == false);
            }

            /*
            # lower_bound

                Finds first element in container which is not less than val.
            */
            {
                std::vector<int> v{0, 2, 3};
                auto it = std::lower_bound(v.begin(), v.end(), 1);
                assert(it - v.begin() == 1);
            }

            /*
            # upper_bound

                Finds first element in container is greater than val.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it = std::upper_bound(v.begin(), v.end(), 1);
                assert(it - v.begin() == 2);
            }

            /*
            # equal_range

                Finds first and last location of a value iniside a ranged container.

                Return values are the same as lower_bound and upper_bound.

                log complexity.
            */
            {
                std::vector<int> v{0, 1, 1, 2};
                std::vector<int>::iterator begin, end;
                std::tie(begin, end) = std::equal_range(v.begin(), v.end(), 1);
                assert(begin - v.begin() == 1);
                assert(end   - v.begin() == 3);
            }

            // # count
            {
                std::vector<int> v{2,1,2};
                assert(std::count(v.begin(), v.end(), 0) == 0);
                assert(std::count(v.begin(), v.end(), 1) == 1);
                assert(std::count(v.begin(), v.end(), 2) == 2);
            }


            // # max_element #min_element
            {
                std::vector<int> v{2,0,1};
                assert(*std::max_element(v.begin(), v.end()) == 2);
                assert(*std::min_element(v.begin(), v.end()) == 0);
            }

            /*
            # advance

                Advance iterator by given number.

                If random access, simply adds + N.

                Else, calls `++` N times.

                Advantage over `+`: only random access containers support `+`,
                but this works for any container, allowing one to write more general code.

                Beware however that this operation will be slow for non random access containers.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it = v.begin();
                std::advance(it, 2);
                assert(*it == 2);
            }

#if __cplusplus >= 201103L
            /*
            # next

                Same as advance, but returns a new iterator instead of modifying the old one.
            */
            {
                std::vector<int> v{0, 1, 2};
                auto it(v.begin());
                auto itNext = std::next(it, 2);
                assert(*it == 0);
                assert(*itNext == 2);
            }
#endif

            /*
            # priority queue

                Offers `O(1)` access to the smalles element.

                Other operatoins vary between `O(n)` and `O(1).

                Most common implementaions are via:

                - binary heap
                - fibonacci heap

                Boost offers explicit heap types: fibonacci, binary and others.

                But no guarantees are made.

                As of C++11, does not support the increase key operation.

                A binary heap without increase key can be implemented via the heap function family under algorithm.
            */

            /*
            # heap

                Binary heap implementation.

                <http://en.wikipedia.org/wiki/Heap_%28data_structure%29>

                In short:

                - getting largest element is O(1)
                - removing the largest element is O(lg) for all implementation
                - other operations (insertion) may be O(1) or O(lg) depending on the implementation.

                this makes for a good priority queue.
                Exact heap type is not guaranteed. As of 2013, it seems that most implementations use binary heaps.

                For specific heaps such as Fibonacci, consider [Boost](http://www.boost.org/doc/libs/1_49_0/doc/html/heap.html).

                <http://stackoverflow.com/questions/14118367/stl-for-fibonacci-heap>

                There is no concrete heap data structure in C++:
                only heap operations over random access data structures.
                This is why this is under algoritms and is not a data structure of its own.

                There is however a `priority_queue` stdlib container.

                Why random access structure is needed: <https://github.com/cirosantilli/comp-sci/blob/1.0/src/heap.md#array-implementation>
            */
            {
                int myints[]{10, 20, 30, 5, 15};
                std::vector<int> v(myints, myints + 5);

                /*
                # make_heap

                    Make random access data structure into a heap.

                    This changes the element order so that the range has heap properties

                    Worst case time: $O(n)$.
                */
                    std::make_heap(v.begin(), v.end());
                    assert(v.front() == 30);

                /*
                # pop_heap

                    Remove the largest element from the heap.

                    That element is moved to the end of the data structure, but since the
                    heap should have its length reduced by one, that element will then be out of the heap.

                    Assumes that the input range is already a heap (made with `make_heap` for example).
                */
                    std::pop_heap(v.begin(), v.end());

                    //the element still exists on the data structure
                    assert(v.back() == 30);

                    //the second largest element hat become the largets
                    assert(v.front() == 20);

                    //remove the element from the data structure definitively
                    v.pop_back();

                /*
                # push_heap

                    Insert element into a heap.

                    Assumes that:

                    - the range 0 - (end - 1) was already a heap
                    - the new element to be inserted into that heap is at end.
                */

                    //add the new element to the data structure
                    v.push_back(99);

                    //reorganize the data so that the last element will be placed in the heap
                    std::push_heap(v.begin(), v.end());

                    assert(v.front() == 99);

                /*
                # sort_heap

                    Assumes that the input range is a heap, and sorts it in increasing order.

                    The assumption that we have a heap allows for $O(ln)$ sorting,
                    much faster than the optimal bound $O(n log n)$.

                    This is exactly what the heapsort alrotithm does: make_heap and then sort_heap.
                */

                    std::sort_heap(v.begin(), v.end());
                    //assert(v)
                    //v == 5 10 15 20 99
            }
        }

#if __cplusplus >= 201103L
        /*
        # functional

            Do magic with functions.

            Useful with stdlib functions that take functions as arguments.
        */
        {
            /*
            # bind2nd

                Tranform a function that takes two arguments into a function that takes only the first.

                Useful with stdlib functions that must take functions that take a single argument,
                but you want to pass an extra parameter to that function.

                TODO0 get working
            */
            {
                /*
                std::vector<int> v = {2, 0, 1};
                assert(std::find_if (
                    v.begin(),
                    v.end(),
                    std::bind2nd([](int i, int param){return i == param + 1;}, 1)
                ) == v.begin());
                */
            }
        }
#endif

        /*
        # hash

            <http://www.cplusplus.com/reference/functional/hash/>

            The stdlib furnishes overloaded hash functions for stdlib containers.

            Those functions are implemented as callable classes that implement `()`.

            For base types, those hashes are found under the `functional`.

            For std::vectors, only `std::vector<bool>` has a template.

            For other types, they are found in the same header that defines those types:
            ex: hash for std::vectors is under `<vector>`.

            Returns a `size_t` result.
        */
        {
            std::cout << "hash" << std::endl;
            std::cout << "  1 = "        << std::hash<int>()(1) << std::endl;
            std::cout << "  string abc = "    << std::hash<std::string>()("abc") << std::endl;
        }

#if __cplusplus >= 201103L
        /*
        # regex

            Finally they are supported!

            Many types are supported: Javascript, grep, awk, ...

            It is probably saner and more powerful to stick to Javascript regexes.
        */
        {
            // Js has `[:d:]` equivalent POSIX `[:digit:]`.
            std::regex r("a.(c|d)");
        }
#endif
    }

#if __cplusplus >= 201103L
    /*
    # Attributes

        C++11 introduces a generalized attribute syntax.

        Similar syntaxes have been rmplemented as extensions for a long time in GCC via `__attribtes__`
        and in Microsoft with `#pragma`. Now some have been standardized!

        Intended only for functions which don't change behaviour: only to help
        compilers optimize or geneate better error messages.

        http://www.stroustrup.com/C++11FAQ.html#attributes

        Attributes can be defined for various objects, and there are 2 standard ones:
        `noreturn` and `carries_dependency`

        C11 also has some attributes like `_Noreturn`, but no generalized syntax.
    */
    {
        try {
            noreturn_func();
        } catch (int i) {}
    }
#endif

    /*
    # main return

        Like in C99, C++ return can omit the return, in which case it returns 0.
    */

        return EXIT_SUCCESS;

    // global/static destructors happen at exit time.
}
