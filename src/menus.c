#include "menus.h"
#include "func.h"
#include "ui.h"
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define MIN_WIDTH 40
#define MIN_HEIGHT 15

extern char* filename;
int iterations = 0; // Количество "номеров" в задании
int* order;
enum Menu gamemode = Exit;

/* menu_call_resolution
 * Меню просьбы сменить разрешение, если оно меньше требуемого.
 */
void menu_call_resolution(enum Menu pending_menu)
{
    char resolution_beg[]
            = "Пожалуйста, смените разрешение на более высокое, затем нажмите "
              "любую клавишу, чтобы продолжить.";

    border_print(
            resolution_beg, 0, 0, getmaxy(stdscr), getmaxx(stdscr), 'c', 'c');

    curs_set(0);
    getch();
    menu_call(pending_menu);
}

/* menu_call_type_testing
 * Меню игры - выбор правильного ответа из четырех вариантов.
 * Рекурсивная функция, которая вызывает себя ровно указанное количество
 * итераций.
 * Возвращает количество правильных результатов.
 */

unsigned menu_call_type_testing(unsigned iter, Words* wordlist, int wordnum)
{
    if (iter == iterations)
	return 0;

    unsigned is_correct = 0;
    const int index = order[iter];
    int*  massive;

    if ( index < (wordnum -3))
	massive = random_order(index,index+3);
    else massive =random_order(index-3,index);

    char input[MAX_STRING_SIZE];
     char translation1[MAX_STRING_SIZE + 64];
    sprintf(translation1, "%d:\n%s", iter + 1, wordlist[index].translate_from);

    char translation2[]="Выберите номер правильного перевода:\t ";

    border_print(
            translation1,
            valign('c', getmaxy(stdscr), 0, 15),
            0,
            valign('c', getmaxy(stdscr), 5, 15),
            getmaxx(stdscr),
            'c',
            'b');
    border_print(
            translation2,
            valign('c', getmaxy(stdscr), 6, 15),
            0,
            valign('c', getmaxy(stdscr), 8, 15),
            getmaxx(stdscr),
            'c',
            'b');

//    move(valign('c', getmaxy(stdscr), 9, 15),
//         halign(translation2, 'c', getmaxx(stdscr) + 1));

    int right_answer=-1;
    int t=9;
    for (int i = 1; i <5 ;i++){
	move(valign('c', getmaxy(stdscr), t, 15),
            halign(translation2, 'c', getmaxx(stdscr)+1));
		  t++;

        printw("%d. %s" ,i, wordlist[*massive].translate_to);
	if (*massive == index)
	    right_answer = i;
	massive=massive+1;

}
    move(valign('c', getmaxy(stdscr), 13, 15),
            halign(translation2, 'c', getmaxx(stdscr)+1));

    scanw("%s", input);

    char translation_correct[] = "ВЕРНО.";
    char translation_incorrect[] = "НЕВЕРНО.";

    if (atoi(input)==right_answer){
	is_correct = 1;
	border_print(
                translation_correct,
                valign('c', getmaxy(stdscr), 14, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');

    }    else {
	border_print(
                translation_incorrect,
                valign('c', getmaxy(stdscr), 14, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');
    }

    getch();

    clear();

    return is_correct + menu_call_type_testing(iter + 1, wordlist, wordnum);
}


/* menu_call_result
 * Меню отображения результата. На вход принимает число правильных результатов.
 */
void menu_call_result(unsigned correct_answers)
{
    char result[MAX_STRING_SIZE];
    sprintf(result,
            "Правильных ответов всего:\n%d/%d.\n",
            correct_answers,
            iterations);

    border_print(
            result,
            valign('c', getmaxy(stdscr), 5, 15),
            0,
            valign('c', getmaxy(stdscr), 10, 15),
            getmaxx(stdscr),
            'c',
            'c');

    curs_set(0);
    getch();
    menu_call(Main);
}

/* menu_call_type_en_to_ru
 * Меню игры на перевод с английского на русский.
 * Рекурсивная функция, которая вызывает себя ровно указанное количество
 * итераций.
 * Возвращает количество правильных результатов.
 */
unsigned menu_call_type_en_to_ru(unsigned iter, Words* wordlist)
{
    if (iter == iterations)
        return 0;

    unsigned is_correct = 0;
    const int index = order[iter];

    char translation1[MAX_STRING_SIZE + 64];
    sprintf(translation1, "%d:\n%s", iter + 1, wordlist[index].translate_from);

    char translation2[] = "Введите перевод на русский: ";

    char translation_correct[] = "ВЕРНО.";

    char translation_incorrect[MAX_STRING_SIZE + 64];
    sprintf(translation_incorrect,
            "НЕВЕРНО.\nПравильно: %s.",
            wordlist[index].translate_to);

    char input[MAX_STRING_SIZE];

    border_print(
            translation1,
            valign('c', getmaxy(stdscr), 0, 15),
            0,
            valign('c', getmaxy(stdscr), 5, 15),
            getmaxx(stdscr),
            'c',
            'b');
    border_print(
            translation2,
            valign('c', getmaxy(stdscr), 6, 15),
            0,
            valign('c', getmaxy(stdscr), 8, 15),
            getmaxx(stdscr),
            'c',
            'b');

    move(valign('c', getmaxy(stdscr), 9, 15),
         halign(translation2, 'c', getmaxx(stdscr) + 1));
    scanw("%s", input);

    curs_set(0);
    if (strcmp(input, wordlist[index].translate_to))
        border_print(
                translation_incorrect,
                valign('c', getmaxy(stdscr), 12, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');
    else {
        border_print(
                translation_correct,
                valign('c', getmaxy(stdscr), 12, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');
        is_correct = 1;
    }
    getch();

    clear();
    curs_set(1);
    return is_correct + menu_call_type_en_to_ru(iter + 1, wordlist);
}

/* menu_call_type_ru_to_en
 * Меню игры на перевод с русского на английский.
 * Рекурсивная функция, которая вызывает себя ровно указанное количество
 * итераций.
 * Возвращает количество правильных результатов.
 */
unsigned menu_call_type_ru_to_en(unsigned iter, Words* wordlist)
{
    if (iter == iterations)
        return 0;

    unsigned is_correct = 0;
    const int index = order[iter];

    char translation1[MAX_STRING_SIZE + 64];
    sprintf(translation1, "%d:\n%s", iter + 1, wordlist[index].translate_to);

    char translation2[] = "Введите перевод на английский: ";

    char translation_correct[] = "ВЕРНО.";

    char translation_incorrect[MAX_STRING_SIZE + 64];
    sprintf(translation_incorrect,
            "НЕВЕРНО.\nПравильно: %s.",
            wordlist[index].translate_from);

    char input[MAX_STRING_SIZE];

    border_print(
            translation1,
            valign('c', getmaxy(stdscr), 0, 15),
            0,
            valign('c', getmaxy(stdscr), 5, 15),
            getmaxx(stdscr),
            'c',
            'b');
    border_print(
            translation2,
            valign('c', getmaxy(stdscr), 6, 15),
            0,
            valign('c', getmaxy(stdscr), 8, 15),
            getmaxx(stdscr),
            'c',
            'b');

    move(valign('c', getmaxy(stdscr), 9, 15),
         halign(translation2, 'c', getmaxx(stdscr) + 1));
    scanw("%s", input);

    curs_set(0);
    if (strcmp(input, wordlist[index].translate_from))
        border_print(
                translation_incorrect,
                valign('c', getmaxy(stdscr), 12, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');
    else {
        border_print(
                translation_correct,
                valign('c', getmaxy(stdscr), 12, 15),
                0,
                valign('c', getmaxy(stdscr), 15, 15),
                getmaxx(stdscr),
                'c',
                'u');
        is_correct = 1;
    }
    getch();

    clear();
    curs_set(1);
    return is_correct + menu_call_type_ru_to_en(iter + 1, wordlist);
}

/* menu_call_difficulty
 * Меню выбора сложности.
 * Вызывает впоследствии меню игры, в зависимости от выбранного перед этим
 * режима.
 */
void menu_call_difficulty()
{
    char pick;

    char difficulty1[] = "Вы можете выбрать количество слов для тренировки:";
    char difficulty2[]
            = "1. 10 слов;\n"
              "2. 15 слов;\n"
              "3. 20 слов.";
    char difficulty3[] = "Введите цифру варианта.";

    border_print(
            difficulty1,
            valign('c', getmaxy(stdscr), 0, 15),
            0,
            valign('c', getmaxy(stdscr), 5, 15),
            getmaxx(stdscr),
            'c',
            'b');
    border_print(
            difficulty2,
            valign('c', getmaxy(stdscr), 6, 15),
            0,
            valign('c', getmaxy(stdscr), 12, 15),
            getmaxx(stdscr),
            'c',
            'c');
    border_print(
            difficulty3,
            valign('c', getmaxy(stdscr), 13, 15),
            0,
            valign('c', getmaxy(stdscr), 14, 15),
            getmaxx(stdscr),
            'c',
            'u');
    curs_set(0);
    noecho();

    do {
        pick = getch();
    } while (pick < '1' || pick > '3');

    iterations = (pick - '1') * 5 + 10;
    menu_call(gamemode);
}

/* menu_call_variant
 * Меню выбора игрового режима.
 * Устанавливает игровой режим и вызывает впоследствии меню выбора сложности.
 */
void menu_call_variant()
{
    char pick;

    char variant[]
            = "1. С английского на русский.\n"
              "2. С русского на английский.\n"
	      "3. Тестирование\n\n"
              "Для выбора введите нужную цифру.";

    border_print(
            variant,
            valign('c', getmaxy(stdscr), 0, 10),
            0,
            valign('c', getmaxy(stdscr), 9, 10),
            getmaxx(stdscr),
            'c',
            'u');
    curs_set(0);
    noecho();

    do {
        pick = getch();
    } while (pick < '1' || pick > '3');

    if (pick == '1')
        gamemode = ModeEnToRu;
    else if (pick == '2') 
	gamemode = ModeRuToEn;
    else gamemode = ModeTesting;

    menu_call(Difficulty);
}

/* menu_call_main
 * Главное меню.
 * При выборе либо происходит выход из программы, либо вызывается меню выбора
 * игрового режима, от которого затем продолжается работа программы.
 */
void menu_call_main()
{
    char pick;

    char welcome1[]
            = "МЕНЮ\n \n"
              "Добро пожаловать в WordPractice, программу для заучивания "
              "иноязычных слов!";
    char welcome2[]
            = "Выберите:\n"
              "1. Начать!\n"
              "2. Выход.\n";

    border_print(
            welcome1,
            valign('c', getmaxy(stdscr), 0, 15),
            0,
            valign('c', getmaxy(stdscr), 10, 15),
            getmaxx(stdscr),
            'c',
            'c');
    border_print(
            welcome2,
            valign('c', getmaxy(stdscr), 11, 15),
            0,
            valign('c', getmaxy(stdscr), 14, 15),
            getmaxx(stdscr),
            'c',
            'u');
    curs_set(0);
    noecho();

    do {
        pick = getch();
    } while (pick < '1' || pick > '2');

    if (pick == '1')
        menu_call(Variant);
}

/* menu_call
 * Вызов определённого меню с предварительной очисткой экрана.
 */
void menu_call(enum Menu menu_type)
{
    clear();

    curs_set(1);
    echo();

    if ((getmaxx(stdscr) < MIN_WIDTH) || (getmaxy(stdscr) < MIN_HEIGHT)) {
        menu_call_resolution(menu_type);
        return;
    }

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
        menu_call_result(
                menu_call_type_en_to_ru(0, wordlist_form(filename, &order)));
        break;

    case ModeRuToEn:
        menu_call_result(
                menu_call_type_ru_to_en(0, wordlist_form(filename, &order)));
        break;

    case ModeTesting:
	menu_call_result(
	    menu_call_type_testing(0, wordlist_form(filename, &order),
		file_word_pairs_count(filename)));
	break;


    default:
        break;
    }
    clear();
}