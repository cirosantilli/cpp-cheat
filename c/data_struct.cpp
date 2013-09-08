/*
This contains no details on basic language features,
but sketches of how to implement data structures.

The goal of those implementations is only educational.
Obviously, don't reimplement standard data structers, but use the existing STL ones instead.
*/

#include <cassert>
#include <iostream>
#include <sstream>

/*
Binary search tree node.

Implements a map.
*/

std::ostream& operator<<(std::ostream& os, const BST<KEY,VAL>& rhs);

template<class KEY, class VAL>
class BST
{
        KEY key;
        VAL val;
        BST<KEY,VAL>* left;
        BST<KEY,VAL>* right;

    public:

        BST() {
            this->left = NULL;
            this->right = NULL;
        }

        BST( const KEY& key, const VAL& val ) {
            this->key = key;
            this->val = val;
            this->left = NULL;
            this->right = NULL;
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

        /*
        */
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
    BST<int,int> bst(0, 1);
    int val;

    //create a simple BST which in which we can predict the map
    bst.add(-1, 0);
    bst.add( 2, 3);
    bst.add( 1, 2);
    bst.add( 3, 4);

    //template argument deduction takes care of the template for `operator<<`
    std::cout << bst;

    //find

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
}
