#!/usr/bin/env python3

import common

t = common.GdbTestcase(__file__)
t.continue_to('inc')
assert t.get_int('i') == 0
t.continue_to('inc')
assert t.get_int('i') == 1
t.destroy()
