/**
Sketches of how to implement famous data structures and algorithms.

The goal of those implementations is only educational.

It is a great exercise to try and implement the fundamental data structures yourself,
as you will probably meet new needs and difficulties which will lead you to learn more C++.

Obviously, don't reimplement classical algorithms from scratch for serious use,
as more performant implementations certainly exist already.
*/

//#define DEBUG_OUTPUT

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
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

                - if it is not the current node, its pasrent
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
Represents a directed graph via adjency lists.
*/
class GraphList {
    public:
        typedef std::vector<int>::size_type EdgeNumberType ;
        class Edge {
            public:
                Edge(){}
                Edge( EdgeNumberType to, int weight ) : to(to), weight(weight) {}

                // To which vertex this edge goes to.
                EdgeNumberType to;
                int weight;
        };
        typedef std::pair<EdgeNumberType,std::vector<Edge> > NodeEdgesPair;

        GraphList() {}
        GraphList(std::initializer_list<NodeEdgesPair> pairs) {
            for (auto& pair : pairs)
                this->add( pair );
        }

        /**
        Adds a node / edges pair to the graph.

        If the node number is larger than the current number of nodes, the current number of
        nodes is increased to fit that new list of edges.

        No error check is done to see if one of the edges points to a destination node that is not in the graph,
        If you add such an edge, you must also explicitly add the node afterwards, even if it has no edges coming
        out of it for example via:

            graph.add({1234, {}});
        */
        void add(NodeEdgesPair pair) {
            EdgeNumberType node_number = pair.first;
            if (nodes.size() < node_number + 1) {
                nodes.resize(node_number + 1);
            }
            nodes[node_number] = pair.second;
        }

        std::string str() const {
            std::stringstream ss;
            for (EdgeNumberType i = 0; i < nodes.size(); ++i) {
                ss << i << ": ";
                for (auto& edge : nodes[i]) {
                    ss << edge.to << "," << edge.weight << " ";
                }
                ss << std::endl;
            }
            return ss.str();
        }

        /**
        Calculates the single source shortest path from one node to another.

        Recommended for dense graphs (unordered list implementation).

        The weights of the graph must all be positive. No check is done to determine that.

        @param[in] from, to Node numbers of source and destination respectively.

            If `from == to`, a 0 length path is assumed to exist even if there is no edge from `from` to itself.

            If either `from` or `to` not in the graph, the behaviour is undefined (possibly an infinite loop).

        @param[out] path

            - if a path exists, this it shall be modified to contain one of the shortest paths from from to to.

                In case that there are mutiple solutions, only one of them shall be found and it is not predictable which.

                The output shall be of type: `{from, X, Y, Z, ..., to}`.

                This is still valid if `to == from`, in which case the output will be of type: `{from, from}`

            - else: this parameter shall be modified to be equal to an empty container.
        */
        void dijikstra(const EdgeNumberType& from,
                    const EdgeNumberType& to,
                    std::vector<EdgeNumberType>& path) const {
            std::list<EdgeNumberType> not_visited;  // This is better as a list than an array, so that it is possible to loop over the non-visited nodes only to find the next min one.
            std::vector<int> distances(nodes.size(), std::numeric_limits<int>::max());
            std::vector<EdgeNumberType> previous(nodes.size());
            EdgeNumberType cur(from);
            distances[from] = 0;
            for (EdgeNumberType i = 0; i < nodes.size(); i++) {
                if (i != from)
                    not_visited.push_back(i);
            }
            path = std::vector<EdgeNumberType>();
            while (cur != to) {
                //DEBUG prints!
                /*
                std::cout << "cur = " << cur << std::endl;
                std::cout << "distances = ";
                for (auto& d : distances) std::cout << d << " " ;
                std::cout << std::endl;
                std::cout << "not_visited = ";
                for (auto& d : not_visited) std::cout << d << " " ;
                std::cout << std::endl;
                std::cout.flush();
                */
                // Update weights of nodes neighbour to cur.
                for (auto& edge : nodes[cur]) {
                        int new_distance = distances[cur] + edge.weight;
                        if (new_distance < distances[edge.to]) {
                            distances[edge.to] = new_distance;
                            previous[edge.to] = cur;
                        }
                }
                // Find non visited min and make it current.
                int min_distance = std::numeric_limits<int>::max();
                auto min_not_visited_it = not_visited.begin();
                for (auto it = not_visited.begin(); it != not_visited.end(); ++it) {
                    if (distances[*it] < min_distance) {
                        min_distance = distances[*it];
                        min_not_visited_it = it;
                    }
                }
                // Next has infinite distance: graph not connected.
                if (distances[*min_not_visited_it] == std::numeric_limits<int>::max())
                    return;
                cur = *min_not_visited_it;
                not_visited.erase(min_not_visited_it);
            }
            // Rebuild the path.
            cur = to;
            path.push_back(to);
            cur = previous[cur];
            while (cur != from) {
                path.push_back(cur);
                cur = previous[cur];
            }
            path.push_back(from);
            std::reverse(path.begin(), path.end()); //TODO with a push_front container this would not be necessary.
                                                    //so what to do? force the users to give push_front containers?
        }

        /**
        Calculates the single source shortest path from one node to another.

        Recommended for sparse graphs (Fibonacci heap implementation).

        Has not been implemented because there is no Fibonacci heap in the STL, only in Boost.
        */
        void dijikstraSparse(const EdgeNumberType& from,
                    const EdgeNumberType& to,
                    std::vector<EdgeNumberType>& path) {}

    private:
        std::vector<std::vector<Edge> > nodes;

        friend std::ostream& operator<<(std::ostream& os, const GraphList& rhs) {
            return os << rhs.str();
        }
};

/**
Solves the 0-1 knapsack problem via dynamic programming.

All inputs must be contain only positive integer types.

The input is expected to be normalized beforehand, that is,
all values, weights and the maximum weight must have already been divided
by the GCD of all of those values, or this algorithm will be very memory inneficient.

@param[in] weights      Weight of each item.
@param[in] values       Value of each item.
@param[in] max_weight   Maximum weight to be carried.
@param[out] output      Modified to contain one of the sets of element indexes that reaches the minimum.

    If this container is ordered, no sorting shall be done on it, and the item order is unspecified.

    If more than one optimal solution exists, it is not specified which one shall be returned.

@param[out] output_value The maximum value attained by the solution.

@tparam WEIGHT data type of the weights
@tparam VALUE  data type of the values
*/
template<typename WEIGHT = int, typename VALUE = int>
void Knapsack01Dynamic(const std::vector<WEIGHT>& weights,
                const std::vector<VALUE>& values,
                WEIGHT max_weight,
                std::vector<typename std::vector<WEIGHT>::size_type>& output,
                VALUE& output_value) {
    typename std::vector<WEIGHT>::size_type number_items = weights.size();
    std::vector<std::vector<VALUE>> sub_problems(number_items + 1,
                                                 std::vector<VALUE>(max_weight + 1));
    std::vector<std::vector<bool>> accepted_items(number_items + 1,
                                             std::vector<bool>(max_weight + 1));
    for (typename std::vector<WEIGHT>::size_type i = 1; i <= number_items; ++i ) {
        for (WEIGHT w = 1; w <= max_weight; ++w ) {
            if (weights[i] <= w) {
                VALUE new_optimum_if_accept = values[i] + sub_problems[i - 1][w - weights[i]];
                if (new_optimum_if_accept > sub_problems[i - 1][w]) {
                    accepted_items[i][w] = true;
                    sub_problems[i][w] = new_optimum_if_accept;
                    continue;
                }
            }
            sub_problems[i][w] = sub_problems[i - 1][w];
        }
    }
    output_value = sub_problems[number_items][max_weight];
    // Generate the solution.
    for (typename std::vector<WEIGHT>::size_type i = number_items; i > 0; --i) {
        if (accepted_items[i][max_weight]) {
            output.push_back(i);
            max_weight -= weights[i];
        }
    }
}

void VectorSum(const std::vector<int>& v0, const std::vector<int>& v1, std::vector<int>& output) {
    output.resize(v0.size());
    for (std::vector<int>::size_type i = 0; i < v0.size(); ++i)
        output[i] = v0[i] + v1[i];
}

/**
Solves the change making problem via dynamic programming.

Given a value `total`, choose the minimum ammount of coins
with one of the values inside `coin_values` that sums up to exactly `total`.

@param[in] coin_values  The value of each type of coin. Must be already ordered.
                        All values must be positive.
@param[in] total        The total value that must be reached with the coins.
                        Must be positive.
@param[out] output      The solution, that is, how many of each type of coin is needed to attain the total.

    If the total is not attainable, this container shall be empty.
*/
void MakeChange(const std::vector<int>& coin_values, int total, std::vector<int>& output) {
    std::vector<bool> possible(total + 1, false);
    std::vector<int> coin_counts(total + 1, std::numeric_limits<int>::max());
    std::vector<std::vector<int> > solutions(total + 1, std::vector<int>(coin_values.size(), 0));
    possible[0] = true;
    coin_counts[0] = 0;
    for (std::vector<int>::size_type i = 0; i < coin_values.size(); ++i) {
        int coin_value = coin_values[i];
        possible[coin_value] = true;
        solutions[coin_value][i] = 1;
        coin_counts[coin_value] = 1;
    }
    for (int subtotal = 1; subtotal <= total; ++subtotal) {
        /*
        std::cout << "subtotal = " << subtotal << std::endl;
        std::cout << "possible    = ";
        for (auto i : possible) std::cout << i << " ";
        std::cout << std::endl;
        std::cout << "coin_counts = ";
        for (auto& i : coin_counts) std::cout << i << " ";
        std::cout << std::endl;
        std::cout << std::endl;
        */
        int min_coin_count = coin_counts[subtotal];
        int best_first, best_second;
        bool cur_possible = false;
        for (int first = 0; first <= subtotal / 2; ++first) {
            int second = subtotal - first;
            if (possible[first] && possible[second]) {
                /*
                std::cout << "first = " << first << std::endl;
                std::cout << "second = " << second << std::endl;
                std::cout << "coin_counts[first] = " << coin_counts[first] << std::endl;
                std::cout << "coin_counts[second] = " << coin_counts[second] << std::endl;
                std::cout << "min_coin_count = " << min_coin_count << std::endl;
                std::cout << std::endl;
                */
                int new_coin_count = coin_counts[first] + coin_counts[second];
                if (new_coin_count < min_coin_count) {
                    best_first = first;
                    best_second = second;
                    min_coin_count = new_coin_count;
                    cur_possible = true;
                }
            }
        }
        if (cur_possible) {
            possible[subtotal] = true;
            coin_counts[subtotal] = coin_counts[best_first]
                + coin_counts[best_second];
            VectorSum(solutions[best_first], solutions[best_second], solutions[subtotal]);
        }
    }
    /*
    std::cout << "possible    = ";
    for (auto i : possible) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "coin_counts = ";
    for (auto& i : coin_counts) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    for (auto& solution : solutions) {
        for (auto& i : solution) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    */
    output = solutions[total];
}

/**
Sorts the input vector via merge sort.

@parm[in,out]  input      The input vector to be sorted. It shall be modified to contain the output.
@tparm         COMPARABLE A type that supports operators `<` and `==`.
*/
template<typename COMPARABLE = int>
void MergeSort(std::vector<COMPARABLE>& input) {
    typename std::vector<COMPARABLE>::size_type input_size, current_size, left0, right0, left1, right1, output_position, size_pow2;
    typename std::vector<COMPARABLE>::iterator output_begin;
    auto input_begin = input.begin();
    input_size = input.size();
    std::vector<COMPARABLE> output(input_size);
    if (input_size < 2)
        return;
    size_pow2 = std::pow(2, std::ceil(std::log2(input_size)));
    current_size = 1;
    output_begin = output.begin();
    while (current_size <= size_pow2 / 2) {
#ifdef DEBUG_OUTPUT
        std::cout << "current_size = " << current_size << std::endl << std::endl;
#endif
        output_position = 0;
        while (output_position < input_size) {
            left0  = output_position;
            right0 = left0  + current_size;
            left1  = right0;
            right1 = right0 + current_size;
            // Make corrections in case the input size is not a power of 2.
            if (right0 > input_size) {
                right0 = input_size;
                // If left1 == right1, no data access is ever made on the right side.
                // This is what we want since the right side is completely out of range in this case.
                left1 = right1;
            } else if (right1 > input_size) {
                right1 = input_size;
            }
            while (true) {
#ifdef DEBUG_OUTPUT
                std::cout << "output_position = " << output_position << std::endl;
                std::cout << "left0  = " << left0  << std::endl;
                std::cout << "right0 = " << right0 << std::endl;
                std::cout << "left1  = " << left1  << std::endl;
                std::cout << "right1 = " << right1 << std::endl;
#endif
                if (left0 == right0) {
                    std::copy(input_begin + left1, input_begin + right1, output_begin + output_position);
                    output_position += right1 - left1;
                    break;
                } else if (left1 == right1) {
                    std::copy(input_begin + left0, input_begin + right0, output_begin + output_position);
                    output_position += right0 - left0;
                    break;
                }
                if (input[left0] < input[left1]) {
                    output[output_position] = input[left0];
                    left0++;
                } else {
                    output[output_position] = input[left1];
                    left1++;
                }
                output_position++;
#ifdef DEBUG_OUTPUT
                std::cout << "output = ";
                for (auto& i : output) std::cout << i << " ";
                std::cout << std::endl;
                std::cout << std::endl;
#endif
            }
        }
        input = output;
        current_size *= 2;
    }
}

/**
Sorts the input vector via quick sort.

Same interface as MergeSort.
*/
template<typename COMPARABLE = int>
void QuickSort(std::vector<COMPARABLE>& input) {
    typedef typename std::vector<COMPARABLE>::size_type SizeType;
    SizeType left_begin, left, right, pivot;
    std::vector<std::pair<SizeType,SizeType>> recursion_stack{{0, input.size() - 1}};
    while (!recursion_stack.empty()) {
        std::tie(left_begin, pivot) = recursion_stack.back();
        recursion_stack.pop_back();
        left = left_begin;
        right = left;
#ifdef DEBUG_OUTPUT
                std::cout << "left_begin = " << left_begin  << std::endl;
                std::cout << "left       = " << left        << std::endl;
                std::cout << "right      = " << right       << std::endl;
                std::cout << "pivot      = " << pivot       << std::endl;
#endif
        while (right < pivot) {
            if (input[right] < input[pivot]) {
                std::swap(input[left], input[right]);
                left++;
            }
            right++;
        }
        std::swap(input[left], input[pivot]);
#ifdef DEBUG_OUTPUT
                std::cout << "left  = " << left << std::endl;
                std::cout << "input = ";
                for (auto& i : input) std::cout << i << " ";
                std::cout << std::endl;
                std::cout << std::endl;
#endif
        if (left_begin + 1 < left)
            recursion_stack.push_back({left_begin, left - 1});
        if (left + 1 < pivot)
            recursion_stack.push_back({left + 1, pivot});
    }
}

int main(int argc, char **argv)
{
    typedef Hash<int,int> map_t;
    //map_t mapOrig(0, 1);
    map_t mapOrig{
        { 0, 1},
        { 1, 2},
        { 2, 3},
        { 3, 4},
        { 4, 5},
        {-1, 0},
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

                map.add(5, 6);
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
            map.add( 1,  2 );
            map.add( 2,  3 );
            map.add( 4,  5 );
            map.add( 8,  9 );
            map.add( 16, 17 );

            //find
            assert( map.find( 8, val) );
            assert( val == 9 );

            //del
            map.del(0);
            assert( ! map.find( 0, val ) );
    }

    // Graphs.
    {
        // Dijikstra tests.
        {
            // Input graphs and origin dest pair and expected output shortest paths.

            typedef std::tuple<GraphList,
                               std::pair<GraphList::EdgeNumberType,GraphList::EdgeNumberType>,
                               std::vector<GraphList::EdgeNumberType> > InOut;

            InOut in_outs[]{
                // InOut needed because tuple constructors are explicit
                // Edge case: path to self with edge to self.
                InOut{
                    {
                        {0, {{0, 0}}},
                    },
                    {0, 0},
                    {0, 0}
                },
                // Edge case: path to self with no edge to self.
                InOut{
                    {
                        {0, {}},
                    },
                    {0, 0},
                    {0, 0}
                },
                InOut{
                    {
                        {0, {{1, 1}}},
                        {1, {}},
                    },
                    {0, 1},
                    {0, 1}
                },
                InOut{
                    {
                        {0, {{1, 1}}},
                        {1, {{2, 1}}},
                        {2, {}},
                    },
                    {0, 2},
                    {0, 1, 2}
                },
                InOut{
                    {
                        {0, {{2, 1}}},
                        {1, {}},
                        {2, {{1, 1}}},
                    },
                    {0, 1},
                    {0, 2, 1}
                },
                // No path.
                InOut{
                    {
                        {0, {}},
                        {1, {}},
                    },
                    {0, 1},
                    {}
                },
                // Exampe close to that drawn at: <http://optlab-server.sce.carleton.ca/POAnimations2007/DijkstrasAlgo.html>
                // Some edges have been made unidirectional, and the ambiguity resolved.
                InOut{
                    {
                        {0, {{1, 2}, {2, 5}, {3, 4}, }},
                        {1, {{2, 2}, {4, 7}, {6, 12} }},
                        {2, {{4, 5}, {5, 3}, {3, 1}, }},
                        {3, {{2, 1}, {5, 4},         }},
                        {4, {{5, 1}, {7, 5},         }},
                        {5, {{4, 1}, {7, 7},         }},
                        {6, {{7, 3},                 }},
                        {7, {                        }},
                    },
                    {0, 7},
                    {0, 1, 2, 5, 4, 7}
                },
            };
            for (auto& in_out : in_outs) {
                auto& graph = std::get<0>(in_out);
                auto& origin_destination = std::get<1>(in_out);
                auto& expected_path = std::get<2>(in_out);
                std::vector<GraphList::EdgeNumberType> path;
                //std::cout << graph << std::endl;
                graph.dijikstra(origin_destination.first, origin_destination.second, path);
                /*
                std::cout << "dijikstra path: ";
                for (auto& node_number : path)
                    std::cout << node_number << " ";
                std::cout << std::endl;
                std::cout << std::endl;
                */
                assert(path == expected_path);
            }
        }
    }

    // Knapsack.
    {
        typedef std::tuple<std::vector<int>,
                           std::vector<int>,
                           int,
                           std::vector<std::vector<int>::size_type> > InOut;

        InOut in_outs[]{
            InOut{
                {1, 2,  3 },
                {6, 10, 12},
                5,
                {1, 2}
            },
            InOut{
                {1, 2, 3, 4 , 5 },
                {3, 8, 7, 10, 14},
                10,
                {1, 2, 4}
            },
        };
        for (auto& in_out : in_outs) {
            auto& weights = std::get<0>(in_out);
            auto& values  = std::get<1>(in_out);
            auto& max_weight  = std::get<2>(in_out);
            auto& expected_output = std::get<3>(in_out);
            std::vector<GraphList::EdgeNumberType> output;
            int output_value;

#ifdef DEBUG_OUTPUT
            std::cout << "max_weight = " << max_weight << std::endl;

            std::cout << "weights = ";
            for (auto& i : weights) std::cout << i << " ";
            std::cout << std::endl;

            std::cout << "values = ";
            for (auto& i : values) std::cout << i << " ";
            std::cout << std::endl;
#endif

            Knapsack01Dynamic(weights, values, max_weight, output, output_value);
            std::sort(output.begin(), output.end());
            std::sort(expected_output.begin(), expected_output.end());

#ifdef DEBUG_OUTPUT
            std::cout << "output_value = " << output_value << std::endl;

            std::cout << "output = ";
            for (auto& i : output) std::cout << i << " ";
            std::cout << std::endl;

            std::cout << "expected_output = ";
            for (auto& i : expected_output) std::cout << i << " ";
            std::cout << std::endl;

            std::cout << std::endl;
#endif

            assert(output == expected_output);
        }
    }

    // Make change.
    {
        typedef std::tuple<std::vector<int>,
                           int,
                           std::vector<int> > InOut;

        InOut in_outs[]{
            InOut{
                {1, 3, 4},
                6,
                {0, 2, 0}
            },
            InOut{
                {1, 3, 4, 7, 11, 24},
                1731,
                {0, 1, 0, 0, 0, 72}
            },
        };
        for (auto& in_out : in_outs) {
            auto& coin_values = std::get<0>(in_out);
            auto& total  = std::get<1>(in_out);
            auto& expected_output = std::get<2>(in_out);
            std::vector<int> output;

#ifdef DEBUG_OUTPUT
            std::cout << "total = " << total << std::endl;

            std::cout << "coin_values = ";
            for (auto& i : coin_values) std::cout << i << " ";
            std::cout << std::endl;
#endif

            MakeChange(coin_values, total, output);

#ifdef DEBUG_OUTPUT
            std::cout << "output = ";
            for (auto& i : output) std::cout << i << " ";
            std::cout << std::endl;

            std::cout << "expected_output = ";
            for (auto& i : expected_output) std::cout << i << " ";
            std::cout << std::endl;

            std::cout << std::endl;
#endif

            assert(output == expected_output);
        }
    }

    // Sort.
    {
        typedef std::tuple<std::vector<int>,
                           std::vector<int> > InOut;

        InOut in_outs[]{
            InOut{
                {1, 3, 2, 0},
                {0, 1, 2, 3}
            },
            InOut{
                {4, 5, 6, 2, 1, 3, 0, 7},
                {0, 1, 2, 3, 4, 5, 6, 7}
            },
            // Size not power of 2, specially 2^n + 1
            // Edgy for merge sort.
            InOut{
                {1, 2, 0},
                {0, 1, 2}
            },
            InOut{
                {1, 4, 0, 2, 3},
                {0, 1, 2, 3, 4}
            },
        };
        void (*algorithms[])(std::vector<int>&){MergeSort, QuickSort};
        for (auto& algorithm : algorithms) {
            for (auto& in_out : in_outs) {
                auto input = std::get<0>(in_out);
                auto expected_output = std::get<1>(in_out);
#ifdef DEBUG_OUTPUT
                std::cout << "input = ";
                for (auto& i : input) std::cout << i << " ";
                std::cout << std::endl;
                std::cout << std::endl;
#endif
                (*algorithm)(input);
#ifdef DEBUG_OUTPUT
                std::cout << std::endl;

                std::cout << "output = ";
                for (auto& i : input) std::cout << i << " ";
                std::cout << std::endl;

                std::cout << "expected_output = ";
                for (auto& i : expected_output) std::cout << i << " ";
                std::cout << std::endl;

                std::cout << std::endl;
#endif
                assert(input == expected_output);
            }
        }
    }

    return EXIT_SUCCESS;
}
