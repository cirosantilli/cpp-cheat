/*
-   likely hash map backed, thus O(1) instead of O(log(n)) for set

-   uses the std::hash function

    http://stackoverflow.com/questions/15869066/inserting-into-unordered-set-with-custom-hash-function

    http://en.cppreference.com/w/cpp/utility/hash

-   stdlib does not have a hash for tuples... so combining hashes of instance variables is the main question then.

    So you just go with `boost::hash_combine` for now...

    - http://codereview.stackexchange.com/questions/136770/hashing-a-tuple-in-c17
    - http://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
    - http://stackoverflow.com/questions/35985960/c-why-is-boosthash-combine-the-best-way-to-combine-hash-values
    - http://stackoverflow.com/questions/3611951/building-an-unordered-map-with-tuples-as-keys
    - http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set

-   a custom hash for a class can be given either via constructor, or by embedding into std::
*/

#include "common.hpp"

class MyClass {
    public:
        int i;
        int j;
        MyClass(int i, int j) : i(i), j(j) {}
};

bool operator==(const MyClass& lhs, const MyClass& rhs) {
    return lhs.i == rhs.i;
}

namespace std {
  template <>
  struct hash<MyClass> {
    std::size_t operator()(const MyClass& k) const {
        return k.i;
    }
  };
}

int main() {
    std::unordered_set<MyClass> mySet;
    assert(mySet.size() == 0);
    mySet.insert(MyClass(1, 2));
    assert(mySet.size() == 1);
    mySet.insert(MyClass(1, 3));
    assert(mySet.size() == 1);
    assert(mySet.find(MyClass(1, -1))->j == 2);
}
