# Step through every line of the program.
#
# Deficiencies:
#
# -  The problem with this is that it generates a trace too large,
#    specially as it enters every glibc call.
#
#    We should develop a way to only enter functions of the program being studied.
#
# -  Big boring loops are a problem.
#
# -  The while 1 blows at the end of the program.
#
# Python scripting is likely the only way to get around those problems.s

break main
run
while 1
  step
end
