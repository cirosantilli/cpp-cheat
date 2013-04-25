generates parsers.

flex/bison are open source clones of lex/yacc

ubuntu install:

    sudo aptitude install -y flex
    sudo aptitude install -y flex-doc
    sudo aptitude install -y bison
    sudo aptitude install -y bison-doc

##sources

- very good intro source: [Tom Niemann - Lex & Yacc Tutorial](http://epaperpress.com/lexandyacc/)

##flex

    #formal regex to tokens
    
    #why it works well with bison:
    
        #this step is O(n)
        
        #the bison naive algorithm is O(n^3) ( assymptotic O(n^2.40) and falling )

##bison

    #parses deterministic context free languages (aka deterministic LR)
    #subset of context-free, superset of regex
