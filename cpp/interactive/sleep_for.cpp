// Count to infinity sleeping one second per number.

#include "common.hpp"

int main() {
    int i = 0;
    while (1) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        i++;
    }
}
