/*
# chrono
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // TODO
    std::cout << "high_resolution_clock::period::den = " << std::chrono::high_resolution_clock::period::den << std::endl;

    // Wall clock: sleeps are counted.
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
	auto dt = end_time - start_time;

    std::cout << typeid(dt).name() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(dt).count() << std::endl;
	return 0;
#endif
}
