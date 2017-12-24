/*
Simple class for tests on constructor destructor order.

This class has no members which are objects and no base classes.

TODO break this class up.
*/
class NoBaseNoMember {
    public:

        int i;

        /// Default constructor
        NoBaseNoMember() : i(0) {
            callStack.push_back("NoBaseNoMember::NoBaseNoMember()");
        }

        /// Copy constructor
        NoBaseNoMember(const NoBaseNoMember& other) : i(other.i) {
            callStack.push_back("NoBaseNoMember::NoBaseNoMember(NoBaseNoMember)");
        }

        NoBaseNoMember(int i) : i(i) {callStack.push_back("NoBaseNoMember::NoBaseNoMember(int)");}

        /// Assign
        NoBaseNoMember& operator= (const NoBaseNoMember& rhs) {
            this->i = rhs.i;
            callStack.push_back("NoBaseNoMember::operator=");
            return *this;
        }

        /// Destructor
        ~NoBaseNoMember() { callStack.push_back("NoBaseNoMember::~NoBaseNoMember()"); }

        void method() { callStack.push_back("NoBaseNoMember::method()"); }

        static NoBaseNoMember create() {
            return NoBaseNoMember();
        }

        static NoBaseNoMember createNrvo() {
            NoBaseNoMember c;
            return c;
        }

        /// It would be hard or impossible to do RVO for this function.
        static NoBaseNoMember createNrvoHard(bool b = false) {
            //2 int constructors
            NoBaseNoMember cf = NoBaseNoMember(0);
            NoBaseNoMember ct = NoBaseNoMember(1);
            return b ? ct : cf;
            //2 int destructors
        }

        static void temporaryReference(NoBaseNoMember& temp) {
            temp.i = 0;
        }

        static void temporaryReferenceConst(const NoBaseNoMember& temp) {}
};

class NoBaseNoMember0 {
    public:
        NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::NoBaseNoMember0()");}
        ~NoBaseNoMember0(){callStack.push_back("NoBaseNoMember0::~NoBaseNoMember0()");}
        void method(){callStack.push_back("NoBaseNoMember0::method()");}
};

class NoBaseNoMember1 {
    public:
        NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::NoBaseNoMember1()");}
        ~NoBaseNoMember1(){callStack.push_back("NoBaseNoMember1::~NoBaseNoMember1()");}
        void method(){callStack.push_back("NoBaseNoMember1::method()");}
};
