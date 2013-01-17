if expand('%:e') =~ '\(c\|cpp\)'
  call MapAllBuff( '<F6>'  , ':call RedirStdoutNewTabSingle("make run RUN=''\"' . expand('%:r')  . '\"''")<CR>' )
endif
