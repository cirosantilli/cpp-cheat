/*
# string
*/

#include "common.hpp"

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

int main() {
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

        http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
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

    /*
    # string to int

        http://stackoverflow.com/questions/7663709/convert-string-to-int-c
    */
    {
        // Best C++11 error checking option: stoi
#if __cplusplus >= 201103L
        assert(std::stoi("123") == 123);
#endif
    }
}
