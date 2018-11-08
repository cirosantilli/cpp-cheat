import os
import sys

import pexpect

class GdbTestcase:
    def __init__(self, filename, source_ext='.c', debug=False):
        noext, ext = os.path.splitext(filename)
        noext_bare = noext[:-len('_test')]
        self.source_path = noext_bare + source_ext
        self.executable_path = noext_bare + '.out'
        self.prompt = '\(gdb\) '
        self.child = pexpect.spawn(
            'gdb',
            ['-q', '-nh', '-ex', 'set confirm off', self.executable_path],
            encoding='utf-8'
        )
        if debug:
            self.child.logfile = sys.stdout
        self.child.setecho(False)
        self.child.expect(self.prompt)
        self.sendline('start')

    def before(self):
        return self.child.before.rstrip()

    def continue_to(self, lineid):
        line_number = self.find_line(lineid)
        self.sendline('tbreak {}'.format(line_number))
        self.sendline('continue')

    def destroy(self):
        self.child.sendcontrol('d')
        self.child.close()

    def get_int(self, int_id):
        self.sendline('printf "%d\\n", {}'.format(int_id))
        return int(self.before())

    def find_line(self, lineid):
        '''
        Search for the first line that contains a comment line
        that ends in /* lineid-<lineid> */ and return the line number.
        '''
        lineend = '/* lineid-' + lineid + ' */'
        with open(self.source_path, 'r') as f:
            for i, line in enumerate(f):
                if line.rstrip().endswith(lineend):
                    return i + 1
        return -1

    def sendline(self, line):
        self.child.sendline(line)
        self.child.expect(self.prompt)
