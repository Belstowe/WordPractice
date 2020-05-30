#include "curses.h"
#include <ncursesw/curses.h>

#include "func.h"
#include <locale.h>

void Play(int* lvl, int* var)
{
    if (*lvl == 0)
        Difficult(&*lvl);
    if (*var == 0)
        Variant(&*var);
    if (*var == 1)
        eng(&*lvl, &*var);
    if (*var == 2)
        rus(&*lvl, &*var);
}

void Variant(int* var)
{
    char tmp;
    clear();
    *var = 0;
    printw("1. С английского на русский.\n"
           "2. С русского на английский.\n"
           "Для выбора введите нужную цифру.\n ");

    do {
        tmp = getch();
    } while (tmp < '1' || tmp > '2');
    *var = tmp - '0';
    printw("%d", *var);

    clear();
}

void Difficult(int* lvl)
{
    char tmp;
    clear();
    *lvl = 0;
    printw("Вы можете выбрать количество слов для тренировки\n");
    printw("\t\t1. 10 слов\n");
    printw("\t\t2. 15 слов\n");
    printw("\t\t3. 20 слов\n");
    printw("Введите цифру варианта: ");
    do {
        tmp = getch();
    } while (tmp < '1' || tmp > '3');
    *lvl = 5 + 5 * (tmp - '0');
    clear();
}

void Menu(int* item)
{
    char tmp;
    clear();

    *item = 0;
    printw("\t\t  МЕНЮ\n");
    printw("Добро пожаловать в Word Practice, программу для заучивания "
           "иноязычных слов\n\n"
           "Выберите :\n");
    printw("\t\t1. Начать!.\n");
    printw("\t\t2. Выход\n");
    do {
        tmp = getch();
    } while (tmp < '1' || tmp > '2');
    *item = tmp - '0';
    clear();
}
