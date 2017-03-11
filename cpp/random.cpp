#include "common.hpp"

int main() {
    /*
    # random_device

        Ultimate C++11 method to seed a PRNG, wraps over `/dev/urandom`.

        http://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand/13004555#13004555
    */
    {
        std::random_device dev;
        unsigned int seed = dev();
        std::mt19937 prng(seed);
        std::uniform_int_distribution<> dist(1, 10);
        for (unsigned int i = 0; i < 10; ++i) {
            // std::cout << dist(prng) << std::endl;
        }
    }
}
