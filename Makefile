flags=-O2 -std=c23
ldflags=
util_flags=-O3 -Wall -std=c2x
util_ldflags=-fPIC -shared -ldl

.PHONY: all clean

all: vm.exe

utils.so: utils.o
	cc ${util_flags} $^ -o $@ ${util_ldflags}

utils.o: utils.c utils.h
	cc ${util_flags} -c $^

vm.exe: vm.o
	cc $(flags) $< -o $@ $(ldflags) utils.o 

vm.o: vm.c vm.h
	cc $(flags) -c $<


clean:
	rm -f *.o birchvm


all: clean utils.so
