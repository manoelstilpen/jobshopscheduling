all: 
	$(MAKE) $@ -f Makefile.src

.PHONY : debug
debug:
	$(MAKE) $@ -f Makefile.debug

.PHONY : clean
clean:
	make clean -f Makefile.src
	make clean -f Makefile.debug