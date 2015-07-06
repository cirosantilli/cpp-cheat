int i = 0;
int j = 0;
int k = 0;

int main(int argc, char **argv) {
    int i = 1;
    int j = 1;
    {
        int i = 2;
        i = 3;
        i = 4;
    }
    return 0;
}
