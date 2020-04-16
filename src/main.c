#include <stdio.h>
#include <string.h>
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

    int k = check();
    printf("\nРезультат:\t %d/%zu.\n", k, tasks);

    return 0;
}