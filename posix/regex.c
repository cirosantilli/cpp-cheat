/*
   TODO loop over all matches.
http://stackoverflow.com/questions/16417454/why-regexec-in-posix-c-always-return-the-first-match-how-can-it-return-all-mat
*/

#include "common.h"

int main(void) {
    char *src = "0a1 0a2 0a3";
    char err_buf[BUFSIZ];
    const char *pattern = "0.[12]";
    int i;
    int res;
    regex_t preg;
    regmatch_t pmatch[10];

    if ((res = regcomp(&preg, pattern, REG_EXTENDED)) != 0) {
        regerror(res, &preg, err_buf, BUFSIZ);
        printf("regcomp: %s\n", err_buf);
        exit(EXIT_FAILURE);
    }

    res = regexec(&preg, src, 10, pmatch, REG_NOTBOL);
    //~ res = regexec(&preg, src, 10, pmatch, 0);
    //~ res = regexec(&preg, src, 10, pmatch, REG_NOTEOL);
    if (res != REG_NOMATCH) {
        for (i = 0; pmatch[i].rm_so != -1; i++) {
            printf("%ju %ju\n", (uintmax_t)pmatch[i].rm_so, (uintmax_t)pmatch[i].rm_eo);
        }
    }
    regfree(&preg);
    return 0;
}
