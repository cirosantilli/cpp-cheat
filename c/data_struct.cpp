/*This contains no details on basic language features,
but sketches of how to implement data structures.

The goal of those implementations is only educational.
Obviously, don't reimplement standard data structers, but use the existing STL ones instead.
*/

#include <algorithm>
#include <cassert>
#include <cmath>        //ceil
#include <functional>
#include <iostream>
#include <list>
#include <sstream>

/**
Interface for a Map.

@tparam KEY the key type of the map
@tparam VAL the value type value of the map.
*/
template<class KEY,class VAL>
class Map {
    virtual bool add( const KEY& key, const VAL& val ) = 0;
    virtual bool del( const KEY& key ) = 0;
    virtual bool find( const KEY& key, VAL& val ) = 0;
};

/*
Binary search tree node.

Implements a map.

@tparam KEY the key type of the map. Must be sortable via `<` family of operators.
@tparam VAL the value type value of the map.

#rationale

    Differentiaing tree objects may be a good thing since some methods such as `==` have different meanings
    for entire subtrees or for single nodes.

    A better possibility may be to make every operator operate nodewise, and give nodes an extra subtree function
    version of those operators.
*/

template<class KEY, class VAL>
class BST : Map<KEY,VAL>
{
        KEY key;
        VAL val;
        BST<KEY,VAL>* left;
        BST<KEY,VAL>* right;

    public:

        BST() : key(0), val(0), left(NULL), right(NULL) {}

        BST( const KEY& key, const VAL& val ) : key(key), val(val), left(NULL), right(NULL) {
        }

        BST( const BST& other ) : key(other.key), val(other.val) {

            if ( other.hasLeft() ) {
                this->left = new BST<KEY,VAL>( *(other.left) );
            } else {
                this->left = NULL;
            }

            if ( other.hasRight() ) {
                this->right = new BST<KEY,VAL>( *(other.right) );
            } else {
                this->right = NULL;
            }
        }

        virtual ~BST() {
            delete this->left;
            delete this->right;
        }

        friend void swap(BST<KEY,VAL>& first, BST<KEY,VAL>& second)
        {
            std::swap(first.key,   second.key);
            std::swap(first.val,   second.val);
            std::swap(first.left,  second.left);
            std::swap(first.right, second.right);
        }

        BST<KEY,VAL>& operator=(BST<KEY,VAL> other)
        {
            swap(*this, other);
            return *this;
        }

#if __cplusplus >= 201103L

        // move constructor
        BST<KEY,VAL>(BST<KEY,VAL>&& other) :
        BST<KEY,VAL>() // initialize via default constructor, C++11 only
        {
            swap(*this, other);
        }

#endif

        bool operator==(const BST<KEY,VAL>& other) const {

            if ( this->key != other.key )
                return false;

            if ( this->val != other.val )
                return false;

            if ( other.hasLeft() ) {
                if ( ! ( *(this->left) == *(other.left) ) )
                    return false;
            } else {
                if ( ! ( this->left == NULL ) )
                    return false;
            }

            if ( other.hasRight() ) {
                if ( ! ( *(this->right) == *(other.right) ) )
                    return false;
            } else {
                if ( ! ( this->right == NULL ) )
                    return false;
            }

            return true;
        }

        bool operator!=(const BST<KEY,VAL>& other) const {
            return ! ( *this == other );
        }

        bool hasLeft() const {
            return this->left != NULL;
        }

        bool hasRight() const {
            return this->right != NULL;
        }

        /*
        Add a key to the BST below current node.

        Retuns `true` if the key was inserted sucessfuly,
        `false` if it was already present.
        */
        bool add( const KEY& key, const VAL& val ) {
            BST<KEY,VAL>* cur = this;
            while ( true ) {
                if ( key == cur->key ) {
                    return false;
                } else if ( key < cur->key ) {
                    if ( cur->hasLeft() ) {
                        cur = cur->left;
                    } else {
                        cur->left = new BST<KEY,VAL>(key, val);
                        return true;
                    }
                } else {
                    if ( cur->hasRight() ) {
                        cur = cur->right;
                    } else {
                        cur->right = new BST<KEY,VAL>(key, val);
                        return true;
                    }
                }
            }
        }

            /*
            add with findNodeAndParent helper

            This is still less efficient than a direct add,
            since a direct add does not keep track of parent and lr.
            */
        /*
        bool add( const KEY& key, const VAL& val ) {

            BST<KEY,VAL> *parent, *node;
            int lr;

            lr = findNodeAndParent(key, parent, node);
            if ( node == NULL ) {
                if( lr < 0 )
                    parent->left = new BST<KEY,VAL>(key, val);
                else
                    parent->right = new BST<KEY,VAL>(key, val);
                return true;
            }
            return false;
        }
        */

        void removeLeft() {
            delete this->left;
            this->left = NULL;
        }

        void removeRight() {
            delete this->right;
            this->right = NULL;
        }

        /**
        Remove either the left or right node depending on rl.

        @parm[in] rl If `-1`, remove left, if `1`, remove right, else do nothing.
        */
        void remove( int rl ) {
            if ( rl == -1 ) {
                delete this->left;
                this->left = NULL;
            } else if ( rl == -1 ) {
                delete this->right;
                this->right = NULL;
            }
        }

        /**
        @brief Find the value for a given key under the current node.

        @param[in]  key key to search for.
        @param[out] val output value found. If not found, `NULL`.
        @return     true iff the key was found

        #rationale

        This could return either the values, or a pointer to the found node.

        If this class is is only a map interface, then it should node return nodes,
        since maps could be implemented in other ways, for example as a hashmap.

        There are other functions such as `del` which can reuse this function if it returns
        pointers.

        A possible solution is then to have a helper that returns pointers,
        and use that helper to implement both this function and `del`.
        */

            /* direct implementation */
        /*
        bool find( const KEY& key, VAL& val ) const {
            const BST<KEY,VAL>* cur = this;
            while ( true ) {
                if ( key == cur->key ) {
                    val = cur->val;
                    return true;
                } else if ( key < cur->key ) {
                    if ( cur->hasLeft() ) {
                        cur = cur->left;
                    } else {
                        return false;
                    }
                } else {
                    if ( cur->hasRight() ) {
                        cur = cur->right;
                    } else {
                        return false;
                    }
                }
            }
        }
        */

            /* Implementation with `findNodeAndParent` helper.

            Better code reuse, but slower as a tradeoff. */
        /*
        bool find( const KEY& key, VAL& val ) const {
            const BST<KEY,VAL> *parent, *node;
            findNodeAndParent(key, parent, node);
            if ( node != NULL ) {
                val = node->val;
                return true;
            }
            return false;
        }
        */

            /* Implementation with `findNode` helper.

            Better code reuse */


        /**
        #todo

        How to make this const correct? In particular, how to call findNode if it were const?
        */
        bool find( const KEY& key, VAL& val ) {
            BST<KEY,VAL> *node;
            findNode(key, node);
            if ( node != NULL ) {
                val = node->val;
                return true;
            }
            return false;
        }

        /**
        Remove key value pair from map.

        @param[in] key key to search
        @return true iff the value was present
        */

        bool del( const KEY& key ) {

            BST<KEY,VAL> *node, *parent, *nextNode, *nextNodeParent; // nextNode: first node that has a larger key than key
            bool hasLeft, hasRight;
            int nodeLr, nextNodeLr;

            //this->findNode(key, node);
            nodeLr = this->findNodeAndParent(key, parent, node);

            if ( node == NULL )
                return false;

            hasLeft = node->hasLeft();
            hasRight = node->hasRight();

            if ( hasRight && hasLeft ) {

                nextNode = node->right;
                nextNodeParent = NULL;
                while ( nextNode->hasLeft() ) {
                    nextNodeParent = nextNode;
                    nextNode = nextNode->left;
                }

                node->key = nextNode->key;
                node->val = nextNode->val;
                nextNodeParent->removeLeft();

            } else if ( hasLeft ) { //only left

                node->key   = node->left->key;
                node->val   = node->left->val;
                node->right = node->left->right;

                nextNode  = node->left->left;
                node->left->left  = NULL;
                node->left->right = NULL;
                delete node->left;
                node->left = nextNode;

            } else if ( hasRight ) { //only right

                node->key   = node->right->key;
                node->val   = node->right->val;
                node->left  = node->right->left;

                nextNode = node->right->right;
                node->right->left  = NULL;
                node->right->right = NULL;
                delete node->right;
                node->right = nextNode;

            } else { // only child

                parent->remove( nodeLr );

            }

            return true;
        }

        /**
        DFS preorder print
        */
        friend std::ostream& operator<<(std::ostream& os, const BST<KEY,VAL>& rhs) {

            bool hasLeft = rhs.hasLeft();
            bool hasRight = rhs.hasRight();
            std::string stringLeft;
            std::string stringRight;

            os << rhs.key << ": ";

            if ( hasLeft ) {
                os << rhs.left->key;
            } else {
                os << "NULL";
            }

            os << ", ";

            if ( hasRight ) {
                os << rhs.right->key;
            } else {
                os << "NULL";
            }

            os << std::endl;

            if ( hasLeft )
                os << *(rhs.left);

            if ( hasRight )
                os << *(rhs.right);

            return os;
        }

    private:

        /**
        Find node and its parent in current node's subtree.

        @param[in]  key key to find
        @param[out] parent output only

            At return points to either:

            - if the node is found

                - if it is not the current node, its parent
                - else, NULL

            - else, the last searched parent node

        @param[out] node

            At return contains:

            - if the node is not found, `NULL`
            - else, points to the node searched for

        @return

            - -1 if `node` was found and is the left  child
            -  1 if `node` was found and is the right child
            -  0 otherwise.

                This could happen either if:

                - the found node is the node given by key
                - the node was not found.

                so this cannot be used to decide if the node was found or not.

        #rationale

            This helper allows for maximal code reuse and minimum memory usage (no parent pointers)
            at the cost of slower speeds.

            If each node had a parent pointer, this helper function would not be necessary for certain methods
            a simpler find would do.

            There are methods for each even having a parent node would not suffice.
            For example, in `add`, if the node cannot be found we do want a pointer to the last searched parent
            so we can add the node there. Up to now this is the only method I could find for which this does not work,
            and if it really the only such method, this function can be ommited and implemented directly inside `add`
            as it gives no code reuse. In the case of add however, using this helper makes things slower,
            because a direct add implementation does not need:

            - `lr = +-1`
            - `parent = node`

            so maybe this helper can never be used for optimal speed.

            Parent nodes can be avoided with this helper for ceratin operations such as `del` and `find`,
            at the cost of making find operations slower,
            since two extra assignments have to be done for each descent:

            - `lr = +-1`
            - `parent = node`

            It is a classic speed / memory tradeoff. In this case it might be better so simply.
        */
        int findNodeAndParent(const KEY& key, BST<KEY,VAL>*& parent, BST<KEY,VAL>*& node) {
            parent = NULL;
            node   = this;
            int lr = 0;
            while ( true ) {
                if ( key == node->key ) {
                    return lr;
                } else {
                    parent = node;
                    if ( key < node->key ) {
                        lr = -1;
                        node = node->left;
                        if ( ! parent->hasLeft() )
                            return 0;
                    } else {
                        lr = 1;
                        node = node->right;
                        if ( ! parent->hasRight() )
                            return 0;
                    }
                }
            }
        }

        /**
        @brief Find a node that has a given key and return a pointer to it.

        @param[in]  key the key to search for.
        @param[out] if the node if found, a pointer to it. Else, NULL.
        @return true iff the node is found
        */
        bool findNode(const KEY& key, BST<KEY,VAL>*& node) {
            node = this;
            while ( true ) {
                if ( key == node->key ) {
                    return true;
                } else {
                    if ( key < node->key ) {
                        node = node->left;
                        if ( node == NULL ) {
                            return false;
                        }
                    } else {
                        node = node->right;
                        if ( node == NULL ) {
                            return false;
                        }
                    }
                }
            }
        }
};

template<class KEY>
size_t hash( KEY key, size_t container_size );

template<>
size_t hash<int>( int key, size_t container_size ){
    return key % container_size;
}

/**
Hash map.

@tparam KEY the key type of the map
@tparam VAL the value value of the map
*/
template<class KEY,class VAL>
class Hash {

        typedef std::vector<std::list<std::pair<KEY,VAL>>> map_t;

    public:

        Hash(
            size_t keyCountInitial = Hash::keyCountInitialDefault,
            float loadFactor = 0.7
            ) :
            keyCount(keyCountInitial),
            loadFactor(loadFactor),
            map( map_t(keyCount) )
        {
        };

        /**
        Initialize hash map with single key value pair
        */
        Hash(
            const KEY& key,
            const VAL& val,
            size_t keyCountInitial = Hash::keyCountInitialDefault,
            float loadFactor = 0.7
            ) : Hash(keyCountInitial, loadFactor)
        {
            this->add( key, val );
        }

        Hash(std::initializer_list<std::pair<KEY,VAL> > pairs) : Hash() {
            for ( auto& pair : pairs )
                this->add( pair );
        }

        bool add( const KEY& key, const VAL& val ) {

            size_t h, newKeyCount, newSize, newHash;
            map_t oldMap;

            h = hash<KEY>( key, map.size() );

            //if already present, return false
            for ( auto& pair : map[h] )
                if ( std::get<0>(pair) == key )
                    return false;

            newKeyCount = this->keyCount + 1;

            //increase size if necessary and rehash everything
            if ( newKeyCount >= this->map.size() * this->loadFactor ) {
                oldMap = this->map; //TODO possible to avoid this costly copy?
                newSize = this->map.size() * this->increaseFactor;
                this->map = map_t( newSize );
                for ( auto& list : oldMap ) {
                    for ( auto& pair : list ) {
                        this->add(pair);
                    }
                }
                h = hash( key, newSize );
            }

            /*
            if ( std::find_if(
                map[h].begin(),
                map[h].end(),
                [&key](std::pair<KEY,VAL> pair){ return std::get<0>(pair) == key; }
            ) != map[h].end() ) {
                return false;
            }
            */

            this->map[h].push_back( std::pair<KEY,VAL>( key, val ) );

            this->keyCount = newKeyCount;

            return true;
        }

        bool add( const std::pair<KEY,VAL>& pair ) {
            return add( std::get<0>(pair), std::get<1>(pair) );
        }

        bool del( const KEY& key ) {

            auto& list = map[ hash<KEY>( key, map.size() ) ];

            /*
            for (auto& pair : list ) {
                if ( std::get<0>(pair) == key )
                    break;
            }
            */

            auto it = std::find_if(
                list.begin(),
                list.end(),
                [&key]( const std::pair<KEY,VAL>& pair ){ return std::get<0>(pair) == key; } );

            if ( it != list.end() ) {
                list.erase( it );
                return true;
            }
            return false;
        }

        bool find( const KEY& key, VAL& val ) const {

            size_t h;

            h = hash<KEY>( key, map.size() );

            for ( auto& pair : map[h] ) {
                if ( std::get<0>(pair) == key ) {
                    val = std::get<1>(pair);
                    return true;
                }
            }
            return false;
        }

        /**
        Get a string representation from a map.
        */
        std::string str() const {
            std::stringstream ss;
            for ( size_t i = 0; i < this->map.size(); i++ ) {
                auto& list = this->map[i];
                if ( list.size() > (size_t)0 ) {
                    ss << i << ": ";
                    for ( auto& pair : list ) {
                        ss << std::get<0>(pair) << ":" << std::get<1>(pair) << ", ";
                    }
                    ss << std::endl;
                }
            }
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& os, const Hash<KEY,VAL>& rhs) {
            return os << rhs.str();
        }

        bool operator==(const Hash<KEY,VAL>& other) const {
            return this->map == other.map;
        }

        bool operator!=(const Hash<KEY,VAL>& other) const {
            return ! ( this->map == other.map );
        }

    private:

        const static size_t keyCountInitialDefault = 1;
        const static int increaseFactor = 2;             /* by how much the map size will be multiplied if it needs to grow */
        size_t keyCount;
        float loadFactor;
        map_t map;
};

/**
Represents a graph via adjency lists.
*/
class GraphList {

    public:

        GraphList(){
        }

    private:

        std::vector<int> lists;
};

class GraphMatrix {

    public:

    private:

};

int main(int argc, char** argv)
{
    typedef Hash<int,int> map_t;
    //map_t mapOrig(0, 1);
    map_t mapOrig{
        std::pair<int,int>(0,1),
        std::pair<int,int>(1,2),
        std::pair<int,int>(2,3),
        std::pair<int,int>(3,4),
        std::pair<int,int>(4,5),
        std::pair<int,int>(-1,0),
    };
    map_t map;
    map_t mapExpect;
    int val;

    for ( int i = 0; i < 1; i++ )
    {

        //add

            //bst test

            //create a bst with all possible deletion cases:
            //
            //- two children
            //- one child
            //- 0   children

                //mapOrig.add( 2, 3);
                //mapOrig.add( 1, 2);
                //mapOrig.add( 3, 4);
                //mapOrig.add( 4, 5);
                //mapOrig.add(-1, 0);

        //<<

            std::cout << mapOrig << std::endl;

        //find

            map = mapOrig;

            assert( ! map.find(-2, val) );

            assert( map.find(-1, val) );
            assert( val == 0 );

            assert( map.find( 0, val) );
            assert( val == 1 );

            assert( map.find( 1, val) );
            assert( val == 2 );

            assert( map.find( 2, val) );
            assert( val == 3 );

            assert( map.find( 3, val) );
            assert( val == 4 );

            assert( map.find( 4, val) );
            assert( val == 5 );

            //==

                map = mapOrig;
                assert( map == mapOrig );

                map.add( 5, 6);
                assert( map != mapOrig );


            //del

                //two children
                map.del(0);
                assert( ! map.find( 0, val ) );

                //leaf
                map = mapOrig;
                map.del(1);
                assert( ! map.find( 1, val ) );

                //one child
                map = mapOrig;
                map.del(3);
                assert( ! map.find( 3, val ) );

        //hash map tests

            //add at powers of 2 the 0 hash so they clutter at hash 0
            map = map_t( 0, 1 );
            map.add( 1, 2 );
            map.add( 2, 3 );
            map.add( 4, 5 );
            map.add( 8, 9 );
            map.add( 16, 17 );

            //find
            assert( map.find( 8, val) );
            assert( val == 9 );

            //del
            map.del(0);
            assert( ! map.find( 0, val ) );
    }

    {
        GraphList g;
    }

    return EXIT_SUCCESS;
}
