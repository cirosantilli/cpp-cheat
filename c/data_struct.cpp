/*
This contains no details on basic language features,
but sketches of how to implement data structures.

The goal of those implementations is only educational.
Obviously, don't reimplement standard data structers, but use the existing STL ones instead.
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

/*
Binary search tree node.

Implements a map.
*/

template<class KEY, class VAL>
class BST
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

        ~BST() {
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

        bool operator==(BST<KEY,VAL>& other) const {

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
        Find the value for a given key under the current node.

        @key: key to search for.
        @val: output only.

            If the key is found, will be modified to contain the output value for the key.

            Otherwise, its value will not be changed.

        @return: true iff the key was found
        */
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

        bool del( const KEY& key ) {
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
};

int main(int argc, char** argv)
{
    BST<int,int> bstOrig(0, 1);
    BST<int,int> bst;
    int val;

    //add
    //create a simple BST which in which we can predict the map

        bstOrig.add(-1, 0);
        bstOrig.add( 2, 3);
        bstOrig.add( 1, 2);
        bstOrig.add( 3, 4);

    //<<

        std::cout << bstOrig << std::endl;

    //==

        bst = bstOrig;
        assert( bst == bstOrig );

    //find

        bst = bstOrig;

        assert( ! bst.find(-2, val) );

        assert( bst.find(-1, val) );
        assert( val == 0 );

        assert( bst.find( 0, val) );
        assert( val == 1 );

        assert( bst.find( 1, val) );
        assert( val == 2 );

        assert( bst.find( 2, val) );
        assert( val == 3 );

        assert( bst.find( 3, val) );
        assert( val == 4 );

    //del

        //bst = bstOrig;
        //bst.del(0);

    return EXIT_SUCCESS;
}
