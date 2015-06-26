/*
# Sequence point

    - http://stackoverflow.com/questions/10782863/what-is-the-correct-answer-for-cout-c-c
    - http://stackoverflow.com/questions/3575350/sequence-points-in-c
    - http://stackoverflow.com/questions/4176328/undefined-behavior-and-sequence-points

    Some language features force side effects of an expression evaluation
    to happen before continuing while others don't.

    A typical example of a side effect is the increment of `i` on `i++`,
    being the main effect the returning of the value of `i` before the increment.

    Sequence points are the operations which enforce order of evaulation.

    A full list is given here: <http://en.wikipedia.org/wiki/Sequence_point>

    Since operators such as `*` or `+` are not on the sequence point list,
    it is undetermined behaviour in `f1() * f2()` if `f1` or `f2` is evaluated first.
    The same goes for `-`, `/` and the evaulation of arguments of a function.

    Other operators however do create sequence points, for example the comma operator.

    In simple cases, gcc 4.7 is smart enough to notice undefiened behaviour and emmits a warning.
    This warning has been ignored for test purposes by a test only `-Wno-sequence-point` flag.

# Order of evaulation of arguments

    The order of evaluation for expressions that are arguments
    of functions or operators is unspecified behaviour.

    For example, it is unspecified behaviour in
    `f1() * f2()` if `f1` or `f2` is evaluated first,
    which may matter if they have side-effects.

    The same goes for `g(f1(), f2())`.

    Also note that there is a further separation between evaluation (getting the value to pass forward),
    and side effects which this evaulation may have (increasing `i` on an `i++`).
    See sequence point` for that.

    TODO example.
*/

#include "common.h"

int global = 1;

int post_inc_global() {
    global++;
    return global - 1;
}

int main() {
    /*
    Implementation defined.

    `=`does not create sequence points, to it is not possible to know if the side effect of `++`
    will happen before or after the assigment.

    Therefore, it is possible that this gives either:

        post_increment_return = 0;
        i = post_increment_return;
        i++;

    or

        post_increment_return = 0;
        i++;
        i = post_increment_return;
    */
    {
        int i = 0;
        i = i++;
        printf("i = i++ = %d\n", i);
        assert(i == 0 || i == 1);
    }

    /*
    Defined behaviour because the return statement
    guarantees that all side effects have happened.

    Contrast with `i = i++`, which has no return statement.
    */
    {
        global = 0;
        global = post_inc_global();
        assert(global == 0);
    }

    /*
    `+` does not specify a sequence point between its two sides.

    Therefore, the side effect of either `++` (incrementing i) may or may not happen before the other `++` is evaluated.

    This allows for the following outputs:

        0 + 0           (neither side effect happened before the other)
        1 + 0 or 0 + 1  (one side effect happened before the other)
    */
    {
        int i = 0;
        int j = i++ + i++;
        printf("i++ + i++ = %d\n", j);
        assert(j == 0 || j == 1);
    }

    /*
    Implementation defined.

    The return statements are full expressions,
    so they guarantee that either one or the other function call happens first.

    However, it is not possible to know which side of `-` is evaulated first.

    Ouptput depends on evaulation order, giving either:

        0 - 1 = -1

    if the first `post_inc_global()` is evaluated first or

        1 - 0 = 1

    if the second `post_inc_global()` is evaluated first.
    */
    {
        global = 0;
        int j = post_inc_global() - post_inc_global();
        printf("post_inc_global() - post_inc_global() = %d\n", j);
        assert(j == -1 || j == 1);
    }

    /*
    Defined behaviour because of the commutativity of addition and because the return statements guarantees
    that all side effects are done with.

    Constrast with `++global + ++global`, which is unspecified
    because there are no return statements.

    This may give either:

        0 + 1 = 1

    or

        1 + 0 = 1

    so both are the same by coincidence.
    */
    {
        global = 0;
        assert(post_inc_global() + post_inc_global() == 1);
    }

    /*
    Comma operator introduces a sequence point.
    */
    {
        int i = 0;
        assert((i++, i++) == 1);
    }

    /* declarators in declarator sequence instroduce sequence points */
    {
        int i = 0, j = i;
        assert(j == 0);
    }

    /*
    Boolean operators `||` and `&&` introduce a sequence point.
    */
    {
        /*
        The following happens:

        - the first i++ returns 0
        - since this is false, the second side is evaulated
        - since `||` adds a sequence point, the increment side effect must happen
        - i now equals one, and `||` evals true
        */
        {
            int i = 0;
            assert(i++ || i);
        }

        /* same as for `||` */
        {
            int i = 1;
            assert(! (i-- && i));
        }
    }

    return EXIT_SUCCESS;
}
