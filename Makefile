C = gcc
flag = -Wall -o

all:
	mkdir -p bin
	$(C) $(flag) ./bin/result ./src/*.c
	cp ./src/translate.txt ./bin/