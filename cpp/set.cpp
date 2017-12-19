/*
# set

    -   unique elements: inserting twice does nothing

    -   always ordered: $O(log)$ find / insert

    -   immutable elements: it is not possible to modify an object,
        one must first remove it and resinsert.

        This is so because modification may mean reordering.
*/

#include "common.hpp"

// Non key searches.

    class MemberKey {
        public:
            // Note that there is _no_ conversion constructor,
            // everything is done at the template level without
            // intermediate object creation.
            //MemberKey(int key) : key(key) {}
            MemberKey(int key, int notkey) : key(key), notkey(notkey) {}
            int key;
            int notkey;
    };

    bool operator<(const MemberKey& c, int key) { return c.key < key; }
    bool operator<(int key, const MemberKey& c) { return key < c.key; }
    bool operator<(const MemberKey& c, const MemberKey& d) {
        return c.key < d.key;
    }

    //bool operator<(const std::unique_ptr<MemberKey>& c, int key) { return *c < key; }
    //bool operator<(int key, const std::unique_ptr<MemberKey>& c) { return key < *c; }
    // Works but not very cool as it hides the default unique_ptr::operator<,
    // which is meaningful for arrays like regular pointers are.
    //bool operator<(const std::unique_ptr<MemberKey>& c, const std::unique_ptr<MemberKey>& d) {
        //return c->key < d->key;
    //}

    struct PointerCmp {
        // Required for the heterogeneous searches to be found by compiler.
        // Value does not seem to matter, only presence, but std::true_type is a good choice semantically.
        typedef std::true_type is_transparent;
        typedef std::unique_ptr<MemberKey> T;
        bool operator()(const T& c, int key) const { return *c < key; }
        bool operator()(int key, const T& c) const { return key < *c; }
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs->key < rhs->key;
        }
    };

int main() {
    // C++11 initializer list
    {
        {
            std::set<int> s{1, 2, 0, 1};
            std::set<int> s2{0, 1, 2};
            assert(s == s2);
        }

        {
            std::set<std::string> s = {"a", "c", "b", "a"};
            std::set<std::string> s1 = {"a","b", "c"};
            assert(s == s1);
        }
    }

    // You can modify objects if you store pointers.
    {
        int i = 0;
        std::set<int*> s;
        s.insert(&i);
        std::set<int*>::iterator it = s.find(&i);
        *(*it) = 1;
        assert(i == 1);
    }

    /*
    # insert

        Return is a pair conatining:

        - if the item was not present, an iterator to the item inserted and true
        - if the item was     present, an iterator to the existing item inserted and false
    */
    {
        std::pair<std::set<int,std::string>::iterator,bool> ret;
        std::set<int> s;

        ret = s.insert(1);
        assert(ret.first == s.find(1));
        assert(ret.second == true);

        ret = s.insert(2);
        assert(ret.first == s.find(2));
        assert(ret.second == true);

        ret = s.insert(0);
        assert(ret.first == s.find(0));
        assert(ret.second == true);

        // Item already present:
        // nothing is done and returns false on the pair.
        ret = s.insert(1);
        assert(ret.first == s.find(1));
        assert(ret.second == false);

        std::set<int> s1 = {0, 1, 2};
        assert(s == s1);
    }

    /*
    # erase

        Remove element from set.

        Returns number of elements removed (either 0 or 1).
    */
    {
        std::set<int> s = {0, 1, 2};

        assert(s.erase(1) == 1);
        std::set<int> s2 = {0, 2};
        assert(s == s2);

        assert(s.erase(1) == 0);
    }

    // ERROR no random access since it uses bidirection iterator.
    {
        //cout << s[0] << endl;
    }

    // size
    {
        std::set<int> s;
        assert(s.size() == 0);
        s.insert(0);
        assert(s.size() == 1);
    }

    /*
    iterate

        Biderectional iterator.

        Always sorted by key:
        http://stackoverflow.com/questions/8833938/is-the-stdset-iteration-order-always-ascending-according-to-the-c-specificat/41424755#41424755

        This basically forces a balanced tree implementation instead of hash set,
        and requires < > operators to be implemented on the value.

        Sorted by insertion order does not exist:
        http://stackoverflow.com/questions/7801109/does-the-c-standard-library-have-a-set-ordered-by-insertion-order
    */
    {
        std::set<int> s;
        s.insert(2);
        s.insert(1);
        auto it = s.begin();
        assert(*it == 1);
        it++;
        assert(*it == 2);
        it++;
        assert(it == s.end());
    }

    /*
    # find

        If found, returns an iterator pointing to the element.
        Else, returns `map::end()`

        find is `log n` time since the container is ordered.
    */
    {
        std::set<int> s = {0, 1, 2};
        std::set<int>::iterator it;

        it = s.find(1);
        assert(*it == 1);

        it = s.find(3);
        assert(it == s.end());
    }

    /*
    count

        Count how many times an item is in the set.

        Can only return 1 or 0.

        Equivalent to doing a find.
    */
    {
        std::set<int> s = {1, 2, 0, 1};
        assert(s.count(1) == 1);
        assert(s.count(3) == 0);
    }

    /*
    # Modify key.

    # Update

        Impossible without either:

        - remove and re-insert (possibly with hint), which is the right way
        - hacks like `mutable`

        Because `std::set<X>::iterator` is actually `const` by the standard:

        - http://stackoverflow.com/questions/908949/what-happens-when-you-modify-an-element-of-an-stdset
        - http://stackoverflow.com/questions/2217878/c-stl-set-update-is-tedious-i-cant-change-an-element-in-place
        - http://stackoverflow.com/questions/7340434/how-to-update-an-existing-element-of-stdset
        - http://stackoverflow.com/questions/6068167/is-this-safe-mutability-and-sets

        # Hint

            If an iterator is given, it serves as a hint to where the new value is likely to be inserted.

            This is speciall useful if you want to update a value,
            but expect the new result to be in the same position.
    */
    {
        class C {
            public:
                C(int i) : i(i) {}
                bool operator<(const C& other) const { return this->i < other.i; }
                bool operator==(const C& other) const { return this->i == other.i; }
                bool operator>(const C& other) const { return this->i > other.i; }
                mutable int i;
        };
        std::set<C> s;
        s.insert(C(1));
        s.insert(C(2));
        auto it = s.find(C(1));
        //*it = C(3);
        // Almost certainly bad, but I can't find the C++ quote that says so.
        it->i = 3;
    }

    // Search by non-key comparable
    // - http://stackoverflow.com/questions/17375780/is-it-possible-to-use-elements-of-a-different-type-than-contained-in-a-stdset
    // - http://stackoverflow.com/questions/20317413/what-are-transparent-comparators
    {
        // Member is key, operators injected as comparisions with memeber make sense.
        // http://stackoverflow.com/questions/13827973/c-map-container-where-key-is-part-of-value/41624995#41624995
        {
            std::set<MemberKey, std::less<>> s;
            s.insert(MemberKey(1, -1));
            s.insert(MemberKey(2, -2));
            s.insert(MemberKey(0,  0));
            s.insert(MemberKey(3, -3));
            assert(s.find(0)->notkey ==  0);
            assert(s.find(1)->notkey == -1);
            assert(s.find(2)->notkey == -2);
            assert(s.find(3)->notkey == -3);
            assert(s.find(MemberKey(1, 1234))->notkey == -1);
        }

        // unique_ptr
        // - http://stackoverflow.com/questions/18939882/raw-pointer-lookup-for-sets-of-unique-ptrs
        // - http://stackoverflow.com/questions/17851088/using-a-stdunordered-set-of-stdunique-ptr
        {
            // Less good solution with a hidden operator<.
            {
                //std::set<std::unique_ptr<MemberKey>, std::less<>> s;
                //s.insert(std::make_unique<MemberKey>(1, -1));
                //s.insert(std::make_unique<MemberKey>(2, -2));
                //s.insert(std::make_unique<MemberKey>(0,  0));
                //s.insert(std::make_unique<MemberKey>(3, -3));
                //assert((*s.find(0))->notkey ==  0);
                //assert((*s.find(1))->notkey == -1);
                //assert((*s.find(2))->notkey == -2);
                //assert((*s.find(3))->notkey == -3);
            }

            // Better solution with a custom comparator.
            {
                std::set<std::unique_ptr<MemberKey>, PointerCmp> s;
                s.insert(std::make_unique<MemberKey>(1, -1));
                s.insert(std::make_unique<MemberKey>(2, -2));
                s.insert(std::make_unique<MemberKey>(0,  0));
                s.insert(std::make_unique<MemberKey>(3, -3));
                assert((*s.find(0))->notkey ==  0);
                assert((*s.find(1))->notkey == -1);
                assert((*s.find(2))->notkey == -2);
                assert((*s.find(3))->notkey == -3);
            }
        }
    }
}
