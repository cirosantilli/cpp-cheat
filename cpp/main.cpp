/*
C++ cheatsheat.

Features which are identical to C will not be described.

This file is being split up into smaller files.
*/

#include "common.hpp"

class Class {};

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
    # Assign operator

        Unlike in C, the C++ assign operator returns lvalues.

        TODO rationale. Related to return refs from functions?
    */
    {
        int i = 0, j = 1, k = 2;
        (i = j) = k;
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

    // # stdlib
    //
    // # Standard library
    {
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
            # cin

            # stdin

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
                # dec

                # hex

                # oct

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

                /*
                # Read entire file at once

                    http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring

                    Best way seems to be to get file size, allocate, and read manually.
                */
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

                /*
                # Copy file to another

                # cp

                # rdbuf

                    http://stackoverflow.com/questions/2141749/what-does-ifstreamrdbuf-actually-do
                */
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

                /*
                # Compare two files larger than memory.

                    TODO is there an easier way than reading each?
                */
                {
                }

                // # Append to file
                {
                    std::ofstream ofs(path);

                    if (ofs) {
                        ofs << data;
                        ofs.close();
                    } else {
                        ios_write_fail(path);
                    }

                    /*
                    # open

                    # Reopen

                        Can be used to reopen ofstream with new properties.

                        Also consider clearing error flags if there can be any.
                    */
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
        # path

        # directory

        # join

            Like in C, no system independant path or directory operations (for the love of God...)

            Boost does have a system independant path separator.

            Some Boost fs features were proposed on TR2.
        */
    }

    /*
    # main return

        Like in C99, C++ return can omit the return, in which case it returns 0.
    */

        return EXIT_SUCCESS;

    // global/static destructors happen at exit time.
}
