if expand('%:e') =~ '\(c\|cpp\)'
  call MapAllBuff( '<F6>'  , ':call RedirStdoutNewTabSingle("make run RUN=''\"' . expand('%:r')  . '\"''")<CR>' )
  "run individual files by basename
else
  call MapAllBuff( '<F5>'  , ':w<CR>:make<CR>' )
  call MapAllBuff( '<F6>'  , ':call RedirStdoutNewTabSingle("make run")<CR>' )
endif
