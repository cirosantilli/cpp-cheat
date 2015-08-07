	.file	"string.c"
	.text
.Ltext0:
	.globl	s
	.section	.rodata
.LC0:
	.string	"ab\ncd\n"
	.data
	.align 8
	.type	s, @object
	.size	s, 8
s:
	.quad	.LC0
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.file 1 "string.c"
	.loc 1 9 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 10 0
	movq	s(%rip), %rax
	movq	%rax, %rdi
	call	puts
	.loc 1 11 0
	movl	$0, %eax
	.loc 1 12 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xaa
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF590
	.byte	0x1
	.long	.LASF591
	.long	.LASF592
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.long	.Ldebug_macro0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF581
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF582
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF583
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF584
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF585
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF586
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF587
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF588
	.uleb128 0x4
	.byte	0x8
	.long	0x76
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF589
	.uleb128 0x5
	.long	.LASF593
	.byte	0x1
	.byte	0x9
	.long	0x5b
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.string	"s"
	.byte	0x1
	.byte	0x7
	.long	0x70
	.uleb128 0x9
	.byte	0x3
	.quad	s
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.uleb128 0x2119
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_macro,"",@progbits
.Ldebug_macro0:
	.value	0x4
	.byte	0x2
	.long	.Ldebug_line0
	.byte	0x7
	.long	.Ldebug_macro1
	.byte	0x3
	.uleb128 0
	.uleb128 0x1
	.file 2 "/usr/include/stdc-predef.h"
	.byte	0x3
	.uleb128 0
	.uleb128 0x2
	.byte	0x7
	.long	.Ldebug_macro2
	.byte	0x4
	.file 3 "/usr/include/stdio.h"
	.byte	0x3
	.uleb128 0x5
	.uleb128 0x3
	.byte	0x5
	.uleb128 0x1a
	.long	.LASF239
	.file 4 "/usr/include/features.h"
	.byte	0x3
	.uleb128 0x1b
	.uleb128 0x4
	.byte	0x7
	.long	.Ldebug_macro3
	.file 5 "/usr/include/x86_64-linux-gnu/sys/cdefs.h"
	.byte	0x3
	.uleb128 0x176
	.uleb128 0x5
	.byte	0x7
	.long	.Ldebug_macro4
	.file 6 "/usr/include/x86_64-linux-gnu/bits/wordsize.h"
	.byte	0x3
	.uleb128 0x181
	.uleb128 0x6
	.byte	0x7
	.long	.Ldebug_macro5
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro6
	.byte	0x4
	.file 7 "/usr/include/x86_64-linux-gnu/gnu/stubs.h"
	.byte	0x3
	.uleb128 0x18e
	.uleb128 0x7
	.file 8 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h"
	.byte	0x3
	.uleb128 0xa
	.uleb128 0x8
	.byte	0x7
	.long	.Ldebug_macro7
	.byte	0x4
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro8
	.file 9 "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stddef.h"
	.byte	0x3
	.uleb128 0x21
	.uleb128 0x9
	.byte	0x7
	.long	.Ldebug_macro9
	.byte	0x4
	.file 10 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.byte	0x3
	.uleb128 0x23
	.uleb128 0xa
	.byte	0x5
	.uleb128 0x18
	.long	.LASF401
	.byte	0x3
	.uleb128 0x1b
	.uleb128 0x6
	.byte	0x7
	.long	.Ldebug_macro5
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro10
	.file 11 "/usr/include/x86_64-linux-gnu/bits/typesizes.h"
	.byte	0x3
	.uleb128 0x79
	.uleb128 0xb
	.byte	0x7
	.long	.Ldebug_macro11
	.byte	0x4
	.byte	0x6
	.uleb128 0xc0
	.long	.LASF454
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro12
	.file 12 "/usr/include/libio.h"
	.byte	0x3
	.uleb128 0x4a
	.uleb128 0xc
	.byte	0x5
	.uleb128 0x1d
	.long	.LASF462
	.file 13 "/usr/include/_G_config.h"
	.byte	0x3
	.uleb128 0x1f
	.uleb128 0xd
	.byte	0x7
	.long	.Ldebug_macro13
	.byte	0x3
	.uleb128 0xf
	.uleb128 0x9
	.byte	0x7
	.long	.Ldebug_macro14
	.byte	0x4
	.byte	0x5
	.uleb128 0x10
	.long	.LASF464
	.file 14 "/usr/include/wchar.h"
	.byte	0x3
	.uleb128 0x14
	.uleb128 0xe
	.byte	0x7
	.long	.Ldebug_macro15
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro16
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro17
	.file 15 "/usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h"
	.byte	0x3
	.uleb128 0x31
	.uleb128 0xf
	.byte	0x7
	.long	.Ldebug_macro18
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro19
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro20
	.file 16 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h"
	.byte	0x3
	.uleb128 0xa4
	.uleb128 0x10
	.byte	0x7
	.long	.Ldebug_macro21
	.byte	0x4
	.byte	0x7
	.long	.Ldebug_macro22
	.file 17 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.byte	0x3
	.uleb128 0x355
	.uleb128 0x11
	.byte	0x4
	.byte	0x4
	.byte	0x4
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.0.7766608fd2b8de38f63af1762c2bb425,comdat
.Ldebug_macro1:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0
	.long	.LASF0
	.byte	0x5
	.uleb128 0
	.long	.LASF1
	.byte	0x5
	.uleb128 0
	.long	.LASF2
	.byte	0x5
	.uleb128 0
	.long	.LASF3
	.byte	0x5
	.uleb128 0
	.long	.LASF4
	.byte	0x5
	.uleb128 0
	.long	.LASF5
	.byte	0x5
	.uleb128 0
	.long	.LASF6
	.byte	0x5
	.uleb128 0
	.long	.LASF7
	.byte	0x5
	.uleb128 0
	.long	.LASF8
	.byte	0x5
	.uleb128 0
	.long	.LASF9
	.byte	0x5
	.uleb128 0
	.long	.LASF10
	.byte	0x5
	.uleb128 0
	.long	.LASF11
	.byte	0x5
	.uleb128 0
	.long	.LASF12
	.byte	0x5
	.uleb128 0
	.long	.LASF13
	.byte	0x5
	.uleb128 0
	.long	.LASF14
	.byte	0x5
	.uleb128 0
	.long	.LASF15
	.byte	0x5
	.uleb128 0
	.long	.LASF16
	.byte	0x5
	.uleb128 0
	.long	.LASF17
	.byte	0x5
	.uleb128 0
	.long	.LASF18
	.byte	0x5
	.uleb128 0
	.long	.LASF19
	.byte	0x5
	.uleb128 0
	.long	.LASF20
	.byte	0x5
	.uleb128 0
	.long	.LASF21
	.byte	0x5
	.uleb128 0
	.long	.LASF22
	.byte	0x5
	.uleb128 0
	.long	.LASF23
	.byte	0x5
	.uleb128 0
	.long	.LASF24
	.byte	0x5
	.uleb128 0
	.long	.LASF25
	.byte	0x5
	.uleb128 0
	.long	.LASF26
	.byte	0x5
	.uleb128 0
	.long	.LASF27
	.byte	0x5
	.uleb128 0
	.long	.LASF28
	.byte	0x5
	.uleb128 0
	.long	.LASF29
	.byte	0x5
	.uleb128 0
	.long	.LASF30
	.byte	0x5
	.uleb128 0
	.long	.LASF31
	.byte	0x5
	.uleb128 0
	.long	.LASF32
	.byte	0x5
	.uleb128 0
	.long	.LASF33
	.byte	0x5
	.uleb128 0
	.long	.LASF34
	.byte	0x5
	.uleb128 0
	.long	.LASF35
	.byte	0x5
	.uleb128 0
	.long	.LASF36
	.byte	0x5
	.uleb128 0
	.long	.LASF37
	.byte	0x5
	.uleb128 0
	.long	.LASF38
	.byte	0x5
	.uleb128 0
	.long	.LASF39
	.byte	0x5
	.uleb128 0
	.long	.LASF40
	.byte	0x5
	.uleb128 0
	.long	.LASF41
	.byte	0x5
	.uleb128 0
	.long	.LASF42
	.byte	0x5
	.uleb128 0
	.long	.LASF43
	.byte	0x5
	.uleb128 0
	.long	.LASF44
	.byte	0x5
	.uleb128 0
	.long	.LASF45
	.byte	0x5
	.uleb128 0
	.long	.LASF46
	.byte	0x5
	.uleb128 0
	.long	.LASF47
	.byte	0x5
	.uleb128 0
	.long	.LASF48
	.byte	0x5
	.uleb128 0
	.long	.LASF49
	.byte	0x5
	.uleb128 0
	.long	.LASF50
	.byte	0x5
	.uleb128 0
	.long	.LASF51
	.byte	0x5
	.uleb128 0
	.long	.LASF52
	.byte	0x5
	.uleb128 0
	.long	.LASF53
	.byte	0x5
	.uleb128 0
	.long	.LASF54
	.byte	0x5
	.uleb128 0
	.long	.LASF55
	.byte	0x5
	.uleb128 0
	.long	.LASF56
	.byte	0x5
	.uleb128 0
	.long	.LASF57
	.byte	0x5
	.uleb128 0
	.long	.LASF58
	.byte	0x5
	.uleb128 0
	.long	.LASF59
	.byte	0x5
	.uleb128 0
	.long	.LASF60
	.byte	0x5
	.uleb128 0
	.long	.LASF61
	.byte	0x5
	.uleb128 0
	.long	.LASF62
	.byte	0x5
	.uleb128 0
	.long	.LASF63
	.byte	0x5
	.uleb128 0
	.long	.LASF64
	.byte	0x5
	.uleb128 0
	.long	.LASF65
	.byte	0x5
	.uleb128 0
	.long	.LASF66
	.byte	0x5
	.uleb128 0
	.long	.LASF67
	.byte	0x5
	.uleb128 0
	.long	.LASF68
	.byte	0x5
	.uleb128 0
	.long	.LASF69
	.byte	0x5
	.uleb128 0
	.long	.LASF70
	.byte	0x5
	.uleb128 0
	.long	.LASF71
	.byte	0x5
	.uleb128 0
	.long	.LASF72
	.byte	0x5
	.uleb128 0
	.long	.LASF73
	.byte	0x5
	.uleb128 0
	.long	.LASF74
	.byte	0x5
	.uleb128 0
	.long	.LASF75
	.byte	0x5
	.uleb128 0
	.long	.LASF76
	.byte	0x5
	.uleb128 0
	.long	.LASF77
	.byte	0x5
	.uleb128 0
	.long	.LASF78
	.byte	0x5
	.uleb128 0
	.long	.LASF79
	.byte	0x5
	.uleb128 0
	.long	.LASF80
	.byte	0x5
	.uleb128 0
	.long	.LASF81
	.byte	0x5
	.uleb128 0
	.long	.LASF82
	.byte	0x5
	.uleb128 0
	.long	.LASF83
	.byte	0x5
	.uleb128 0
	.long	.LASF84
	.byte	0x5
	.uleb128 0
	.long	.LASF85
	.byte	0x5
	.uleb128 0
	.long	.LASF86
	.byte	0x5
	.uleb128 0
	.long	.LASF87
	.byte	0x5
	.uleb128 0
	.long	.LASF88
	.byte	0x5
	.uleb128 0
	.long	.LASF89
	.byte	0x5
	.uleb128 0
	.long	.LASF90
	.byte	0x5
	.uleb128 0
	.long	.LASF91
	.byte	0x5
	.uleb128 0
	.long	.LASF92
	.byte	0x5
	.uleb128 0
	.long	.LASF93
	.byte	0x5
	.uleb128 0
	.long	.LASF94
	.byte	0x5
	.uleb128 0
	.long	.LASF95
	.byte	0x5
	.uleb128 0
	.long	.LASF96
	.byte	0x5
	.uleb128 0
	.long	.LASF97
	.byte	0x5
	.uleb128 0
	.long	.LASF98
	.byte	0x5
	.uleb128 0
	.long	.LASF99
	.byte	0x5
	.uleb128 0
	.long	.LASF100
	.byte	0x5
	.uleb128 0
	.long	.LASF101
	.byte	0x5
	.uleb128 0
	.long	.LASF102
	.byte	0x5
	.uleb128 0
	.long	.LASF103
	.byte	0x5
	.uleb128 0
	.long	.LASF104
	.byte	0x5
	.uleb128 0
	.long	.LASF105
	.byte	0x5
	.uleb128 0
	.long	.LASF106
	.byte	0x5
	.uleb128 0
	.long	.LASF107
	.byte	0x5
	.uleb128 0
	.long	.LASF108
	.byte	0x5
	.uleb128 0
	.long	.LASF109
	.byte	0x5
	.uleb128 0
	.long	.LASF110
	.byte	0x5
	.uleb128 0
	.long	.LASF111
	.byte	0x5
	.uleb128 0
	.long	.LASF112
	.byte	0x5
	.uleb128 0
	.long	.LASF113
	.byte	0x5
	.uleb128 0
	.long	.LASF114
	.byte	0x5
	.uleb128 0
	.long	.LASF115
	.byte	0x5
	.uleb128 0
	.long	.LASF116
	.byte	0x5
	.uleb128 0
	.long	.LASF117
	.byte	0x5
	.uleb128 0
	.long	.LASF118
	.byte	0x5
	.uleb128 0
	.long	.LASF119
	.byte	0x5
	.uleb128 0
	.long	.LASF120
	.byte	0x5
	.uleb128 0
	.long	.LASF121
	.byte	0x5
	.uleb128 0
	.long	.LASF122
	.byte	0x5
	.uleb128 0
	.long	.LASF123
	.byte	0x5
	.uleb128 0
	.long	.LASF124
	.byte	0x5
	.uleb128 0
	.long	.LASF125
	.byte	0x5
	.uleb128 0
	.long	.LASF126
	.byte	0x5
	.uleb128 0
	.long	.LASF127
	.byte	0x5
	.uleb128 0
	.long	.LASF128
	.byte	0x5
	.uleb128 0
	.long	.LASF129
	.byte	0x5
	.uleb128 0
	.long	.LASF130
	.byte	0x5
	.uleb128 0
	.long	.LASF131
	.byte	0x5
	.uleb128 0
	.long	.LASF132
	.byte	0x5
	.uleb128 0
	.long	.LASF133
	.byte	0x5
	.uleb128 0
	.long	.LASF134
	.byte	0x5
	.uleb128 0
	.long	.LASF135
	.byte	0x5
	.uleb128 0
	.long	.LASF136
	.byte	0x5
	.uleb128 0
	.long	.LASF137
	.byte	0x5
	.uleb128 0
	.long	.LASF138
	.byte	0x5
	.uleb128 0
	.long	.LASF139
	.byte	0x5
	.uleb128 0
	.long	.LASF140
	.byte	0x5
	.uleb128 0
	.long	.LASF141
	.byte	0x5
	.uleb128 0
	.long	.LASF142
	.byte	0x5
	.uleb128 0
	.long	.LASF143
	.byte	0x5
	.uleb128 0
	.long	.LASF144
	.byte	0x5
	.uleb128 0
	.long	.LASF145
	.byte	0x5
	.uleb128 0
	.long	.LASF146
	.byte	0x5
	.uleb128 0
	.long	.LASF147
	.byte	0x5
	.uleb128 0
	.long	.LASF148
	.byte	0x5
	.uleb128 0
	.long	.LASF149
	.byte	0x5
	.uleb128 0
	.long	.LASF150
	.byte	0x5
	.uleb128 0
	.long	.LASF151
	.byte	0x5
	.uleb128 0
	.long	.LASF152
	.byte	0x5
	.uleb128 0
	.long	.LASF153
	.byte	0x5
	.uleb128 0
	.long	.LASF154
	.byte	0x5
	.uleb128 0
	.long	.LASF155
	.byte	0x5
	.uleb128 0
	.long	.LASF156
	.byte	0x5
	.uleb128 0
	.long	.LASF157
	.byte	0x5
	.uleb128 0
	.long	.LASF158
	.byte	0x5
	.uleb128 0
	.long	.LASF159
	.byte	0x5
	.uleb128 0
	.long	.LASF160
	.byte	0x5
	.uleb128 0
	.long	.LASF161
	.byte	0x5
	.uleb128 0
	.long	.LASF162
	.byte	0x5
	.uleb128 0
	.long	.LASF163
	.byte	0x5
	.uleb128 0
	.long	.LASF164
	.byte	0x5
	.uleb128 0
	.long	.LASF165
	.byte	0x5
	.uleb128 0
	.long	.LASF166
	.byte	0x5
	.uleb128 0
	.long	.LASF167
	.byte	0x5
	.uleb128 0
	.long	.LASF168
	.byte	0x5
	.uleb128 0
	.long	.LASF169
	.byte	0x5
	.uleb128 0
	.long	.LASF170
	.byte	0x5
	.uleb128 0
	.long	.LASF171
	.byte	0x5
	.uleb128 0
	.long	.LASF172
	.byte	0x5
	.uleb128 0
	.long	.LASF173
	.byte	0x5
	.uleb128 0
	.long	.LASF174
	.byte	0x5
	.uleb128 0
	.long	.LASF175
	.byte	0x5
	.uleb128 0
	.long	.LASF176
	.byte	0x5
	.uleb128 0
	.long	.LASF177
	.byte	0x5
	.uleb128 0
	.long	.LASF178
	.byte	0x5
	.uleb128 0
	.long	.LASF179
	.byte	0x5
	.uleb128 0
	.long	.LASF180
	.byte	0x5
	.uleb128 0
	.long	.LASF181
	.byte	0x5
	.uleb128 0
	.long	.LASF182
	.byte	0x5
	.uleb128 0
	.long	.LASF183
	.byte	0x5
	.uleb128 0
	.long	.LASF184
	.byte	0x5
	.uleb128 0
	.long	.LASF185
	.byte	0x5
	.uleb128 0
	.long	.LASF186
	.byte	0x5
	.uleb128 0
	.long	.LASF187
	.byte	0x5
	.uleb128 0
	.long	.LASF188
	.byte	0x5
	.uleb128 0
	.long	.LASF189
	.byte	0x5
	.uleb128 0
	.long	.LASF190
	.byte	0x5
	.uleb128 0
	.long	.LASF191
	.byte	0x5
	.uleb128 0
	.long	.LASF192
	.byte	0x5
	.uleb128 0
	.long	.LASF193
	.byte	0x5
	.uleb128 0
	.long	.LASF194
	.byte	0x5
	.uleb128 0
	.long	.LASF195
	.byte	0x5
	.uleb128 0
	.long	.LASF196
	.byte	0x5
	.uleb128 0
	.long	.LASF197
	.byte	0x5
	.uleb128 0
	.long	.LASF198
	.byte	0x5
	.uleb128 0
	.long	.LASF199
	.byte	0x5
	.uleb128 0
	.long	.LASF200
	.byte	0x5
	.uleb128 0
	.long	.LASF201
	.byte	0x5
	.uleb128 0
	.long	.LASF202
	.byte	0x5
	.uleb128 0
	.long	.LASF203
	.byte	0x5
	.uleb128 0
	.long	.LASF204
	.byte	0x5
	.uleb128 0
	.long	.LASF205
	.byte	0x5
	.uleb128 0
	.long	.LASF206
	.byte	0x5
	.uleb128 0
	.long	.LASF207
	.byte	0x5
	.uleb128 0
	.long	.LASF208
	.byte	0x5
	.uleb128 0
	.long	.LASF209
	.byte	0x5
	.uleb128 0
	.long	.LASF210
	.byte	0x5
	.uleb128 0
	.long	.LASF211
	.byte	0x5
	.uleb128 0
	.long	.LASF212
	.byte	0x5
	.uleb128 0
	.long	.LASF213
	.byte	0x5
	.uleb128 0
	.long	.LASF214
	.byte	0x5
	.uleb128 0
	.long	.LASF215
	.byte	0x5
	.uleb128 0
	.long	.LASF216
	.byte	0x5
	.uleb128 0
	.long	.LASF217
	.byte	0x5
	.uleb128 0
	.long	.LASF218
	.byte	0x5
	.uleb128 0
	.long	.LASF219
	.byte	0x5
	.uleb128 0
	.long	.LASF220
	.byte	0x5
	.uleb128 0
	.long	.LASF221
	.byte	0x5
	.uleb128 0
	.long	.LASF222
	.byte	0x5
	.uleb128 0
	.long	.LASF223
	.byte	0x5
	.uleb128 0
	.long	.LASF224
	.byte	0x5
	.uleb128 0
	.long	.LASF225
	.byte	0x5
	.uleb128 0
	.long	.LASF226
	.byte	0x5
	.uleb128 0
	.long	.LASF227
	.byte	0x5
	.uleb128 0
	.long	.LASF228
	.byte	0x5
	.uleb128 0
	.long	.LASF229
	.byte	0x5
	.uleb128 0
	.long	.LASF230
	.byte	0x5
	.uleb128 0
	.long	.LASF231
	.byte	0x5
	.uleb128 0
	.long	.LASF232
	.byte	0x5
	.uleb128 0
	.long	.LASF233
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdcpredef.h.19.13d357f53e03e35e37f3aa674f978c59,comdat
.Ldebug_macro2:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF234
	.byte	0x5
	.uleb128 0x29
	.long	.LASF235
	.byte	0x5
	.uleb128 0x31
	.long	.LASF236
	.byte	0x5
	.uleb128 0x36
	.long	.LASF237
	.byte	0x5
	.uleb128 0x39
	.long	.LASF238
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.features.h.19.6a64ea47d1cc44cfc57d4e550ef9c824,comdat
.Ldebug_macro3:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF240
	.byte	0x6
	.uleb128 0x65
	.long	.LASF241
	.byte	0x6
	.uleb128 0x66
	.long	.LASF242
	.byte	0x6
	.uleb128 0x67
	.long	.LASF243
	.byte	0x6
	.uleb128 0x68
	.long	.LASF244
	.byte	0x6
	.uleb128 0x69
	.long	.LASF245
	.byte	0x6
	.uleb128 0x6a
	.long	.LASF246
	.byte	0x6
	.uleb128 0x6b
	.long	.LASF247
	.byte	0x6
	.uleb128 0x6c
	.long	.LASF248
	.byte	0x6
	.uleb128 0x6d
	.long	.LASF249
	.byte	0x6
	.uleb128 0x6e
	.long	.LASF250
	.byte	0x6
	.uleb128 0x6f
	.long	.LASF251
	.byte	0x6
	.uleb128 0x70
	.long	.LASF252
	.byte	0x6
	.uleb128 0x71
	.long	.LASF253
	.byte	0x6
	.uleb128 0x72
	.long	.LASF254
	.byte	0x6
	.uleb128 0x73
	.long	.LASF255
	.byte	0x6
	.uleb128 0x74
	.long	.LASF256
	.byte	0x6
	.uleb128 0x75
	.long	.LASF257
	.byte	0x6
	.uleb128 0x76
	.long	.LASF258
	.byte	0x6
	.uleb128 0x77
	.long	.LASF259
	.byte	0x6
	.uleb128 0x78
	.long	.LASF260
	.byte	0x6
	.uleb128 0x79
	.long	.LASF261
	.byte	0x6
	.uleb128 0x7a
	.long	.LASF262
	.byte	0x6
	.uleb128 0x7b
	.long	.LASF263
	.byte	0x6
	.uleb128 0x7c
	.long	.LASF264
	.byte	0x6
	.uleb128 0x7d
	.long	.LASF265
	.byte	0x6
	.uleb128 0x7e
	.long	.LASF266
	.byte	0x5
	.uleb128 0x83
	.long	.LASF267
	.byte	0x5
	.uleb128 0x8e
	.long	.LASF268
	.byte	0x6
	.uleb128 0xb9
	.long	.LASF269
	.byte	0x5
	.uleb128 0xba
	.long	.LASF270
	.byte	0x6
	.uleb128 0xbb
	.long	.LASF271
	.byte	0x5
	.uleb128 0xbc
	.long	.LASF272
	.byte	0x6
	.uleb128 0xbd
	.long	.LASF273
	.byte	0x5
	.uleb128 0xbe
	.long	.LASF274
	.byte	0x5
	.uleb128 0xe1
	.long	.LASF275
	.byte	0x6
	.uleb128 0xe3
	.long	.LASF276
	.byte	0x5
	.uleb128 0xe4
	.long	.LASF277
	.byte	0x6
	.uleb128 0xe5
	.long	.LASF278
	.byte	0x5
	.uleb128 0xe6
	.long	.LASF279
	.byte	0x5
	.uleb128 0xf8
	.long	.LASF280
	.byte	0x5
	.uleb128 0xfc
	.long	.LASF281
	.byte	0x5
	.uleb128 0x100
	.long	.LASF282
	.byte	0x5
	.uleb128 0x104
	.long	.LASF283
	.byte	0x5
	.uleb128 0x108
	.long	.LASF284
	.byte	0x6
	.uleb128 0x109
	.long	.LASF243
	.byte	0x5
	.uleb128 0x10a
	.long	.LASF285
	.byte	0x6
	.uleb128 0x10b
	.long	.LASF242
	.byte	0x5
	.uleb128 0x10c
	.long	.LASF286
	.byte	0x5
	.uleb128 0x110
	.long	.LASF287
	.byte	0x6
	.uleb128 0x111
	.long	.LASF288
	.byte	0x5
	.uleb128 0x112
	.long	.LASF289
	.byte	0x5
	.uleb128 0x13c
	.long	.LASF290
	.byte	0x5
	.uleb128 0x140
	.long	.LASF291
	.byte	0x5
	.uleb128 0x144
	.long	.LASF292
	.byte	0x5
	.uleb128 0x148
	.long	.LASF293
	.byte	0x5
	.uleb128 0x15b
	.long	.LASF294
	.byte	0x6
	.uleb128 0x168
	.long	.LASF295
	.byte	0x5
	.uleb128 0x169
	.long	.LASF296
	.byte	0x5
	.uleb128 0x16d
	.long	.LASF297
	.byte	0x5
	.uleb128 0x16e
	.long	.LASF298
	.byte	0x5
	.uleb128 0x170
	.long	.LASF299
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.cdefs.h.19.deed8300036fdf53f6654237d4653cad,comdat
.Ldebug_macro4:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x13
	.long	.LASF300
	.byte	0x2
	.uleb128 0x22
	.string	"__P"
	.byte	0x6
	.uleb128 0x23
	.long	.LASF301
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF302
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF303
	.byte	0x5
	.uleb128 0x37
	.long	.LASF304
	.byte	0x5
	.uleb128 0x38
	.long	.LASF305
	.byte	0x5
	.uleb128 0x39
	.long	.LASF306
	.byte	0x5
	.uleb128 0x52
	.long	.LASF307
	.byte	0x5
	.uleb128 0x53
	.long	.LASF308
	.byte	0x5
	.uleb128 0x58
	.long	.LASF309
	.byte	0x5
	.uleb128 0x59
	.long	.LASF310
	.byte	0x5
	.uleb128 0x5c
	.long	.LASF311
	.byte	0x5
	.uleb128 0x5d
	.long	.LASF312
	.byte	0x5
	.uleb128 0x65
	.long	.LASF313
	.byte	0x5
	.uleb128 0x66
	.long	.LASF314
	.byte	0x5
	.uleb128 0x7a
	.long	.LASF315
	.byte	0x5
	.uleb128 0x7b
	.long	.LASF316
	.byte	0x5
	.uleb128 0x7c
	.long	.LASF317
	.byte	0x5
	.uleb128 0x7d
	.long	.LASF318
	.byte	0x5
	.uleb128 0x7e
	.long	.LASF319
	.byte	0x5
	.uleb128 0x7f
	.long	.LASF320
	.byte	0x5
	.uleb128 0x84
	.long	.LASF321
	.byte	0x5
	.uleb128 0x85
	.long	.LASF322
	.byte	0x5
	.uleb128 0x86
	.long	.LASF323
	.byte	0x5
	.uleb128 0x89
	.long	.LASF324
	.byte	0x5
	.uleb128 0x8b
	.long	.LASF325
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF326
	.byte	0x5
	.uleb128 0x97
	.long	.LASF327
	.byte	0x5
	.uleb128 0xb2
	.long	.LASF328
	.byte	0x5
	.uleb128 0xb9
	.long	.LASF329
	.byte	0x5
	.uleb128 0xbb
	.long	.LASF330
	.byte	0x5
	.uleb128 0xbe
	.long	.LASF331
	.byte	0x5
	.uleb128 0xbf
	.long	.LASF332
	.byte	0x5
	.uleb128 0xd4
	.long	.LASF333
	.byte	0x5
	.uleb128 0xdc
	.long	.LASF334
	.byte	0x5
	.uleb128 0xe6
	.long	.LASF335
	.byte	0x5
	.uleb128 0xed
	.long	.LASF336
	.byte	0x5
	.uleb128 0xf6
	.long	.LASF337
	.byte	0x5
	.uleb128 0xf7
	.long	.LASF338
	.byte	0x5
	.uleb128 0xff
	.long	.LASF339
	.byte	0x5
	.uleb128 0x10b
	.long	.LASF340
	.byte	0x5
	.uleb128 0x115
	.long	.LASF341
	.byte	0x5
	.uleb128 0x11e
	.long	.LASF342
	.byte	0x5
	.uleb128 0x126
	.long	.LASF343
	.byte	0x5
	.uleb128 0x12f
	.long	.LASF344
	.byte	0x5
	.uleb128 0x134
	.long	.LASF345
	.byte	0x5
	.uleb128 0x13c
	.long	.LASF346
	.byte	0x5
	.uleb128 0x147
	.long	.LASF347
	.byte	0x5
	.uleb128 0x148
	.long	.LASF348
	.byte	0x5
	.uleb128 0x156
	.long	.LASF349
	.byte	0x5
	.uleb128 0x157
	.long	.LASF350
	.byte	0x5
	.uleb128 0x16b
	.long	.LASF351
	.byte	0x5
	.uleb128 0x17a
	.long	.LASF352
	.byte	0x5
	.uleb128 0x17b
	.long	.LASF353
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.wordsize.h.4.256e8fdbd37801980286acdbc40d0280,comdat
.Ldebug_macro5:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x4
	.long	.LASF354
	.byte	0x5
	.uleb128 0xa
	.long	.LASF355
	.byte	0x5
	.uleb128 0xc
	.long	.LASF356
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.cdefs.h.407.c122ddb2157a4c1fbd957332b50319ec,comdat
.Ldebug_macro6:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x197
	.long	.LASF357
	.byte	0x5
	.uleb128 0x198
	.long	.LASF358
	.byte	0x5
	.uleb128 0x199
	.long	.LASF359
	.byte	0x5
	.uleb128 0x19a
	.long	.LASF360
	.byte	0x5
	.uleb128 0x19b
	.long	.LASF361
	.byte	0x5
	.uleb128 0x19d
	.long	.LASF362
	.byte	0x5
	.uleb128 0x19e
	.long	.LASF363
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stubs64.h.10.6fb4b470a4f113ab27ac07383b62200b,comdat
.Ldebug_macro7:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xa
	.long	.LASF364
	.byte	0x5
	.uleb128 0xb
	.long	.LASF365
	.byte	0x5
	.uleb128 0xc
	.long	.LASF366
	.byte	0x5
	.uleb128 0xd
	.long	.LASF367
	.byte	0x5
	.uleb128 0xe
	.long	.LASF368
	.byte	0x5
	.uleb128 0xf
	.long	.LASF369
	.byte	0x5
	.uleb128 0x10
	.long	.LASF370
	.byte	0x5
	.uleb128 0x11
	.long	.LASF371
	.byte	0x5
	.uleb128 0x12
	.long	.LASF372
	.byte	0x5
	.uleb128 0x13
	.long	.LASF373
	.byte	0x5
	.uleb128 0x14
	.long	.LASF374
	.byte	0x5
	.uleb128 0x15
	.long	.LASF375
	.byte	0x5
	.uleb128 0x16
	.long	.LASF376
	.byte	0x5
	.uleb128 0x17
	.long	.LASF377
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.31.e39a94e203ad4e1d978c0fc68ce016ee,comdat
.Ldebug_macro8:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x1f
	.long	.LASF378
	.byte	0x5
	.uleb128 0x20
	.long	.LASF379
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stddef.h.184.159df79b4ca79c76561572a55985524c,comdat
.Ldebug_macro9:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xb8
	.long	.LASF380
	.byte	0x5
	.uleb128 0xb9
	.long	.LASF381
	.byte	0x5
	.uleb128 0xba
	.long	.LASF382
	.byte	0x5
	.uleb128 0xbb
	.long	.LASF383
	.byte	0x5
	.uleb128 0xbc
	.long	.LASF384
	.byte	0x5
	.uleb128 0xbd
	.long	.LASF385
	.byte	0x5
	.uleb128 0xbe
	.long	.LASF386
	.byte	0x5
	.uleb128 0xbf
	.long	.LASF387
	.byte	0x5
	.uleb128 0xc0
	.long	.LASF388
	.byte	0x5
	.uleb128 0xc1
	.long	.LASF389
	.byte	0x5
	.uleb128 0xc2
	.long	.LASF390
	.byte	0x5
	.uleb128 0xc3
	.long	.LASF391
	.byte	0x5
	.uleb128 0xc4
	.long	.LASF392
	.byte	0x5
	.uleb128 0xc5
	.long	.LASF393
	.byte	0x5
	.uleb128 0xc6
	.long	.LASF394
	.byte	0x5
	.uleb128 0xc7
	.long	.LASF395
	.byte	0x5
	.uleb128 0xce
	.long	.LASF396
	.byte	0x6
	.uleb128 0xea
	.long	.LASF397
	.byte	0x6
	.uleb128 0x18d
	.long	.LASF398
	.byte	0x5
	.uleb128 0x192
	.long	.LASF399
	.byte	0x6
	.uleb128 0x198
	.long	.LASF400
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.types.h.89.468e2451361e3b92f048f6cad51690ff,comdat
.Ldebug_macro10:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x59
	.long	.LASF402
	.byte	0x5
	.uleb128 0x5a
	.long	.LASF403
	.byte	0x5
	.uleb128 0x5b
	.long	.LASF404
	.byte	0x5
	.uleb128 0x5c
	.long	.LASF405
	.byte	0x5
	.uleb128 0x5d
	.long	.LASF406
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF407
	.byte	0x5
	.uleb128 0x6c
	.long	.LASF408
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF409
	.byte	0x5
	.uleb128 0x6e
	.long	.LASF410
	.byte	0x5
	.uleb128 0x6f
	.long	.LASF411
	.byte	0x5
	.uleb128 0x70
	.long	.LASF412
	.byte	0x5
	.uleb128 0x71
	.long	.LASF413
	.byte	0x5
	.uleb128 0x72
	.long	.LASF414
	.byte	0x5
	.uleb128 0x73
	.long	.LASF415
	.byte	0x5
	.uleb128 0x75
	.long	.LASF416
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.typesizes.h.24.c4a72432ea65bcf9f35838c785ffdcc8,comdat
.Ldebug_macro11:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x18
	.long	.LASF417
	.byte	0x5
	.uleb128 0x22
	.long	.LASF418
	.byte	0x5
	.uleb128 0x23
	.long	.LASF419
	.byte	0x5
	.uleb128 0x26
	.long	.LASF420
	.byte	0x5
	.uleb128 0x27
	.long	.LASF421
	.byte	0x5
	.uleb128 0x28
	.long	.LASF422
	.byte	0x5
	.uleb128 0x29
	.long	.LASF423
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF424
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF425
	.byte	0x5
	.uleb128 0x2d
	.long	.LASF426
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF427
	.byte	0x5
	.uleb128 0x33
	.long	.LASF428
	.byte	0x5
	.uleb128 0x34
	.long	.LASF429
	.byte	0x5
	.uleb128 0x35
	.long	.LASF430
	.byte	0x5
	.uleb128 0x36
	.long	.LASF431
	.byte	0x5
	.uleb128 0x37
	.long	.LASF432
	.byte	0x5
	.uleb128 0x38
	.long	.LASF433
	.byte	0x5
	.uleb128 0x39
	.long	.LASF434
	.byte	0x5
	.uleb128 0x3a
	.long	.LASF435
	.byte	0x5
	.uleb128 0x3b
	.long	.LASF436
	.byte	0x5
	.uleb128 0x3c
	.long	.LASF437
	.byte	0x5
	.uleb128 0x3d
	.long	.LASF438
	.byte	0x5
	.uleb128 0x3e
	.long	.LASF439
	.byte	0x5
	.uleb128 0x3f
	.long	.LASF440
	.byte	0x5
	.uleb128 0x40
	.long	.LASF441
	.byte	0x5
	.uleb128 0x41
	.long	.LASF442
	.byte	0x5
	.uleb128 0x42
	.long	.LASF443
	.byte	0x5
	.uleb128 0x43
	.long	.LASF444
	.byte	0x5
	.uleb128 0x44
	.long	.LASF445
	.byte	0x5
	.uleb128 0x45
	.long	.LASF446
	.byte	0x5
	.uleb128 0x46
	.long	.LASF447
	.byte	0x5
	.uleb128 0x47
	.long	.LASF448
	.byte	0x5
	.uleb128 0x48
	.long	.LASF449
	.byte	0x5
	.uleb128 0x49
	.long	.LASF450
	.byte	0x5
	.uleb128 0x4f
	.long	.LASF451
	.byte	0x5
	.uleb128 0x52
	.long	.LASF452
	.byte	0x5
	.uleb128 0x56
	.long	.LASF453
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.36.2dd12c1fd035242ad5cfd0152a01be5a,comdat
.Ldebug_macro12:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x24
	.long	.LASF455
	.byte	0x5
	.uleb128 0x25
	.long	.LASF456
	.byte	0x5
	.uleb128 0x38
	.long	.LASF457
	.byte	0x6
	.uleb128 0x3a
	.long	.LASF458
	.byte	0x5
	.uleb128 0x42
	.long	.LASF459
	.byte	0x6
	.uleb128 0x44
	.long	.LASF460
	.byte	0x5
	.uleb128 0x48
	.long	.LASF461
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._G_config.h.5.b0f37d9e474454cf6e459063458db32f,comdat
.Ldebug_macro13:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x5
	.long	.LASF463
	.byte	0x5
	.uleb128 0xa
	.long	.LASF378
	.byte	0x5
	.uleb128 0xe
	.long	.LASF379
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stddef.h.234.5fa44232df77937e0d1fcac1468785aa,comdat
.Ldebug_macro14:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0xea
	.long	.LASF397
	.byte	0x6
	.uleb128 0x18d
	.long	.LASF398
	.byte	0x5
	.uleb128 0x192
	.long	.LASF399
	.byte	0x6
	.uleb128 0x198
	.long	.LASF400
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.wchar.h.80.628010d306c9ecbd260f9d4475ab1db1,comdat
.Ldebug_macro15:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x50
	.long	.LASF465
	.byte	0x6
	.uleb128 0x60
	.long	.LASF466
	.byte	0x6
	.uleb128 0x383
	.long	.LASF466
	.byte	0x6
	.uleb128 0x384
	.long	.LASF467
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4._G_config.h.46.5187c97b14fd664662cb32e6b94fc49e,comdat
.Ldebug_macro16:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x2e
	.long	.LASF468
	.byte	0x5
	.uleb128 0x30
	.long	.LASF469
	.byte	0x5
	.uleb128 0x31
	.long	.LASF470
	.byte	0x5
	.uleb128 0x33
	.long	.LASF471
	.byte	0x5
	.uleb128 0x36
	.long	.LASF472
	.byte	0x5
	.uleb128 0x38
	.long	.LASF473
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.libio.h.33.a775b9ecae273f33bc59931e9891e4ca,comdat
.Ldebug_macro17:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x21
	.long	.LASF474
	.byte	0x5
	.uleb128 0x22
	.long	.LASF475
	.byte	0x5
	.uleb128 0x23
	.long	.LASF476
	.byte	0x5
	.uleb128 0x24
	.long	.LASF477
	.byte	0x5
	.uleb128 0x25
	.long	.LASF478
	.byte	0x5
	.uleb128 0x26
	.long	.LASF479
	.byte	0x5
	.uleb128 0x27
	.long	.LASF480
	.byte	0x5
	.uleb128 0x28
	.long	.LASF481
	.byte	0x5
	.uleb128 0x29
	.long	.LASF482
	.byte	0x5
	.uleb128 0x2a
	.long	.LASF483
	.byte	0x5
	.uleb128 0x2b
	.long	.LASF484
	.byte	0x5
	.uleb128 0x2c
	.long	.LASF485
	.byte	0x5
	.uleb128 0x2d
	.long	.LASF486
	.byte	0x5
	.uleb128 0x30
	.long	.LASF487
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdarg.h.34.3a23a216c0c293b3d2ea2e89281481e6,comdat
.Ldebug_macro18:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0x22
	.long	.LASF488
	.byte	0x5
	.uleb128 0x27
	.long	.LASF489
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.libio.h.51.981a9f406a7830caa4638ead01d5e3e6,comdat
.Ldebug_macro19:
	.value	0x4
	.byte	0
	.byte	0x6
	.uleb128 0x33
	.long	.LASF490
	.byte	0x5
	.uleb128 0x34
	.long	.LASF491
	.byte	0x5
	.uleb128 0x3b
	.long	.LASF492
	.byte	0x5
	.uleb128 0x3e
	.long	.LASF493
	.byte	0x5
	.uleb128 0x4d
	.long	.LASF494
	.byte	0x5
	.uleb128 0x4e
	.long	.LASF495
	.byte	0x5
	.uleb128 0x4f
	.long	.LASF496
	.byte	0x5
	.uleb128 0x50
	.long	.LASF497
	.byte	0x5
	.uleb128 0x51
	.long	.LASF498
	.byte	0x5
	.uleb128 0x52
	.long	.LASF499
	.byte	0x5
	.uleb128 0x53
	.long	.LASF500
	.byte	0x5
	.uleb128 0x54
	.long	.LASF501
	.byte	0x5
	.uleb128 0x5c
	.long	.LASF502
	.byte	0x5
	.uleb128 0x5d
	.long	.LASF503
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF504
	.byte	0x5
	.uleb128 0x5f
	.long	.LASF505
	.byte	0x5
	.uleb128 0x60
	.long	.LASF506
	.byte	0x5
	.uleb128 0x61
	.long	.LASF507
	.byte	0x5
	.uleb128 0x62
	.long	.LASF508
	.byte	0x5
	.uleb128 0x63
	.long	.LASF509
	.byte	0x5
	.uleb128 0x64
	.long	.LASF510
	.byte	0x5
	.uleb128 0x65
	.long	.LASF511
	.byte	0x5
	.uleb128 0x66
	.long	.LASF512
	.byte	0x5
	.uleb128 0x67
	.long	.LASF513
	.byte	0x5
	.uleb128 0x68
	.long	.LASF514
	.byte	0x5
	.uleb128 0x69
	.long	.LASF515
	.byte	0x5
	.uleb128 0x6a
	.long	.LASF516
	.byte	0x5
	.uleb128 0x6b
	.long	.LASF517
	.byte	0x5
	.uleb128 0x6c
	.long	.LASF518
	.byte	0x5
	.uleb128 0x6d
	.long	.LASF519
	.byte	0x5
	.uleb128 0x6e
	.long	.LASF520
	.byte	0x5
	.uleb128 0x70
	.long	.LASF521
	.byte	0x5
	.uleb128 0x71
	.long	.LASF522
	.byte	0x5
	.uleb128 0x75
	.long	.LASF523
	.byte	0x5
	.uleb128 0x7d
	.long	.LASF524
	.byte	0x5
	.uleb128 0x7e
	.long	.LASF525
	.byte	0x5
	.uleb128 0x7f
	.long	.LASF526
	.byte	0x5
	.uleb128 0x80
	.long	.LASF527
	.byte	0x5
	.uleb128 0x81
	.long	.LASF528
	.byte	0x5
	.uleb128 0x82
	.long	.LASF529
	.byte	0x5
	.uleb128 0x83
	.long	.LASF530
	.byte	0x5
	.uleb128 0x84
	.long	.LASF531
	.byte	0x5
	.uleb128 0x85
	.long	.LASF532
	.byte	0x5
	.uleb128 0x86
	.long	.LASF533
	.byte	0x5
	.uleb128 0x87
	.long	.LASF534
	.byte	0x5
	.uleb128 0x88
	.long	.LASF535
	.byte	0x5
	.uleb128 0x89
	.long	.LASF536
	.byte	0x5
	.uleb128 0x8a
	.long	.LASF537
	.byte	0x5
	.uleb128 0x8b
	.long	.LASF538
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF539
	.byte	0x5
	.uleb128 0x8d
	.long	.LASF540
	.byte	0x5
	.uleb128 0xf7
	.long	.LASF541
	.byte	0x5
	.uleb128 0x114
	.long	.LASF542
	.byte	0x5
	.uleb128 0x144
	.long	.LASF543
	.byte	0x5
	.uleb128 0x145
	.long	.LASF544
	.byte	0x5
	.uleb128 0x146
	.long	.LASF545
	.byte	0x5
	.uleb128 0x190
	.long	.LASF546
	.byte	0x5
	.uleb128 0x195
	.long	.LASF547
	.byte	0x5
	.uleb128 0x198
	.long	.LASF548
	.byte	0x5
	.uleb128 0x19c
	.long	.LASF549
	.byte	0x5
	.uleb128 0x1af
	.long	.LASF550
	.byte	0x5
	.uleb128 0x1b0
	.long	.LASF551
	.byte	0x5
	.uleb128 0x1ba
	.long	.LASF552
	.byte	0x5
	.uleb128 0x1c8
	.long	.LASF553
	.byte	0x5
	.uleb128 0x1c9
	.long	.LASF554
	.byte	0x5
	.uleb128 0x1ca
	.long	.LASF555
	.byte	0x5
	.uleb128 0x1cb
	.long	.LASF556
	.byte	0x5
	.uleb128 0x1cc
	.long	.LASF557
	.byte	0x5
	.uleb128 0x1cd
	.long	.LASF558
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.80.2c0b67e94eb93fd8dd1cc22c150ce71c,comdat
.Ldebug_macro20:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x50
	.long	.LASF559
	.byte	0x5
	.uleb128 0x5e
	.long	.LASF560
	.byte	0x5
	.uleb128 0x67
	.long	.LASF561
	.byte	0x5
	.uleb128 0x78
	.long	.LASF562
	.byte	0x5
	.uleb128 0x79
	.long	.LASF563
	.byte	0x5
	.uleb128 0x7a
	.long	.LASF564
	.byte	0x5
	.uleb128 0x7f
	.long	.LASF565
	.byte	0x5
	.uleb128 0x8c
	.long	.LASF566
	.byte	0x5
	.uleb128 0x8d
	.long	.LASF567
	.byte	0x5
	.uleb128 0x8e
	.long	.LASF568
	.byte	0x5
	.uleb128 0x97
	.long	.LASF569
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio_lim.h.23.557290a6cddeba0587f574f29e3a5fb9,comdat
.Ldebug_macro21:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x17
	.long	.LASF570
	.byte	0x5
	.uleb128 0x18
	.long	.LASF571
	.byte	0x5
	.uleb128 0x19
	.long	.LASF572
	.byte	0x5
	.uleb128 0x1c
	.long	.LASF573
	.byte	0x6
	.uleb128 0x24
	.long	.LASF574
	.byte	0x5
	.uleb128 0x25
	.long	.LASF575
	.byte	0
	.section	.debug_macro,"G",@progbits,wm4.stdio.h.172.df21df34a7396d7da2e08f9b617d582f,comdat
.Ldebug_macro22:
	.value	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xac
	.long	.LASF576
	.byte	0x5
	.uleb128 0xad
	.long	.LASF577
	.byte	0x5
	.uleb128 0xae
	.long	.LASF578
	.byte	0x5
	.uleb128 0x21f
	.long	.LASF579
	.byte	0x5
	.uleb128 0x249
	.long	.LASF580
	.byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF528:
	.string	"_IO_DEC 020"
.LASF244:
	.string	"__USE_ISOCXX11"
.LASF578:
	.string	"stderr stderr"
.LASF390:
	.string	"_SIZE_T_DEFINED "
.LASF71:
	.string	"__LONG_LONG_MAX__ 9223372036854775807LL"
.LASF176:
	.string	"__DEC64_SUBNORMAL_MIN__ 0.000000000000001E-383DD"
.LASF141:
	.string	"__DBL_DECIMAL_DIG__ 17"
.LASF129:
	.string	"__FLT_MIN__ 1.17549435082228750797e-38F"
.LASF124:
	.string	"__FLT_MIN_10_EXP__ (-37)"
.LASF419:
	.string	"__SYSCALL_ULONG_TYPE __ULONGWORD_TYPE"
.LASF446:
	.string	"__CLOCKID_T_TYPE __S32_TYPE"
.LASF201:
	.string	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1"
.LASF110:
	.string	"__INT_FAST32_MAX__ 9223372036854775807L"
.LASF451:
	.string	"__OFF_T_MATCHES_OFF64_T 1"
.LASF175:
	.string	"__DEC64_EPSILON__ 1E-15DD"
.LASF109:
	.string	"__INT_FAST16_MAX__ 9223372036854775807L"
.LASF92:
	.string	"__INT_LEAST8_MAX__ 127"
.LASF472:
	.string	"_G_HAVE_ST_BLKSIZE defined (_STATBUF_ST_BLKSIZE)"
.LASF327:
	.string	"__flexarr []"
.LASF84:
	.string	"__INT8_MAX__ 127"
.LASF101:
	.string	"__UINT8_C(c) c"
.LASF501:
	.string	"_IOS_BIN 128"
.LASF346:
	.string	"__attribute_artificial__ __attribute__ ((__artificial__))"
.LASF517:
	.string	"_IO_IS_APPENDING 0x1000"
.LASF333:
	.string	"__attribute_malloc__ __attribute__ ((__malloc__))"
.LASF509:
	.string	"_IO_EOF_SEEN 0x10"
.LASF567:
	.string	"SEEK_CUR 1"
.LASF559:
	.string	"_VA_LIST_DEFINED "
.LASF137:
	.string	"__DBL_MIN_EXP__ (-1021)"
.LASF194:
	.string	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 2"
.LASF577:
	.string	"stdout stdout"
.LASF291:
	.string	"__USE_BSD 1"
.LASF402:
	.string	"__S16_TYPE short int"
.LASF455:
	.string	"__need_FILE "
.LASF208:
	.string	"__SIZEOF_WINT_T__ 4"
.LASF268:
	.string	"__GNUC_PREREQ(maj,min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))"
.LASF433:
	.string	"__BLKCNT_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF382:
	.string	"_SIZE_T "
.LASF278:
	.string	"_POSIX_C_SOURCE"
.LASF469:
	.string	"_G_HAVE_MMAP 1"
.LASF157:
	.string	"__LDBL_MIN__ 3.36210314311209350626e-4932L"
.LASF493:
	.string	"EOF (-1)"
.LASF508:
	.string	"_IO_NO_WRITES 8"
.LASF159:
	.string	"__LDBL_DENORM_MIN__ 3.64519953188247460253e-4951L"
.LASF431:
	.string	"__RLIM_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF394:
	.string	"_GCC_SIZE_T "
.LASF3:
	.string	"__GNUC_MINOR__ 8"
.LASF584:
	.string	"unsigned int"
.LASF299:
	.string	"__GLIBC_PREREQ(maj,min) ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((maj) << 16) + (min))"
.LASF379:
	.string	"__need_NULL "
.LASF276:
	.string	"_POSIX_SOURCE"
.LASF18:
	.string	"__SIZEOF_SHORT__ 2"
.LASF37:
	.string	"__CHAR16_TYPE__ short unsigned int"
.LASF205:
	.string	"__SSP__ 1"
.LASF22:
	.string	"__SIZEOF_SIZE_T__ 8"
.LASF2:
	.string	"__GNUC__ 4"
.LASF26:
	.string	"__ORDER_BIG_ENDIAN__ 4321"
.LASF514:
	.string	"_IO_LINE_BUF 0x200"
.LASF375:
	.string	"__stub_sigreturn "
.LASF386:
	.string	"__SIZE_T "
.LASF107:
	.string	"__UINT64_C(c) c ## UL"
.LASF295:
	.string	"__GNU_LIBRARY__"
.LASF135:
	.string	"__DBL_MANT_DIG__ 53"
.LASF134:
	.string	"__FLT_HAS_QUIET_NAN__ 1"
.LASF334:
	.string	"__attribute_alloc_size__(params) __attribute__ ((__alloc_size__ params))"
.LASF420:
	.string	"__DEV_T_TYPE __UQUAD_TYPE"
.LASF592:
	.string	"/home/ciro/bak/git/cpp/cheat/gdb"
.LASF9:
	.string	"__ATOMIC_RELEASE 3"
.LASF562:
	.string	"_IOFBF 0"
.LASF367:
	.string	"__stub_fchflags "
.LASF41:
	.string	"__INT16_TYPE__ short int"
.LASF168:
	.string	"__DEC32_EPSILON__ 1E-6DF"
.LASF392:
	.string	"_SIZE_T_DECLARED "
.LASF69:
	.string	"__INT_MAX__ 2147483647"
.LASF150:
	.string	"__LDBL_DIG__ 18"
.LASF315:
	.string	"__BEGIN_NAMESPACE_STD "
.LASF7:
	.string	"__ATOMIC_SEQ_CST 5"
.LASF281:
	.string	"__USE_POSIX2 1"
.LASF285:
	.string	"__USE_ISOC95 1"
.LASF317:
	.string	"__USING_NAMESPACE_STD(name) "
.LASF47:
	.string	"__UINT64_TYPE__ long unsigned int"
.LASF48:
	.string	"__INT_LEAST8_TYPE__ signed char"
.LASF54:
	.string	"__UINT_LEAST32_TYPE__ unsigned int"
.LASF504:
	.string	"_IO_MAGIC_MASK 0xFFFF0000"
.LASF311:
	.string	"__ptr_t void *"
.LASF404:
	.string	"__S32_TYPE int"
.LASF62:
	.string	"__UINT_FAST32_TYPE__ long unsigned int"
.LASF238:
	.string	"__STDC_NO_THREADS__ 1"
.LASF28:
	.string	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF100:
	.string	"__UINT_LEAST8_MAX__ 255"
.LASF228:
	.string	"linux 1"
.LASF146:
	.string	"__DBL_HAS_DENORM__ 1"
.LASF67:
	.string	"__SCHAR_MAX__ 127"
.LASF51:
	.string	"__INT_LEAST64_TYPE__ long int"
.LASF73:
	.string	"__WCHAR_MIN__ (-__WCHAR_MAX__ - 1)"
.LASF532:
	.string	"_IO_SHOWPOINT 0400"
.LASF61:
	.string	"__UINT_FAST16_TYPE__ long unsigned int"
.LASF448:
	.string	"__BLKSIZE_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF128:
	.string	"__FLT_MAX__ 3.40282346638528859812e+38F"
.LASF55:
	.string	"__UINT_LEAST64_TYPE__ long unsigned int"
.LASF81:
	.string	"__UINTMAX_C(c) c ## UL"
.LASF56:
	.string	"__INT_FAST8_TYPE__ signed char"
.LASF145:
	.string	"__DBL_DENORM_MIN__ ((double)4.94065645841246544177e-324L)"
.LASF454:
	.string	"__STD_TYPE"
.LASF251:
	.string	"__USE_UNIX98"
.LASF294:
	.string	"__USE_FORTIFY_LEVEL 0"
.LASF288:
	.string	"_ATFILE_SOURCE"
.LASF233:
	.string	"__DECIMAL_BID_FORMAT__ 1"
.LASF206:
	.string	"__SIZEOF_INT128__ 16"
.LASF306:
	.string	"__NTH(fct) __attribute__ ((__nothrow__ __LEAF)) fct"
.LASF496:
	.string	"_IOS_ATEND 4"
.LASF537:
	.string	"_IO_UNITBUF 020000"
.LASF93:
	.string	"__INT8_C(c) c"
.LASF385:
	.string	"_T_SIZE "
.LASF565:
	.string	"BUFSIZ _IO_BUFSIZ"
.LASF289:
	.string	"_ATFILE_SOURCE 1"
.LASF209:
	.string	"__SIZEOF_PTRDIFF_T__ 8"
.LASF304:
	.string	"__THROW __attribute__ ((__nothrow__ __LEAF))"
.LASF139:
	.string	"__DBL_MAX_EXP__ 1024"
.LASF561:
	.string	"__ssize_t_defined "
.LASF384:
	.string	"_T_SIZE_ "
.LASF551:
	.string	"_IO_ferror_unlocked(__fp) (((__fp)->_flags & _IO_ERR_SEEN) != 0)"
.LASF391:
	.string	"_BSD_SIZE_T_DEFINED_ "
.LASF352:
	.string	"__glibc_unlikely(cond) __builtin_expect ((cond), 0)"
.LASF112:
	.string	"__UINT_FAST8_MAX__ 255"
.LASF426:
	.string	"__NLINK_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF230:
	.string	"__unix__ 1"
.LASF343:
	.string	"__attribute_warn_unused_result__ __attribute__ ((__warn_unused_result__))"
.LASF184:
	.string	"__REGISTER_PREFIX__ "
.LASF116:
	.string	"__INTPTR_MAX__ 9223372036854775807L"
.LASF447:
	.string	"__TIMER_T_TYPE void *"
.LASF388:
	.string	"_BSD_SIZE_T_ "
.LASF374:
	.string	"__stub_setlogin "
.LASF122:
	.string	"__FLT_DIG__ 6"
.LASF189:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1"
.LASF275:
	.string	"__USE_POSIX_IMPLICITLY 1"
.LASF239:
	.string	"_STDIO_H 1"
.LASF143:
	.string	"__DBL_MIN__ ((double)2.22507385850720138309e-308L)"
.LASF166:
	.string	"__DEC32_MIN__ 1E-95DF"
.LASF473:
	.string	"_G_BUFSIZ 8192"
.LASF305:
	.string	"__THROWNL __attribute__ ((__nothrow__))"
.LASF158:
	.string	"__LDBL_EPSILON__ 1.08420217248550443401e-19L"
.LASF337:
	.string	"__attribute_used__ __attribute__ ((__used__))"
.LASF543:
	.string	"_IO_stdin ((_IO_FILE*)(&_IO_2_1_stdin_))"
.LASF178:
	.string	"__DEC128_MIN_EXP__ (-6142)"
.LASF267:
	.string	"__KERNEL_STRICT_NAMES "
.LASF579:
	.string	"getc(_fp) _IO_getc (_fp)"
.LASF182:
	.string	"__DEC128_EPSILON__ 1E-33DL"
.LASF248:
	.string	"__USE_POSIX199506"
.LASF120:
	.string	"__FLT_RADIX__ 2"
.LASF482:
	.string	"_IO_iconv_t _G_iconv_t"
.LASF308:
	.string	"__PMT(args) args"
.LASF422:
	.string	"__GID_T_TYPE __U32_TYPE"
.LASF21:
	.string	"__SIZEOF_LONG_DOUBLE__ 16"
.LASF148:
	.string	"__DBL_HAS_QUIET_NAN__ 1"
.LASF401:
	.string	"_BITS_TYPES_H 1"
.LASF430:
	.string	"__PID_T_TYPE __S32_TYPE"
.LASF590:
	.string	"GNU C 4.8.4 -mtune=generic -march=x86-64 -ggdb3 -fstack-protector"
.LASF91:
	.string	"__UINT64_MAX__ 18446744073709551615UL"
.LASF215:
	.string	"__ATOMIC_HLE_RELEASE 131072"
.LASF153:
	.string	"__LDBL_MAX_EXP__ 16384"
.LASF98:
	.string	"__INT_LEAST64_MAX__ 9223372036854775807L"
.LASF370:
	.string	"__stub_gtty "
.LASF505:
	.string	"_IO_USER_BUF 1"
.LASF442:
	.string	"__USECONDS_T_TYPE __U32_TYPE"
.LASF349:
	.string	"__va_arg_pack() __builtin_va_arg_pack ()"
.LASF64:
	.string	"__INTPTR_TYPE__ long int"
.LASF174:
	.string	"__DEC64_MAX__ 9.999999999999999E384DD"
.LASF131:
	.string	"__FLT_DENORM_MIN__ 1.40129846432481707092e-45F"
.LASF198:
	.string	"__GCC_ATOMIC_INT_LOCK_FREE 2"
.LASF219:
	.string	"__MMX__ 1"
.LASF108:
	.string	"__INT_FAST8_MAX__ 127"
.LASF531:
	.string	"_IO_SHOWBASE 0200"
.LASF377:
	.string	"__stub_stty "
.LASF156:
	.string	"__LDBL_MAX__ 1.18973149535723176502e+4932L"
.LASF526:
	.string	"_IO_RIGHT 04"
.LASF403:
	.string	"__U16_TYPE unsigned short int"
.LASF25:
	.string	"__ORDER_LITTLE_ENDIAN__ 1234"
.LASF284:
	.string	"__USE_XOPEN2K 1"
.LASF462:
	.string	"_IO_STDIO_H "
.LASF271:
	.string	"_BSD_SOURCE"
.LASF177:
	.string	"__DEC128_MANT_DIG__ 34"
.LASF286:
	.string	"__USE_ISOC99 1"
.LASF458:
	.string	"__need_FILE"
.LASF42:
	.string	"__INT32_TYPE__ int"
.LASF332:
	.string	"__ASMNAME2(prefix,cname) __STRING (prefix) cname"
.LASF405:
	.string	"__U32_TYPE unsigned int"
.LASF363:
	.string	"__REDIRECT_NTH_LDBL(name,proto,alias) __REDIRECT_NTH (name, proto, alias)"
.LASF243:
	.string	"__USE_ISOC95"
.LASF165:
	.string	"__DEC32_MAX_EXP__ 97"
.LASF564:
	.string	"_IONBF 2"
.LASF242:
	.string	"__USE_ISOC99"
.LASF282:
	.string	"__USE_POSIX199309 1"
.LASF471:
	.string	"_G_IO_IO_FILE_VERSION 0x20001"
.LASF515:
	.string	"_IO_TIED_PUT_GET 0x400"
.LASF236:
	.string	"__STDC_IEC_559_COMPLEX__ 1"
.LASF142:
	.string	"__DBL_MAX__ ((double)1.79769313486231570815e+308L)"
.LASF234:
	.string	"_STDC_PREDEF_H 1"
.LASF372:
	.string	"__stub_putmsg "
.LASF94:
	.string	"__INT_LEAST16_MAX__ 32767"
.LASF389:
	.string	"_SIZE_T_DEFINED_ "
.LASF313:
	.string	"__BEGIN_DECLS "
.LASF398:
	.string	"NULL"
.LASF498:
	.string	"_IOS_TRUNC 16"
.LASF66:
	.string	"__GXX_ABI_VERSION 1002"
.LASF443:
	.string	"__SUSECONDS_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF568:
	.string	"SEEK_END 2"
.LASF513:
	.string	"_IO_IN_BACKUP 0x100"
.LASF270:
	.string	"_DEFAULT_SOURCE 1"
.LASF553:
	.string	"_IO_peekc(_fp) _IO_peekc_unlocked (_fp)"
.LASF211:
	.string	"__amd64__ 1"
.LASF465:
	.string	"____mbstate_t_defined 1"
.LASF511:
	.string	"_IO_DELETE_DONT_CLOSE 0x40"
.LASF354:
	.string	"__WORDSIZE 64"
.LASF45:
	.string	"__UINT16_TYPE__ short unsigned int"
.LASF503:
	.string	"_OLD_STDIO_MAGIC 0xFABC0000"
.LASF499:
	.string	"_IOS_NOCREATE 32"
.LASF218:
	.string	"__code_model_small__ 1"
.LASF193:
	.string	"__GCC_ATOMIC_CHAR_LOCK_FREE 2"
.LASF533:
	.string	"_IO_UPPERCASE 01000"
.LASF413:
	.string	"__ULONG32_TYPE unsigned int"
.LASF53:
	.string	"__UINT_LEAST16_TYPE__ short unsigned int"
.LASF126:
	.string	"__FLT_MAX_10_EXP__ 38"
.LASF524:
	.string	"_IO_SKIPWS 01"
.LASF399:
	.string	"NULL ((void *)0)"
.LASF86:
	.string	"__INT32_MAX__ 2147483647"
.LASF342:
	.string	"__nonnull(params) __attribute__ ((__nonnull__ params))"
.LASF550:
	.string	"_IO_feof_unlocked(__fp) (((__fp)->_flags & _IO_EOF_SEEN) != 0)"
.LASF187:
	.string	"__NO_INLINE__ 1"
.LASF545:
	.string	"_IO_stderr ((_IO_FILE*)(&_IO_2_1_stderr_))"
.LASF366:
	.string	"__stub_fattach "
.LASF121:
	.string	"__FLT_MANT_DIG__ 24"
.LASF312:
	.string	"__long_double_t long double"
.LASF190:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1"
.LASF329:
	.string	"__REDIRECT_NTH(name,proto,alias) name proto __asm__ (__ASMNAME (#alias)) __THROW"
.LASF31:
	.string	"__SIZE_TYPE__ long unsigned int"
.LASF449:
	.string	"__FSID_T_TYPE struct { int __val[2]; }"
.LASF119:
	.string	"__DEC_EVAL_METHOD__ 2"
.LASF481:
	.string	"_IO_uid_t __uid_t"
.LASF138:
	.string	"__DBL_MIN_10_EXP__ (-307)"
.LASF589:
	.string	"char"
.LASF466:
	.string	"__need_mbstate_t"
.LASF529:
	.string	"_IO_OCT 040"
.LASF152:
	.string	"__LDBL_MIN_10_EXP__ (-4931)"
.LASF483:
	.string	"_IO_HAVE_ST_BLKSIZE _G_HAVE_ST_BLKSIZE"
.LASF316:
	.string	"__END_NAMESPACE_STD "
.LASF118:
	.string	"__FLT_EVAL_METHOD__ 0"
.LASF435:
	.string	"__FSBLKCNT_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF213:
	.string	"__x86_64__ 1"
.LASF79:
	.string	"__INTMAX_C(c) c ## L"
.LASF114:
	.string	"__UINT_FAST32_MAX__ 18446744073709551615UL"
.LASF328:
	.string	"__REDIRECT(name,proto,alias) name proto __asm__ (__ASMNAME (#alias))"
.LASF436:
	.string	"__FSBLKCNT64_T_TYPE __UQUAD_TYPE"
.LASF283:
	.string	"__USE_POSIX199506 1"
.LASF226:
	.string	"__linux 1"
.LASF479:
	.string	"_IO_off64_t __off64_t"
.LASF381:
	.string	"__SIZE_T__ "
.LASF555:
	.string	"_IO_funlockfile(_fp) "
.LASF445:
	.string	"__KEY_T_TYPE __S32_TYPE"
.LASF6:
	.string	"__ATOMIC_RELAXED 0"
.LASF347:
	.string	"__extern_inline extern __inline __attribute__ ((__gnu_inline__))"
.LASF200:
	.string	"__GCC_ATOMIC_LLONG_LOCK_FREE 2"
.LASF90:
	.string	"__UINT32_MAX__ 4294967295U"
.LASF522:
	.string	"_IO_FLAGS2_NOTCANCEL 2"
.LASF345:
	.string	"__always_inline __inline __attribute__ ((__always_inline__))"
.LASF502:
	.string	"_IO_MAGIC 0xFBAD0000"
.LASF344:
	.string	"__wur "
.LASF59:
	.string	"__INT_FAST64_TYPE__ long int"
.LASF576:
	.string	"stdin stdin"
.LASF318:
	.string	"__BEGIN_NAMESPACE_C99 "
.LASF417:
	.string	"_BITS_TYPESIZES_H 1"
.LASF167:
	.string	"__DEC32_MAX__ 9.999999E96DF"
.LASF557:
	.string	"_IO_cleanup_region_start(_fct,_fp) "
.LASF247:
	.string	"__USE_POSIX199309"
.LASF49:
	.string	"__INT_LEAST16_TYPE__ short int"
.LASF348:
	.string	"__extern_always_inline extern __always_inline __attribute__ ((__gnu_inline__))"
.LASF225:
	.string	"__gnu_linux__ 1"
.LASF544:
	.string	"_IO_stdout ((_IO_FILE*)(&_IO_2_1_stdout_))"
.LASF425:
	.string	"__MODE_T_TYPE __U32_TYPE"
.LASF293:
	.string	"__USE_ATFILE 1"
.LASF252:
	.string	"__USE_XOPEN2K"
.LASF136:
	.string	"__DBL_DIG__ 15"
.LASF300:
	.string	"_SYS_CDEFS_H 1"
.LASF359:
	.string	"__LDBL_REDIR1_NTH(name,proto,alias) name proto __THROW"
.LASF14:
	.string	"__LP64__ 1"
.LASF199:
	.string	"__GCC_ATOMIC_LONG_LOCK_FREE 2"
.LASF102:
	.string	"__UINT_LEAST16_MAX__ 65535"
.LASF336:
	.string	"__attribute_const__ __attribute__ ((__const__))"
.LASF11:
	.string	"__ATOMIC_CONSUME 1"
.LASF13:
	.string	"_LP64 1"
.LASF240:
	.string	"_FEATURES_H 1"
.LASF427:
	.string	"__FSWORD_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF406:
	.string	"__SLONGWORD_TYPE long int"
.LASF85:
	.string	"__INT16_MAX__ 32767"
.LASF358:
	.string	"__LDBL_REDIR(name,proto) name proto"
.LASF23:
	.string	"__CHAR_BIT__ 8"
.LASF113:
	.string	"__UINT_FAST16_MAX__ 18446744073709551615UL"
.LASF192:
	.string	"__GCC_ATOMIC_BOOL_LOCK_FREE 2"
.LASF453:
	.string	"__FD_SETSIZE 1024"
.LASF12:
	.string	"__FINITE_MATH_ONLY__ 0"
.LASF320:
	.string	"__USING_NAMESPACE_C99(name) "
.LASF558:
	.string	"_IO_cleanup_region_end(_Doit) "
.LASF541:
	.string	"_IO_file_flags _flags"
.LASF350:
	.string	"__va_arg_pack_len() __builtin_va_arg_pack_len ()"
.LASF542:
	.string	"__HAVE_COLUMN "
.LASF494:
	.string	"_IOS_INPUT 1"
.LASF68:
	.string	"__SHRT_MAX__ 32767"
.LASF580:
	.string	"putc(_ch,_fp) _IO_putc (_ch, _fp)"
.LASF416:
	.string	"__STD_TYPE typedef"
.LASF301:
	.string	"__PMT"
.LASF409:
	.string	"__UQUAD_TYPE unsigned long int"
.LASF302:
	.string	"__LEAF , __leaf__"
.LASF309:
	.string	"__CONCAT(x,y) x ## y"
.LASF65:
	.string	"__UINTPTR_TYPE__ long unsigned int"
.LASF95:
	.string	"__INT16_C(c) c"
.LASF203:
	.string	"__GCC_HAVE_DWARF2_CFI_ASM 1"
.LASF19:
	.string	"__SIZEOF_FLOAT__ 4"
.LASF169:
	.string	"__DEC32_SUBNORMAL_MIN__ 0.000001E-95DF"
.LASF133:
	.string	"__FLT_HAS_INFINITY__ 1"
.LASF106:
	.string	"__UINT_LEAST64_MAX__ 18446744073709551615UL"
.LASF476:
	.string	"_IO_size_t size_t"
.LASF296:
	.string	"__GNU_LIBRARY__ 6"
.LASF0:
	.string	"__STDC__ 1"
.LASF221:
	.string	"__SSE2__ 1"
.LASF412:
	.string	"__SLONG32_TYPE int"
.LASF298:
	.string	"__GLIBC_MINOR__ 19"
.LASF16:
	.string	"__SIZEOF_LONG__ 8"
.LASF5:
	.string	"__VERSION__ \"4.8.4\""
.LASF80:
	.string	"__UINTMAX_MAX__ 18446744073709551615UL"
.LASF521:
	.string	"_IO_FLAGS2_MMAP 1"
.LASF185:
	.string	"__USER_LABEL_PREFIX__ "
.LASF34:
	.string	"__WINT_TYPE__ unsigned int"
.LASF279:
	.string	"_POSIX_C_SOURCE 200809L"
.LASF105:
	.string	"__UINT32_C(c) c ## U"
.LASF58:
	.string	"__INT_FAST32_TYPE__ long int"
.LASF461:
	.string	"_STDIO_USES_IOSTREAM "
.LASF20:
	.string	"__SIZEOF_DOUBLE__ 8"
.LASF535:
	.string	"_IO_SCIENTIFIC 04000"
.LASF434:
	.string	"__BLKCNT64_T_TYPE __SQUAD_TYPE"
.LASF4:
	.string	"__GNUC_PATCHLEVEL__ 4"
.LASF265:
	.string	"__USE_FORTIFY_LEVEL"
.LASF75:
	.string	"__WINT_MIN__ 0U"
.LASF353:
	.string	"__glibc_likely(cond) __builtin_expect ((cond), 1)"
.LASF571:
	.string	"TMP_MAX 238328"
.LASF566:
	.string	"SEEK_SET 0"
.LASF444:
	.string	"__DADDR_T_TYPE __S32_TYPE"
.LASF212:
	.string	"__x86_64 1"
.LASF263:
	.string	"__USE_GNU"
.LASF322:
	.string	"__bos0(ptr) __builtin_object_size (ptr, 0)"
.LASF459:
	.string	"____FILE_defined 1"
.LASF161:
	.string	"__LDBL_HAS_INFINITY__ 1"
.LASF280:
	.string	"__USE_POSIX 1"
.LASF452:
	.string	"__INO_T_MATCHES_INO64_T 1"
.LASF492:
	.string	"_IO_UNIFIED_JUMPTABLES 1"
.LASF554:
	.string	"_IO_flockfile(_fp) "
.LASF207:
	.string	"__SIZEOF_WCHAR_T__ 4"
.LASF339:
	.string	"__attribute_deprecated__ __attribute__ ((__deprecated__))"
.LASF29:
	.string	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__"
.LASF340:
	.string	"__attribute_format_arg__(x) __attribute__ ((__format_arg__ (x)))"
.LASF163:
	.string	"__DEC32_MANT_DIG__ 7"
.LASF258:
	.string	"__USE_FILE_OFFSET64"
.LASF171:
	.string	"__DEC64_MIN_EXP__ (-382)"
.LASF83:
	.string	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)"
.LASF488:
	.string	"__need___va_list"
.LASF527:
	.string	"_IO_INTERNAL 010"
.LASF393:
	.string	"___int_size_t_h "
.LASF8:
	.string	"__ATOMIC_ACQUIRE 2"
.LASF103:
	.string	"__UINT16_C(c) c"
.LASF371:
	.string	"__stub_lchmod "
.LASF378:
	.string	"__need_size_t "
.LASF321:
	.string	"__bos(ptr) __builtin_object_size (ptr, __USE_FORTIFY_LEVEL > 1)"
.LASF262:
	.string	"__USE_ATFILE"
.LASF223:
	.string	"__SSE_MATH__ 1"
.LASF292:
	.string	"__USE_SVID 1"
.LASF36:
	.string	"__UINTMAX_TYPE__ long unsigned int"
.LASF188:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1"
.LASF397:
	.string	"__need_size_t"
.LASF330:
	.string	"__REDIRECT_NTHNL(name,proto,alias) name proto __asm__ (__ASMNAME (#alias)) __THROWNL"
.LASF179:
	.string	"__DEC128_MAX_EXP__ 6145"
.LASF525:
	.string	"_IO_LEFT 02"
.LASF323:
	.string	"__fortify_function __extern_always_inline __attribute_artificial__"
.LASF540:
	.string	"_IO_BOOLALPHA 0200000"
.LASF115:
	.string	"__UINT_FAST64_MAX__ 18446744073709551615UL"
.LASF88:
	.string	"__UINT8_MAX__ 255"
.LASF411:
	.string	"__UWORD_TYPE unsigned long int"
.LASF196:
	.string	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 2"
.LASF552:
	.string	"_IO_PENDING_OUTPUT_COUNT(_fp) ((_fp)->_IO_write_ptr - (_fp)->_IO_write_base)"
.LASF520:
	.string	"_IO_USER_LOCK 0x8000"
.LASF27:
	.string	"__ORDER_PDP_ENDIAN__ 3412"
.LASF464:
	.string	"__need_mbstate_t "
.LASF74:
	.string	"__WINT_MAX__ 4294967295U"
.LASF111:
	.string	"__INT_FAST64_MAX__ 9223372036854775807L"
.LASF77:
	.string	"__SIZE_MAX__ 18446744073709551615UL"
.LASF127:
	.string	"__FLT_DECIMAL_DIG__ 9"
.LASF324:
	.string	"__warndecl(name,msg) extern void name (void) __attribute__((__warning__ (msg)))"
.LASF563:
	.string	"_IOLBF 1"
.LASF310:
	.string	"__STRING(x) #x"
.LASF457:
	.string	"__FILE_defined 1"
.LASF151:
	.string	"__LDBL_MIN_EXP__ (-16381)"
.LASF534:
	.string	"_IO_SHOWPOS 02000"
.LASF489:
	.string	"__GNUC_VA_LIST "
.LASF99:
	.string	"__INT64_C(c) c ## L"
.LASF15:
	.string	"__SIZEOF_INT__ 4"
.LASF556:
	.string	"_IO_ftrylockfile(_fp) "
.LASF410:
	.string	"__SWORD_TYPE long int"
.LASF586:
	.string	"short int"
.LASF369:
	.string	"__stub_getmsg "
.LASF172:
	.string	"__DEC64_MAX_EXP__ 385"
.LASF237:
	.string	"__STDC_ISO_10646__ 201103L"
.LASF587:
	.string	"long int"
.LASF87:
	.string	"__INT64_MAX__ 9223372036854775807L"
.LASF428:
	.string	"__OFF_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF246:
	.string	"__USE_POSIX2"
.LASF38:
	.string	"__CHAR32_TYPE__ unsigned int"
.LASF400:
	.string	"__need_NULL"
.LASF186:
	.string	"__GNUC_GNU_INLINE__ 1"
.LASF180:
	.string	"__DEC128_MIN__ 1E-6143DL"
.LASF518:
	.string	"_IO_IS_FILEBUF 0x2000"
.LASF547:
	.string	"_IO_getc_unlocked(_fp) (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) ? __uflow (_fp) : *(unsigned char *) (_fp)->_IO_read_ptr++)"
.LASF423:
	.string	"__INO_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF60:
	.string	"__UINT_FAST8_TYPE__ unsigned char"
.LASF97:
	.string	"__INT32_C(c) c"
.LASF438:
	.string	"__FSFILCNT64_T_TYPE __UQUAD_TYPE"
.LASF162:
	.string	"__LDBL_HAS_QUIET_NAN__ 1"
.LASF40:
	.string	"__INT8_TYPE__ signed char"
.LASF33:
	.string	"__WCHAR_TYPE__ int"
.LASF70:
	.string	"__LONG_MAX__ 9223372036854775807L"
.LASF260:
	.string	"__USE_SVID"
.LASF480:
	.string	"_IO_pid_t __pid_t"
.LASF512:
	.string	"_IO_LINKED 0x80"
.LASF373:
	.string	"__stub_revoke "
.LASF357:
	.string	"__LDBL_REDIR1(name,proto,alias) name proto"
.LASF264:
	.string	"__USE_REENTRANT"
.LASF510:
	.string	"_IO_ERR_SEEN 0x20"
.LASF46:
	.string	"__UINT32_TYPE__ unsigned int"
.LASF360:
	.string	"__LDBL_REDIR_NTH(name,proto) name proto __THROW"
.LASF254:
	.string	"__USE_XOPEN2K8"
.LASF78:
	.string	"__INTMAX_MAX__ 9223372036854775807L"
.LASF572:
	.string	"FILENAME_MAX 4096"
.LASF249:
	.string	"__USE_XOPEN"
.LASF456:
	.string	"__need___FILE "
.LASF575:
	.string	"FOPEN_MAX 16"
.LASF530:
	.string	"_IO_HEX 0100"
.LASF96:
	.string	"__INT_LEAST32_MAX__ 2147483647"
.LASF17:
	.string	"__SIZEOF_LONG_LONG__ 8"
.LASF44:
	.string	"__UINT8_TYPE__ unsigned char"
.LASF396:
	.string	"__size_t "
.LASF224:
	.string	"__SSE2_MATH__ 1"
.LASF414:
	.string	"__S64_TYPE long int"
.LASF335:
	.string	"__attribute_pure__ __attribute__ ((__pure__))"
.LASF570:
	.string	"L_tmpnam 20"
.LASF261:
	.string	"__USE_MISC"
.LASF478:
	.string	"_IO_off_t __off_t"
.LASF287:
	.string	"__USE_XOPEN2K8 1"
.LASF319:
	.string	"__END_NAMESPACE_C99 "
.LASF272:
	.string	"_BSD_SOURCE 1"
.LASF30:
	.string	"__SIZEOF_POINTER__ 8"
.LASF591:
	.string	"string.c"
.LASF485:
	.string	"_IO_va_list _G_va_list"
.LASF269:
	.string	"_DEFAULT_SOURCE"
.LASF424:
	.string	"__INO64_T_TYPE __UQUAD_TYPE"
.LASF487:
	.string	"__need___va_list "
.LASF519:
	.string	"_IO_BAD_SEEN 0x4000"
.LASF72:
	.string	"__WCHAR_MAX__ 2147483647"
.LASF325:
	.string	"__warnattr(msg) __attribute__((__warning__ (msg)))"
.LASF82:
	.string	"__SIG_ATOMIC_MAX__ 2147483647"
.LASF463:
	.string	"_G_config_h 1"
.LASF202:
	.string	"__GCC_ATOMIC_POINTER_LOCK_FREE 2"
.LASF439:
	.string	"__ID_T_TYPE __U32_TYPE"
.LASF574:
	.string	"FOPEN_MAX"
.LASF593:
	.string	"main"
.LASF429:
	.string	"__OFF64_T_TYPE __SQUAD_TYPE"
.LASF441:
	.string	"__TIME_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF588:
	.string	"sizetype"
.LASF241:
	.string	"__USE_ISOC11"
.LASF581:
	.string	"long unsigned int"
.LASF437:
	.string	"__FSFILCNT_T_TYPE __SYSCALL_ULONG_TYPE"
.LASF195:
	.string	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 2"
.LASF365:
	.string	"__stub_chflags "
.LASF229:
	.string	"__unix 1"
.LASF89:
	.string	"__UINT16_MAX__ 65535"
.LASF506:
	.string	"_IO_UNBUFFERED 2"
.LASF440:
	.string	"__CLOCK_T_TYPE __SYSCALL_SLONG_TYPE"
.LASF214:
	.string	"__ATOMIC_HLE_ACQUIRE 65536"
.LASF477:
	.string	"_IO_ssize_t __ssize_t"
.LASF1:
	.string	"__STDC_HOSTED__ 1"
.LASF362:
	.string	"__REDIRECT_LDBL(name,proto,alias) __REDIRECT (name, proto, alias)"
.LASF548:
	.string	"_IO_peekc_unlocked(_fp) (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) && __underflow (_fp) == EOF ? EOF : *(unsigned char *) (_fp)->_IO_read_ptr)"
.LASF307:
	.string	"__P(args) args"
.LASF474:
	.string	"_IO_fpos_t _G_fpos_t"
.LASF408:
	.string	"__SQUAD_TYPE long int"
.LASF253:
	.string	"__USE_XOPEN2KXSI"
.LASF76:
	.string	"__PTRDIFF_MAX__ 9223372036854775807L"
.LASF486:
	.string	"_IO_wint_t wint_t"
.LASF470:
	.string	"_G_HAVE_MREMAP 1"
.LASF297:
	.string	"__GLIBC__ 2"
.LASF125:
	.string	"__FLT_MAX_EXP__ 128"
.LASF351:
	.string	"__restrict_arr __restrict"
.LASF10:
	.string	"__ATOMIC_ACQ_REL 4"
.LASF117:
	.string	"__UINTPTR_MAX__ 18446744073709551615UL"
.LASF341:
	.string	"__attribute_format_strfmon__(a,b) __attribute__ ((__format__ (__strfmon__, a, b)))"
.LASF582:
	.string	"unsigned char"
.LASF569:
	.string	"P_tmpdir \"/tmp\""
.LASF536:
	.string	"_IO_FIXED 010000"
.LASF43:
	.string	"__INT64_TYPE__ long int"
.LASF415:
	.string	"__U64_TYPE unsigned long int"
.LASF523:
	.string	"_IO_FLAGS2_USER_WBUF 8"
.LASF495:
	.string	"_IOS_OUTPUT 2"
.LASF364:
	.string	"__stub_bdflush "
.LASF222:
	.string	"__FXSR__ 1"
.LASF303:
	.string	"__LEAF_ATTR __attribute__ ((__leaf__))"
.LASF52:
	.string	"__UINT_LEAST8_TYPE__ unsigned char"
.LASF387:
	.string	"_SIZE_T_ "
.LASF418:
	.string	"__SYSCALL_SLONG_TYPE __SLONGWORD_TYPE"
.LASF560:
	.string	"__off_t_defined "
.LASF50:
	.string	"__INT_LEAST32_TYPE__ int"
.LASF164:
	.string	"__DEC32_MIN_EXP__ (-94)"
.LASF549:
	.string	"_IO_putc_unlocked(_ch,_fp) (_IO_BE ((_fp)->_IO_write_ptr >= (_fp)->_IO_write_end, 0) ? __overflow (_fp, (unsigned char) (_ch)) : (unsigned char) (*(_fp)->_IO_write_ptr++ = (_ch)))"
.LASF130:
	.string	"__FLT_EPSILON__ 1.19209289550781250000e-7F"
.LASF539:
	.string	"_IO_DONT_CLOSE 0100000"
.LASF217:
	.string	"__k8__ 1"
.LASF421:
	.string	"__UID_T_TYPE __U32_TYPE"
.LASF407:
	.string	"__ULONGWORD_TYPE unsigned long int"
.LASF149:
	.string	"__LDBL_MANT_DIG__ 64"
.LASF277:
	.string	"_POSIX_SOURCE 1"
.LASF250:
	.string	"__USE_XOPEN_EXTENDED"
.LASF257:
	.string	"__USE_LARGEFILE64"
.LASF475:
	.string	"_IO_fpos64_t _G_fpos64_t"
.LASF467:
	.string	"__need_wint_t"
.LASF147:
	.string	"__DBL_HAS_INFINITY__ 1"
.LASF104:
	.string	"__UINT_LEAST32_MAX__ 4294967295U"
.LASF314:
	.string	"__END_DECLS "
.LASF255:
	.string	"__USE_XOPEN2K8XSI"
.LASF32:
	.string	"__PTRDIFF_TYPE__ long int"
.LASF57:
	.string	"__INT_FAST16_TYPE__ long int"
.LASF235:
	.string	"__STDC_IEC_559__ 1"
.LASF183:
	.string	"__DEC128_SUBNORMAL_MIN__ 0.000000000000000000000000000000001E-6143DL"
.LASF338:
	.string	"__attribute_noinline__ __attribute__ ((__noinline__))"
.LASF460:
	.string	"__need___FILE"
.LASF256:
	.string	"__USE_LARGEFILE"
.LASF274:
	.string	"_SVID_SOURCE 1"
.LASF585:
	.string	"signed char"
.LASF259:
	.string	"__USE_BSD"
.LASF484:
	.string	"_IO_BUFSIZ _G_BUFSIZ"
.LASF140:
	.string	"__DBL_MAX_10_EXP__ 308"
.LASF290:
	.string	"__USE_MISC 1"
.LASF583:
	.string	"short unsigned int"
.LASF197:
	.string	"__GCC_ATOMIC_SHORT_LOCK_FREE 2"
.LASF220:
	.string	"__SSE__ 1"
.LASF507:
	.string	"_IO_NO_READS 4"
.LASF24:
	.string	"__BIGGEST_ALIGNMENT__ 16"
.LASF395:
	.string	"_SIZET_ "
.LASF368:
	.string	"__stub_fdetach "
.LASF383:
	.string	"_SYS_SIZE_T_H "
.LASF144:
	.string	"__DBL_EPSILON__ ((double)2.22044604925031308085e-16L)"
.LASF35:
	.string	"__INTMAX_TYPE__ long int"
.LASF123:
	.string	"__FLT_MIN_EXP__ (-125)"
.LASF181:
	.string	"__DEC128_MAX__ 9.999999999999999999999999999999999E6144DL"
.LASF232:
	.string	"__ELF__ 1"
.LASF326:
	.string	"__errordecl(name,msg) extern void name (void) __attribute__((__error__ (msg)))"
.LASF538:
	.string	"_IO_STDIO 040000"
.LASF450:
	.string	"__SSIZE_T_TYPE __SWORD_TYPE"
.LASF546:
	.string	"_IO_BE(expr,res) __builtin_expect ((expr), res)"
.LASF331:
	.string	"__ASMNAME(cname) __ASMNAME2 (__USER_LABEL_PREFIX__, cname)"
.LASF210:
	.string	"__amd64 1"
.LASF490:
	.string	"_IO_va_list"
.LASF227:
	.string	"__linux__ 1"
.LASF355:
	.string	"__WORDSIZE_TIME64_COMPAT32 1"
.LASF573:
	.string	"L_ctermid 9"
.LASF500:
	.string	"_IOS_NOREPLACE 64"
.LASF273:
	.string	"_SVID_SOURCE"
.LASF468:
	.string	"_G_va_list __gnuc_va_list"
.LASF216:
	.string	"__k8 1"
.LASF63:
	.string	"__UINT_FAST64_TYPE__ long unsigned int"
.LASF376:
	.string	"__stub_sstk "
.LASF266:
	.string	"__KERNEL_STRICT_NAMES"
.LASF154:
	.string	"__LDBL_MAX_10_EXP__ 4932"
.LASF173:
	.string	"__DEC64_MIN__ 1E-383DD"
.LASF491:
	.string	"_IO_va_list __gnuc_va_list"
.LASF497:
	.string	"_IOS_APPEND 8"
.LASF231:
	.string	"unix 1"
.LASF204:
	.string	"__PRAGMA_REDEFINE_EXTNAME 1"
.LASF39:
	.string	"__SIG_ATOMIC_TYPE__ int"
.LASF245:
	.string	"__USE_POSIX"
.LASF191:
	.string	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1"
.LASF516:
	.string	"_IO_CURRENTLY_PUTTING 0x800"
.LASF356:
	.string	"__SYSCALL_WORDSIZE 64"
.LASF160:
	.string	"__LDBL_HAS_DENORM__ 1"
.LASF432:
	.string	"__RLIM64_T_TYPE __UQUAD_TYPE"
.LASF380:
	.string	"__size_t__ "
.LASF170:
	.string	"__DEC64_MANT_DIG__ 16"
.LASF132:
	.string	"__FLT_HAS_DENORM__ 1"
.LASF361:
	.string	"__LDBL_REDIR_DECL(name) "
.LASF155:
	.string	"__DECIMAL_DIG__ 21"
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
