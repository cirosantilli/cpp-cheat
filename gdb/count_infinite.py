#!/usr/bin/env python3

import sys

import pexpect

def find_line(source_path, lineid):
    '''
    Search for the first line that contains a comment line
    that ends in /* lineid-<lineid> */ and return the line number.
    '''
    lineend = '/* lineid-' + lineid + ' */'
    with open(source_path, 'r') as f:
        for i, line in enumerate(f):
            if line.rstrip().endswith(lineend):
                return i
    return -1

prompt = '\(gdb\) '
child = pexpect.spawn('gdb', ['-q', '-nh', '-ex', 'set confirm off', 'count_infinite.out'], encoding='utf-8')
child.setecho(False)

child.expect(prompt)
child.sendline('break {}'.format(find_line('count_infinite.c', 'inc')))

child.expect(prompt)
child.sendline('run')

child.expect(prompt)
child.sendline('printf "%d\\n", i')

child.expect(prompt)
assert child.before.rstrip() == '0'
child.sendline('continue')

child.expect(prompt)
child.sendline('printf "%d\\n", i')

child.expect(prompt)
assert child.before.rstrip() == '1'
child.sendcontrol('d')

child.close()
