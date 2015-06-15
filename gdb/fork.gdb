break main

set follow-fork-mode parent
run
while 1
  step
end

# TODO would need to either:

# - ignore the error of doing a `step` after it finishes running
# - check if the program is running on the while

# for the following code to run.

#set follow-fork-mode child
#run
#while 1
#next
#end
