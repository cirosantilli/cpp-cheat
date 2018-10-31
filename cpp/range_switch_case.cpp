// # Range switch case
//
// http://stackoverflow.com/questions/9432226/how-do-i-select-a-range-of-values-in-a-switch-statement/42331563#42331563

#include "common.hpp"

int main() {
    // Test case.
    const std::map<int, int> result{
        {-1, -1},
        { 0,  0},
        { 1,  0},
        { 2,  2},
        { 3,  2},
        { 4,  2},
        { 5,  5},
        { 6,  5},
        { 7,  7},
    };

    // Raw lambda map.
    {
        int x;
        const std::map<int,std::function<void()>> m{
            {0, [&](){
                x = -1;
            }},
            {2, [&](){
                x = 0;
            }},
            {5, [&](){
                x = 2;
            }},
            {7, [&](){
                x = 5;
            }}
        };
        const auto end = m.end();
        for (auto i = -1; i < 8; ++i) {
            auto it = m.upper_bound(i);
            if (it == end) {
                x = 7;
            } else {
                it->second();
            }
            assert(x == result.at(i));
        }
    }

    // How to use the range pattern from a method.
    // The key is to static initialize the lambda map.
    {
        struct RangeSwitch {
            int method(int x) {
                static const std::map<int,std::function<void(int&)>> m{
                    {0, [&](int &x){
                        x = -1;
                    }},
                    {2, [&](int &x){
                        x = 0;
                    }},
                    {5, [&](int &x){
                        x = 2;
                    }},
                    {7, [&](int &x){
                        x = 5;
                    }}
                };
                static const auto end = m.end();
                auto it = m.upper_bound(x);
                if (it == end) {
                    x = 7;
                } else {
                    it->second(x);
                }
                return x;
            }
        };
        RangeSwitch rangeSwitch;
        for (auto i = -1; i < 8; ++i) {
            assert(rangeSwitch.method(i) == result.at(i));
        }
    }
}
