/*
# operator overload

    Like regular functions, C++ also allows operators to be overloaded

    This is not only eye candy, but also allows developpers to forget if they are dealing
    with base types or not, thus making code easier to modify: if we ever decide to move
    from base types to classes we just have to implement the operator overload on classes.

    Great tutorial: <http://stackoverflow.com/questions/4421706/operator-overloading?rq=1>

    Good tutorial, specially on how to implement `=`, `+=` and `+` cases:
    <http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html>

    The following operators can all be overloaded:

        +    -    *    /    =    <    >    +=   -=   *=   /=   << (shift left)   >> (shift right)
        <<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
        ~    &=   ^=   |=   &&   ||   %=   []   ()   ,    ->*  ->   new
        delete    new[]     delete[]

    - typecast operator overload `int()`, `float()`, etc.

    Member or not

        Certain operators can be both member functions and free overloaded functions.
        This includes most operators such as `+`, `=`, `+=` and others.
        See: http://stackoverflow.com/a/4421729/895245 for a discussion on how to decide
        between them.

        One question is that being non member improves the incapsulation, since then those
        functions do not have access to private members, and thus do not reflect changes that are
        otherwise invisible.

        Certain operators *cannot* be member functions, such as `<<`.

        Other *must* be members. Those include:

        - `=`  (assignment)
        - `[]` (array subscription),
        - `->` (member access)
        - `()` (function call)
*/

#include "common.hpp"

/*
ERROR: One of the arguments must be a Class or Enum.

Just imagine the havoc if this were possible! =)
*/

    //int operator+(int i, int j){return i + j + 1;}

/*
class that shows the ideal methods of operator overloading.
*/
class OperatorOverload {

    public:

        int i;

        OperatorOverload() { this->i = 0; }
        OperatorOverload(int i) { this->i = i; }

        /*
        operator=

            Special care must be taken with `=` when memory is dynamically alocated because
            of copy and swap idiom questions.

            This is not the case for this simple class.

        Return non const reference

            Return a *non* const reference because the following is possible for base types:

                (a = b) = c

            which is the same as:

                a = b
                a = c

            so this obscure syntax should also work for classes.
        */
        OperatorOverload& operator=(const OperatorOverload& rhs) {
            this->i = rhs.i;
            return *this;
        }

        /*
        operator+=

            Implement the compound assign, and the non compound in terms of the compound.

            Must return a non-const reference for the same reason as `=`.
        */
        OperatorOverload& operator+=(const OperatorOverload& rhs) {
            this->i += rhs.i;
            return *this;
        }

        /*
        operator++

            - http://stackoverflow.com/questions/3846296/how-to-overload-the-operator-in-two-different-ways-for-postfix-a-and-prefix
            - http://stackoverflow.com/questions/6375697/do-i-have-to-return-a-reference-to-the-object-when-overloading-a-pre-increment-o
            - http://stackoverflow.com/questions/3574831/why-does-the-postfix-increment-operator-take-a-dummy-parameter
        */


            // Prefix. Should return reference to match primitives.
            OperatorOverload& operator++() {
                ++(this->i);
                return *this;
            }

            // Postfix. Should not return reference to match primitives.
            // Yes, this weird `int` dummy argument differentiates signature from prefix.
            const OperatorOverload operator++(int) {
                OperatorOverload old(*this);
                ++(*this);
                return old;
            }

        /*
        Ambiguous call.

            This cannot be distinguished from the member method,
            since the member method gets am implicit `this` first argument.

            Therefore any call to this operator would give an ambiguous message
            if this were defined.

            The effect is the same as the non member function, but the non member is preferred
            because it improves encapsulation.
        */

            /*
                OperatorOverload operator+(OperatorOverload i, OperatorOverload j){
                    OperatorOverload ret;
                    ret.i = i.i + j.i + 1;
                    return ret;
                }
            */

        /*
        # typecast overload

            Automatic conversions will be done using it.

            Notable example on the stdlib: `ifstream::operator bool()` to be able to do `while(getline)` 
            becaues getline returns the updated ifstream.
        */

            operator bool() const { return i % 2 == 1; }
            operator int() const { return i + 1; }
            operator float() const { return ((float)i) + 0.5; }
};

/*
operator+

    Implemented in terms of the compound assign.

    Should be const because the following does nothing:

        (a + b) = c

    Should be an external method, since it is just a function of `+=`.
*/

    OperatorOverload operator+ (const OperatorOverload& lhs, const OperatorOverload& rhs) {
        return OperatorOverload(lhs) += rhs;
    }

/*
Comparison operators: only two are needed: `==` and `<`.

The other are functions of those two.

It is recommended to implement them as non-member functions to increase incapsulation.
*/

    inline bool operator==(const OperatorOverload& lhs, const OperatorOverload& rhs) {return lhs.i == rhs.i;}
    inline bool operator!=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator==(lhs,rhs);}
    inline bool operator< (const OperatorOverload& lhs, const OperatorOverload& rhs) {return lhs.i < rhs.i;}
    inline bool operator> (const OperatorOverload& lhs, const OperatorOverload& rhs) {return  operator< (rhs,lhs);}
    inline bool operator<=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator> (lhs,rhs);}
    inline bool operator>=(const OperatorOverload& lhs, const OperatorOverload& rhs) {return !operator< (lhs,rhs);}

/*
operator<<

    `<<` **cannot** be a member method, because if it were then
    its first argument would be an implicit `Class` for the `this`,
    but the first argument of `<<` must be the `ostream`.

    Therefore it must be a free method outside of a class.

    It is likely that it will need to be a friend of the class in order
    to see its internal fields. This may not be the case in this overly simplified example.
*/

    std::ostream& operator<<(std::ostream& os, const OperatorOverload& c) {
        os << c.i;
        return os;
    }

/*
# number of arguments

    One major difference between regular functions and operators is that operators can only
    have  fixed number of arguments, because they have a very peculiar syntax.

    For example, how could a ternary multiplication possibly be called? ` a * b ???? c` ?

    There are some operators which exist for multiple numbers of arguments with different meaning:

    - `-` with one argument:    unary minus
    - `-` with two arguments:   subtraction

    - `*` with one argument:    dereference
    - `*` with two arguments:   multiplication

    For this reason, we must take into account that member operator overloads *already have one extra argument*,
    which is the `this` pointer, which is always passed as a first hidden parameter of member functions.
*/

    /*
    A failed attemtpt to add the middle handside to `operator*`.

    ERROR: operator* must have one or two arguments.
    */
    /*
    const OperatorOverload operator* (const OperatorOverload& lhs, const OperatorOverload& mhs, const OperatorOverload& rhs){
        return OperatorOverload(lhs.i * mhs.i * rhs.i);
    }
    */

/*
operator*

    operator* can be two things:

    - multiplication `a * b` if it has  two arguments   (or one    in a member method)
    - dereference `*ptr` if it has      one argument    (or none   in a member method)

    It is only differenced by the number of arguments.
*/

    /*
    This exists because it is the dereference operator.

    This is implemented on classes which represent pointers, such as `shared_ptr`,
    which is not the case for this class.
    */

        /*
        Dereference operator.

        This should not be implemented for this class since it makes no (usual) sense,
        it is just to illustrate that it is possible.
        */
        int operator* (const OperatorOverload& rhs){
            return rhs.i;
        }

        OperatorOverload operator* (const OperatorOverload& lhs, const OperatorOverload& rhs){
            return OperatorOverload(lhs.i * rhs.i);
        }

/*
operator-

- `-` with one argument:    unary minus
- `-` with two arguments:   subtraction

*/

        /* Can be defined in terms of * if you class implements it. */
        const OperatorOverload operator- (const OperatorOverload& rhs){
            return OperatorOverload(-1) * rhs;
        }

        /* Defined in terms of unary minus and +. */
        const OperatorOverload operator- (const OperatorOverload& lhs, const OperatorOverload& rhs){
            return lhs + (-rhs);
        }

/*
Operator overload and templates

    Operator overload and templates do not play very well together
    because operator overload leads to special function calling syntax,
    which does not go well with the template calling syntax.
*/

    template <class T>
    T operator/(const T& i, const T& j) {return i + j;}

int main() {
    // OperatorOverload overload `+`
    {
        // ==
        assert(OperatorOverload(3) == OperatorOverload(3));

        // <
        assert(OperatorOverload(1) < OperatorOverload(2));

        // =
        {
            OperatorOverload i(1);
            assert(i == OperatorOverload(1));
        }

        // +=
        {
            OperatorOverload i(1);
            i += OperatorOverload(2);
            assert(i == OperatorOverload(3));
        }

        // +
        assert(OperatorOverload(1) + OperatorOverload(2) == OperatorOverload(3));

        // # operator++
        {
            // Prefix
            {
                {
                    OperatorOverload i(1);
                    assert(++i == OperatorOverload(2));
                    assert(i == OperatorOverload(2));
                }

                // The non-const reference return allows to chain ++.
                {
                    OperatorOverload i(1);
                    assert(++(++i) == OperatorOverload(3));
                    assert(i == OperatorOverload(3));

                    // Just like for primitives.
                    {
                        int i = 0;
                        assert(++(++i) == 2);
                        assert(i == 2);
                    }
                }
            }

            // Postfix. TODO
            {
                OperatorOverload i(1);
                assert(i++ == OperatorOverload(1));
                assert(i == OperatorOverload(2));

                // ERROR. Cannot chain postfix, just like for primitives.
                // It must return a new value.
                //(i++)++
            }
        }

        // -
        {
            // Unary
            assert(-OperatorOverload(1) == OperatorOverload(-1));

            // Subtraction
            assert(OperatorOverload(2) - OperatorOverload(1) == OperatorOverload(1));
        }

        // *
        {
            // Dereference
            assert(*(OperatorOverload(1)) == 1);

            // Subtraction
            assert(OperatorOverload(2) - OperatorOverload(1) == OperatorOverload(1));
        }

        // <<
        {
            OperatorOverload i(123);
            std::stringstream os;
            os << i;
            assert(os.str() == "123");
        }

        // typecast overload
        {
            OperatorOverload oo(1);

            // Explicit typecast:
            assert(((bool)oo) == true);
            assert(((int)oo) == 2);
            assert(((float)oo) == 1.5);

            // Implicit typecast:
            assert(oo);

            int i = oo;
            assert(i == 2);

            float f = oo;
            assert(f == 1.5f);
        }
    }

    /*
    Explicit call syntax.

    Does the same as the implicit call syntax, but is uglier.

    May be required when the function is also a template function.
    */
    {
        OperatorOverload i, j;
        i = OperatorOverload(1);
        j = OperatorOverload(2);

        assert(operator+(i, j) == OperatorOverload(3));

        i.operator=(j);
        assert(i == j);
    }

    /*
    operator overload and templates
    */
    {
        // Works because of template ty.
        assert(OperatorOverload(1) / OperatorOverload(2) == OperatorOverload(3));

        // ERROR: Impossible syntax
        //assert(OperatorOverload(1) /<OperatorOverload> OperatorOverload(2) == OperatorOverload(3));

        // If we needed to specify the template parameter to the operator on this case,
        // an explicit `operator/` call would be needed
        assert(operator/<OperatorOverload>(OperatorOverload(1), OperatorOverload(2)) == OperatorOverload(3));
    }
}
