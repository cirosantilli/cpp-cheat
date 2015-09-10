inouts = [
#string literals
    ["multiple on line",   '"a" "b"',                'STRING: "a"\nSTRING: "b"\n'                 ],
    ["empty",             r'""',                     'STRING: ""\n'                               ],
    ["escape",            r'"\""',                   'STRING: "\\""\n'                            ],
    ["escape error",      r'"\"',                    '',                          [], 'error\n', 1],
#multiline comments
    ["empty",          '/**/',                   'MCOM: /**/\n'                               ],
    ["ends in '*'",    '/***/',                  'MCOM: /***/\n'                              ],
    ["contains **",    '/****/',                 'MCOM: /****/\n'                             ],
    ["contains ** ",   '/*** */',                'MCOM: /*** */\n'                            ],
    ["contains * *",   '/** **/',                'MCOM: /** **/\n'                            ],
    ["multiple",       '/*a*/ /*b*/',            'MCOM: /*a*/\nMCOM: /*b*/\n'                 ],
    ["multiline",      '/*\na\nb*/',             'MCOM: /*\na\nb*/\n'                         ],
]
