// http://stackoverflow.com/questions/5685471/error-jump-to-case-label

int main() {
    goto after;
#if 0
    // error: jump to label ‘after’
    // note: crosses initialization of ‘int i’
    int i = 0;
#endif
after:
    ;
}
