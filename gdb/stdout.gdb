start
define stdout
    catch syscall write
    commands
        printf "rsi = %s\n", $rsi
        bt
        continue
    end
    condition $bpnum $rdi == 1 && strstr((char *)$rsi, "$arg0") != NULL
end
stdout qwer
i b
continue
