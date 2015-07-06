/*
Scopes.
*/

int g = -1;
int i = 0;
float f = 0.5;

enum Enum {
    E0 = 0,
    E1 = 1
};

struct Struct {
    int i;
    int j;
};

int main(int argc, char **argv) {
    int i;
    float f;
    struct Struct s;
    enum Enum e;
    i = 1;
    f = 1.5;
    s.i = 1;
    s.j = 2;
    e = E0;
    {
        int i;
        float f;
        struct Struct s;
        i = 2;
        f = 2.5;
        s.i = 2;
        s.j = 3;
        e = E1;
    }
    return 0;
}
