trace f
actions
    collect $args
end
tstart
run
tfind start
while ($trace_frame != -1)
    tdump
    tfind
end
