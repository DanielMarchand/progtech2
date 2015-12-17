EPATH = ../extern/pyutil/
PYSO = boostpy_random.so

.PHONY: all clean

all:
	make --directory $(EPATH)
	ln -fs ../$(EPATH)$(PYSO) util/

clean:
	rm util/$(PYSO)
	make --directory $(EPATH) clean
