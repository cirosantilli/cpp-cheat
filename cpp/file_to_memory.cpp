/*
http://stackoverflow.com/questions/539537/how-to-write-to-a-memory-buffer-with-a-file
*/

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

template <typename char_type>
struct ostreambuf : public std::basic_streambuf<char_type, std::char_traits<char_type> > {
    ostreambuf(char_type* buffer, std::streamsize bufferLength) {
        this->setp(buffer, buffer + bufferLength);
    }
};

void write(std::ostream& os) {
	os << "abc";
}

int main() {
    /* To memory, in our own externally supplied buffer. */
    {
        char c[3];
        ostreambuf<char> buf(c, sizeof(c));
        std::ostream s(&buf);
        write(s);
        assert(memcmp(c, "abc", sizeof(c)) == 0);
    }

    /* To memory, but in a hidden buffer. */
	{
		std::stringstream s;
		write(s);
		assert(s.str() == "abc");
	}

    /* To file. */
	{
		std::ofstream s("a.tmp");
		write(s);
		s.close();
	}

    /* I think this is implementation defined.
     * pusetbuf calls basic_filebuf::setbuf(). */
	{
	    char c[3];
		std::ofstream s;
        s.rdbuf()->pubsetbuf(c, sizeof c);
		write(s);
		s.close();
        //assert(memcmp(c, "abc", sizeof(c)) == 0);
	}
}
