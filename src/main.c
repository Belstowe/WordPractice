#include "default.h"
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

    char auto_gen_flag = false; // Флаг проставляемый, когда вместо
                                // существующего генерируется шаблонный список
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        if (argc == 1) { //Если не указывался файл, то создаем свой
            f = fopen(filename, "w");
            if (f == NULL) { //Если доступа нет
                printf("Ошибка при генерации шаблонного списка");
                return -1;
            }
            fprintf(f, "%s", default_list); // Берем стандартный список из
                                            // default.h и записываем
            auto_gen_flag = true;
        } else {
            printf("ОШИБКА. Проблемы с доступом к файлу '%s'. Существует ли он "
                   "вообще?\n",
                   filename);
            return -1;
        }
    }
    fclose(f);

    srand(time(0)); // Инициализация рандомизатора
    setlocale(LC_ALL, ""); // Установка системного языка
    initscr(); // Инициализация окна консоли для работы Ncurses
    scrollok(stdscr, TRUE); // Допускаем выход указателя за пределы окна консоли

    menu_call(Main); // Вызываем главное меню

    if (auto_gen_flag) // Удаляем сгенерированный файл
        remove(filename);
    endwin(); // После выхода из цикла меню переходим в обычный режим работы с
              // консолью и выходим
    return 0;
}