C = gcc
compile_flag = -Wall -c
debug_compile_flag = -O0 -g -Wall -c
lib = -lncurses

all: clean Main.o Curses.o Func.o
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

.PHONY: clean debug

debug: clean Main.od Curses.od Func.od
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

clean:
	rm -rf ./build/*.o ./build/src/*.o

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/src/main.o

Main.od:
	$(C) $(debug_compile_flag) ./src/main.c -o ./build/src/main.o

Curses.o:
	$(C) $(compile_flag) ./src/curses.c -o ./build/src/curses.o

Curses.od:
	$(C) $(debug_compile_flag) ./src/curses.c -o ./build/src/curses.o

Func.o:
	$(C) $(compile_flag) ./src/func.c -o ./build/src/func.o

Func.od:
	$(C) $(debug_compile_flag) ./src/funcn.c -o ./build/src/func.o