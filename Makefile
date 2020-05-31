C = gcc
compile_flag = -Wall -c
debug_compile_flag = -O0 -g -Wall -c
lib = -lncurses
include_local_lib = -I ./src -I ./ctest

all: clean Main.o Curses.o Func.o
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

.PHONY: clean debug test

debug: clean Main.od Curses.od Func.od
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

test: clean TMain.o Curses.o Func.o
	$(C) ./build/src/*.o ./build/test/*.o -o ./bin/test $(lib)
	cp ./src/translate.txt ./bin/

clean:
	rm -rf ./build/*.o ./build/src/*.o

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/src/main.o

Main.od:
	$(C) $(debug_compile_flag) ./src/main.c -o ./build/src/main.o

TMain.o:
	$(C) $(include_local_lib) $(compile_flag) ./test/main.c -o ./build/test/main.o

Curses.o:
	$(C) $(compile_flag) ./src/curses.c -o ./build/src/curses.o

Curses.od:
	$(C) $(debug_compile_flag) ./src/curses.c -o ./build/src/curses.o

Func.o:
	$(C) $(compile_flag) ./src/func.c -o ./build/src/func.o

Func.od:
	$(C) $(debug_compile_flag) ./src/func.c -o ./build/src/func.o
