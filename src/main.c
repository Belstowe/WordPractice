#include <stdio.h>
#include <string.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include "curses.h"
#include "func.h"

size_t wordnum = 0; //Количество слов в списке
size_t tasks = 10; //Количество "номеров" в задании
char* filename; //Название файла со списком

/*
* Приложение имеет опциональный аргумент для названия файла с переводами.
* Например, пользователь пишет "./wrdprct eng.txt".
* В данном случае:
* argv[0] = "wrdprct" (название программы).
* argv[1] = "eng.txt" (название файла с переводами; если этого аргумента нет, будет выбран файл "translate.txt").
*/
int main(int argc, char* argv[])
{
	if (argc >= 2) {
		if (strstr(argv[1], ".txt\0"))
			filename = argv[1];
		else if (!strcmp(argv[1], "help\0") || (!strcmp(argv[1], "h\0"))) {
			printf("Использование:\n"\
				   "$ ./wrdprct [filename.txt]\n"\
				   "Если название файла не указано, будет использован стандартный файл 'translate.txt'.\n");
			return 0;
		}
		else {
			printf("Ошибка в аргументе с названием файла. Он должен быть типа файла 'txt'.\n");
			return -1;
		}
	}
	else
		filename = "translate.txt";

	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		printf("ОШИБКА. Проблемы с доступом к файлу '%s'. Существует ли он вообще?\n",filename);
		return -1;
	}
	fclose(f);

    
    setlocale(LC_ALL, "");
    initscr();
    scrollok(stdscr, TRUE);
    int item;
    int lvl = 0;
    int var = 0;
    while (1) {
	Menu(&item);
	if (item == 1) Play(&lvl, &var);
	if (item == 2) {
	    endwin();
	    return 0;
	}
    }

    return 0;
}