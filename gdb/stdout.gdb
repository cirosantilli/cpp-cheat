start
define stdout
    catch syscall write
    commands
        x/s $rsi
        backtrace
        continue
    end
    # Stop if it contains arg0.
    condition 2 $rdi == 1 && strstr((char *)$rsi, "$arg0") != NULL
end
stdout b
continue
