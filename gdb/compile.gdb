start
next
compile code int j = 1; i = j; asm("nop"); asm volatile ("mov $0x123, %rax");
p "HERE"
p $rcx
p "HERE"
continue
