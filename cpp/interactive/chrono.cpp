/*
# chrono

What the clocks map to in GCC Linux:
http://stackoverflow.com/questions/12392278/measure-time-in-linux-time-vs-clock-vs-getrusage-vs-clock-gettime-vs-gettimeof
*/

#include "common.hpp"

int main() {
#if __cplusplus >= 201103L
    // # period
    std::cout << "high_resolution_clock::period::den = " << std::chrono::high_resolution_clock::period::den << std::endl;
    std::cout << "steady_clock::period::den          = " << std::chrono::steady_clock::period::den << std::endl;
    std::cout << "system_clock::period::den          = " << std::chrono::system_clock::period::den << std::endl;

    // high_resolution_clock
    // Wall clock: sleeps are counted.
    {
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> dt = end_time - start_time;
        std::cout << "high_resolution_clock after sleep = " << std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count() << std::endl;
    }

    // steady_clock
    {
        auto start_time = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto end_time = std::chrono::steady_clock::now();
        auto dt = end_time - start_time;
        std::cout << "steady_clock after sleep = " << std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count() << std::endl;
    }

    // system_clock
    {
        auto start_time = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto end_time = std::chrono::system_clock::now();
        auto dt = end_time - start_time;
        std::cout << "system_clock after sleep = " << std::chrono::duration_cast<std::chrono::nanoseconds>(dt).count() << std::endl;
    }

    /*
    # time_point

    Convertions to base types:

    - http://stackoverflow.com/questions/12835577/how-to-convert-stdchronotime-point-to-calendar-datetime-string-with-fraction
    - http://stackoverflow.com/questions/33785564/how-do-i-get-seconds-since-epoch-as-a-double-given-a-time-point
    - http://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back
    */
    {
        std::cout << "nanoseconds since system_clock epoch = " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
        std::cout << "nanoseconds since steady_clock epoch = " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() << std::endl;
    }
	return 0;
#endif
}
