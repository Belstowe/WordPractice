#include "curses.h"
#include "func.h"

#include <ncurses.h>
#include <string.h>

extern char* filename;
int iterations = 0; // Количество "номеров" в задании
int* order;
enum Menu gamemode = Exit;

void menu_call_result(unsigned correct_answers)
{
    printw("Правильных ответов всего: %d/%d.\n", correct_answers, iterations);
    getch();
    menu_call(Main);
}

unsigned menu_call_type_en_to_ru(unsigned iter, Words* wordlist)
{
    if (iter == iterations)
        return 0;

    unsigned is_correct = 0;
    const int index = order[iter];

    char input[MAX_STRING_SIZE];

    printw("\n%d:\t %s\n", iter + 1, wordlist[index].translate_from);
    printw("Введите перевод на русский:\t ");
    scanw("%s", input);

    if (strcmp(input, wordlist[index].translate_to))
        printw("НЕВЕРНО.\n"
               "Правильно: %s.\n",
               wordlist[index].translate_to);
    else {
        printw("ВЕРНО.\n");
        is_correct = 1;
    }
    getch();

    clear();
    return is_correct + menu_call_type_en_to_ru(iter + 1, wordlist);
}

unsigned menu_call_type_ru_to_en(unsigned iter, Words* wordlist)
{
    if (iter == iterations)
        return 0;

    unsigned is_correct = 0;
    const int index = order[iter];

    char input[MAX_STRING_SIZE];

    printw("\n%d:\t %s\n", iter + 1, wordlist[index].translate_to);
    printw("Введите перевод на английский:\t ");
    scanw("%s", input);

    if (strcmp(input, wordlist[index].translate_from))
        printw("НЕВЕРНО.\n"
               "Правильно: %s.\n",
               wordlist[index].translate_from);
    else {
        printw("ВЕРНО.\n");
        is_correct = 1;
    }
    getch();

    clear();
    return is_correct + menu_call_type_en_to_ru(iter + 1, wordlist);
}

void menu_call_difficulty()
{
    char pick;

    printw("Вы можете выбрать количество слов для тренировки\n");
    printw("\t\t1. 10 слов\n");
    printw("\t\t2. 15 слов\n");
    printw("\t\t3. 20 слов\n");
    printw("Введите цифру варианта: ");

    do {
        pick = getch();
    } while (pick < '1' || pick > '3');

    iterations = (pick - '1') * 5 + 10;
    menu_call(gamemode);
}

void menu_call_variant()
{
    char pick;

    printw("1. С английского на русский.\n"
           "2. С русского на английский.\n"
           "Для выбора введите нужную цифру.\n");

    do {
        pick = getch();
    } while (pick < '1' || pick > '2');

    if (pick == '1')
        gamemode = ModeEnToRu;
    else
        gamemode = ModeRuToEn;

    menu_call(Difficulty);
}

void menu_call_main()
{
    char pick;

    printw("\t\t  МЕНЮ\n");
    printw("Добро пожаловать в Word Practice, программу для заучивания "
           "иноязычных слов\n\n"
           "Выберите :\n");
    printw("\t\t1. Начать!.\n");
    printw("\t\t2. Выход\n");

    do {
        pick = getch();
    } while (pick < '1' || pick > '2');

    if (pick == '1')
        menu_call(Variant);
}

void menu_call(enum Menu menu_type)
{
    clear();
    switch (menu_type) {
    case Main:
        menu_call_main();
        break;

    case Variant:
        menu_call_variant();
        break;

    case Difficulty:
        menu_call_difficulty();
        break;

    case ModeEnToRu:
        menu_call_result( menu_call_type_en_to_ru(0, wordlist_form(filename, &order)) );
        break;

    case ModeRuToEn:
        menu_call_result( menu_call_type_ru_to_en(0, wordlist_form(filename, &order)) );
        break;

    default:
        break;
    }
    clear();
}