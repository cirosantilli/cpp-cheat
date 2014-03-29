" Used on directories that compile files individually (e.g. c.c -> c and cpp.cpp -> cpp)
" <F5>: compile all
" <F6>: compile and run the current file

function! RedirStdoutNewTabSingle(cmd)
	tabnext
	if expand('%:p') != ""
		tabprevious
		execute "tabnew"
		setlocal buftype=nofile
		setlocal bufhidden=wipe
		setlocal noswapfile
	endif
	%delete
	execute "silent read !" . a:cmd
	set nomodified
endfunction

function! MapAllBuff(keys, rhs)
    exe 'noremap <buffer>' a:keys a:rhs
    exe 'noremap! <buffer>' a:keys '<ESC>'.a:rhs
endfunction

call MapAllBuff( '<F5>'  , ':w<CR>:make<CR>' )
if expand('%:e') =~ '\(c\|cpp\|f\)'
	call MapAllBuff( '<F6>'  , ':call RedirStdoutNewTabSingle("make run=''\"' . expand('%:r')  . '\"''")<CR>' )
	call MapAllBuff( '<F9>'  , ':call RedirStdoutNewTabSingle("make profile=''\"' . expand('%:r')  . '\"''")<CR>' )
else
	call MapAllBuff( '<F6>'  , ':call RedirStdoutNewTabSingle("make run")<CR>' )
	call MapAllBuff( '<F9>'  , ':w<CR>:call RedirStdoutNewTabSingle("make profile")<CR>' )
endif
