C = gcc
compile_flag = -Wall -c
debug_compile_flag = -O0 -g -Wall -c
lib = -lncursesw
include_local_lib = -I ./src -I ./ctest

all: clean Main.o Menus.o Func.o Ui.o
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

.PHONY: clean debug test

debug: clean Main.od Menus.od Func.od Ui.od
	$(C) ./build/src/*.o -o ./bin/wrdprct $(lib)
	cp ./src/translate.txt ./bin/

test: clean TMain.o Menus.o Func.o TFunc.o Ui.o TUi.o
	$(C) ./build/src/*.o ./build/test/*.o -o ./bin/test $(lib)
	cp ./src/translate.txt ./
	./bin/test
	rm -f ./bin/test translate.txt

clean:
	rm -rf ./build/*.o ./build/src/*.o

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/src/main.o

Main.od:
	$(C) $(debug_compile_flag) ./src/main.c -o ./build/src/main.o

TMain.o:
	$(C) $(include_local_lib) $(compile_flag) ./test/main.c -o ./build/test/main.o

Menus.o:
	$(C) $(compile_flag) ./src/menus.c -o ./build/src/menus.o

Menus.od:
	$(C) $(debug_compile_flag) ./src/menus.c -o ./build/src/menus.o

Func.o:
	$(C) $(compile_flag) ./src/func.c -o ./build/src/func.o

Func.od:
	$(C) $(debug_compile_flag) ./src/func.c -o ./build/src/func.o

TFunc.o:
	$(C) $(include_local_lib) $(compile_flag) ./test/t_func.c -o ./build/test/t_func.o

Ui.o:
	$(C) $(compile_flag) ./src/ui.c -o ./build/src/ui.o

Ui.od:
	$(C) $(debug_compile_flag) ./src/ui.c -o ./build/src/ui.o

TUi.o:
	$(C) $(include_local_lib) $(compile_flag) ./test/t_ui.c -o ./build/test/t_ui.o