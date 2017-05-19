/*
# file io

# ifstream

# ofstream

# fstream
*/

#include "common.hpp"

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
	auto size = ifs.tellg();
	data_read.resize(size);
	ifs.seekg(0);
	ifs.read(&data_read[0], size);
	ifs.close();
}

int main() {
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
		    assert(false);
		} else {
			try {
				//throw std::ios_base::failure("Error: Could not write to file: " + path);
			} catch (std::ios_base::failure e) {
				std::clog << e.what() << std::endl;
			}
		}
	}

	// # ios::in: flag automatically set for ifstream, but not fstream
	//http://stackoverflow.com/questions/7463410/is-iosin-needed-for-ifstreams-opened-in-binary-mode
}
