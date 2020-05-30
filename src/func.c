#define MAX_STRING_SIZE 256

#include "func.h"
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

extern char* filename;
extern size_t wordnum, tasks;

typedef struct {
    char first[MAX_STRING_SIZE];
    char second[MAX_STRING_SIZE];
} Words;

/* get_random_int
 * Возвращает целое число в диапазоне от min до max (включая).
 */
int get_random_int(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min + 1) + min;
}

/* random_order
 * Создаёт массив упорядоченных натуральных чисел от min по max, затем
разбрасывает эти числа случайным образом.
 * Возвращает получившийся массив размером (max - min + 1).
 ? Используется, чтобы избежать повторений в выборе элементов.
 ! max обязательно должен быть больше min, иначе функция вернёт NULL.
 */
int* random_order(const int min, const int max)
{
    if (max - min <= 0)
        return NULL;

    const size_t range = max - min + 1;
    int* temp_arr = malloc(range * sizeof(int));
    if (temp_arr == NULL)
        return NULL;

    for (uint32_t i = 0; i < range; i++)
        temp_arr[i] = min + i;

    for (uint32_t i = 0; i < range - 1; i++) {
        uint32_t j = (uint32_t)get_random_int(i, range - 1);
        temp_arr[j] += temp_arr[i];
        temp_arr[i] = temp_arr[j] - temp_arr[i];
        temp_arr[j] -= temp_arr[i];
    }

    return temp_arr;
}

/* file_word_pairs_count
 * Считывает пары слов в списке и записывает их в переменную wordnum.
 */
void file_word_pairs_count(char* IFILE)
{
    wordnum = 0;
    Words* nulwords = malloc(sizeof(Words));
    FILE* f;
    if ((f = fopen(IFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    while (fscanf(f, "%s %s", nulwords->first, nulwords->second) == 2)
        wordnum++;
    fclose(f);
}

void read_words(char* IFILE, Words* w)
{
    FILE* f;
    if ((f = fopen(IFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    for (size_t i = 0; i < wordnum; i++)
        fscanf(f, "%s %s", ((w[i]).first), ((w[i]).second));
    fclose(f);
}

int sum(char* mass, int i, Words* w, int q)
{
    int k = 0;
    if (q == 1) {
        if (strcmp(mass, w[i].second) == 0) {
            k++;
            printw("ВЕРНО.\n");
        } else
            printw("НЕВЕРНО.\n"
                   "Правильно: %s.\n",
                   w[i].second);
    }
    if (q == 2) {
        if (strcmp(mass, w[i].first) == 0) {
            k++;
            printw("ВЕРНО.\n");
        } else
            printw("НЕВЕРНО.\n"
                   "Правильно: %s.\n",
                   w[i].first);
    }

    return k;
}

void eng(int* lvl, int* var)
{
    int q = 1, k = 0;

    srand(time(0));
    char input[MAX_STRING_SIZE];
    file_word_pairs_count(filename);
    Words w[wordnum];
    read_words(filename, w);

    int* list = random_order(0, wordnum - 1);
    for (int j = 0; j < *lvl; j++) {
        printw("\n%d:\t %s\n", j + 1, w[list[j]].first);
        printw("Введите перевод на русский:\t ");
        scanw("%s", input);
        k += sum(input, list[j], w, q);
    }
    printw("\nПравильных слов: %d\n", k);
    getch();
    *lvl = 0;
    *var = 0;
}

void rus(int* lvl, int* var)
{
    int q = 2, k = 0;
    srand(time(0));
    char input[MAX_STRING_SIZE];
    file_word_pairs_count(filename);
    Words w[wordnum];
    read_words(filename, w);

    int* list = random_order(0, wordnum - 1);
    for (int j = 0; j < *lvl; j++) {
        printw("\n%d:\t %s\n", j + 1, w[list[j]].second);
        printw("Input translate on English:\t ");
        scanw("%s", input);
        k += sum(input, list[j], w, q);
    }
    printw("\nПравильных слов: %d\n", k);
    getch();
    *lvl = 0;
    *var = 0;
}
