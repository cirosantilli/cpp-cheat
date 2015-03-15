EXT ?= f
RUN ?= main

.PROXY: clean run

main: $(RUN).$(EXT)
	gfortran -o '$(RUN)' '$(RUN).$(EXT)'

clean:
	rm '$(RUN)'

run: $(RUN)
	./'$(RUN)'
