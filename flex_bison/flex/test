#!/usr/bin/env python

"""
does many test cases

run as:
        
    test.py executable
"""

import subprocess
import sys
import unittest 

class ProgramInput:

    def __init__(self, stdin, args = [] ):
        self.stdin  = stdin
        self.args   = args

    def __eq__(self, other):
        if type(other) is type(self):
            return self.__dict__ == other.__dict__
        return False

    def __repr__(self):
        return \
            'stdin:\n' + self.stdin + '\n\n' \
            'args: ' + self.args.__repr__() + '\n'

class ProgramOutput:

    def __init__(self, stdout, stderr = '', exit_status = 0):
        self.stdout         = stdout
        self.stderr         = stderr
        self.exit_status    = exit_status

    def __eq__(self, other):
        if type(other) is type(self):
            return self.__dict__ == other.__dict__
        return False

    def __repr__(self):
        return \
            'stdout:\n' + self.stdout + '\n\n' \
            'stderr:\n' + self.stderr + '\n\n' \
            'exit_status: ' + str(self.exit_status) + '\n'

class Test(unittest.TestCase):

    def test(self):

        inouts = [

            #string literals

                #multiple on line
                ( ProgramInput( '"a" "b"' ),    ProgramOutput( 'STRING: "a"\nSTRING: "b"\n' ) ),

                #empty
                ( ProgramInput( r'""' ),        ProgramOutput( 'STRING: ""\n'               ) ),

                #escape
                ( ProgramInput( r'"\""' ),      ProgramOutput( r'STRING: "\""' '\n'         ) ),

                ( ProgramInput( r'"\"' ),       ProgramOutput( '', 'error\n', 1             ) ),

            #multiline comments

                #empty
                ( ProgramInput( '/**/' ),           ProgramOutput( 'MCOM: /**/\n' ) ),

                #ends in '*'
                ( ProgramInput( '/***/' ),          ProgramOutput( 'MCOM: /***/\n' ) ),

                #contains **
                ( ProgramInput( '/****/' ),         ProgramOutput( 'MCOM: /****/\n' ) ),
                ( ProgramInput( '/*** */' ),        ProgramOutput( 'MCOM: /*** */\n' ) ),
                ( ProgramInput( '/** **/' ),        ProgramOutput( 'MCOM: /** **/\n' ) ),

                #multiple
                ( ProgramInput( '/*a*/ /*b*/' ),    ProgramOutput( 'MCOM: /*a*/\nMCOM: /*b*/\n' ) ),

                #multiline
                ( ProgramInput( '/*\na\nb*/' ),     ProgramOutput( 'MCOM: /*\na\nb*/\n' ) ),
        ]

        for inout in inouts:

            inp, out_expect = inout
            command = [ program_path ]
            command.extend( inp.args )

            process = subprocess.Popen(
                command,
                shell  = False,
                stdin  = subprocess.PIPE,
                stdout = subprocess.PIPE,
                stderr = subprocess.PIPE
            )
            stdout, stderr = process.communicate( inp.stdin )
            exit_status = process.wait()
            out = ProgramOutput( stdout, stderr, exit_status )

            #print inp
            #print out
            #print out_expect

            self.assertEqual( out, out_expect )

if __name__ == '__main__':

    program_path = sys.argv[1]
    unittest.main( argv = [sys.argv[0]] )
