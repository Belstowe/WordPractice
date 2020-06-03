#include "menus.h"

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* filename; //Название файла со списком

/*
 * Приложение имеет опциональный аргумент для названия файла с переводами.
 * Например, пользователь пишет "./wrdprct eng.txt".
 * В данном случае:
 * argv[0] = "wrdprct" (название программы).
 * argv[1] = "eng.txt" (название файла с переводами; если этого аргумента нет,
 * будет выбран файл "translate.txt").
 */
int main(int argc, char* argv[])
{
    if (argc >= 2) {
        if (strstr(argv[1], ".txt\0"))
            filename = argv[1];
        else if (!strcmp(argv[1], "help\0") || (!strcmp(argv[1], "h\0"))) {
            printf("Использование:\n"
                   "$ ./wrdprct [filename.txt]\n"
                   "Если название файла не указано, будет использован "
                   "стандартный файл 'translate.txt'.\n");
            return 0;
        } else {
            printf("Ошибка в аргументе с названием файла. Он должен быть типа "
                   "файла 'txt'.\n");
            return -1;
        }
    } else
        filename = "translate.txt";

    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("ОШИБКА. Проблемы с доступом к файлу '%s'. Существует ли он "
               "вообще?\n",
               filename);
        return -1;
    }
    fclose(f);

    srand(time(0));
    setlocale(LC_ALL, "");
    initscr();
    scrollok(stdscr, TRUE);

    menu_call(Main);

    endwin();
    return 0;
}