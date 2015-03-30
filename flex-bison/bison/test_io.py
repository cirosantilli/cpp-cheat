inouts = [
    ["print",               "print 1;\n",                                   "1\n"],
    ["print variable",      "a = 1; print a;\n",                            "1\n"],
    ["variables",           "a = 1; b = a; print b;",                       "1\n"],
    ["variables",           "a = 1 + 1; print a;",                          "2\n"],
    ["if",                  "if(1); print 1;",                              "1\n"],
    ["while",               "i = 0; while (i < 3) {print i; i = i + 1;}",   "0\n1\n2\n"],
]
