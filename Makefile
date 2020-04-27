C = gcc
flag = -Wall -o
debug_flag = -O0 -g -Wall -o

all:
	mkdir -p bin
	$(C) $(flag) ./bin/wrdprct ./src/*.c -lncursesw
	$(C) $(debug_flag) ./bin/dwrdprct ./src/*.c -lncursesw
	cp ./src/translate.txt ./bin/