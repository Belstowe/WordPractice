#include "func.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern size_t wordnum, tasks;

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
        if (j != i) {
            temp_arr[j] += temp_arr[i];
            temp_arr[i] = temp_arr[j] - temp_arr[i];
            temp_arr[j] -= temp_arr[i];
        }
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

    while (fscanf(f, "%s %s", nulwords->translate_from, nulwords->translate_to)
           == 2)
        wordnum++;

    fclose(f);
}

/* file_word_pairs_read
 * Читает пары слов из списка и заносит их в массив пар слов words.
 */
void file_word_pairs_read(char* IFILE, Words* words)
{
    FILE* f;
    if ((f = fopen(IFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    for (size_t i = 0; i < wordnum; i++)
        fscanf(f,
               "%s %s",
               ((words[i]).translate_from),
               ((words[i]).translate_to));

    fclose(f);
}

/* wordlist_form
 * Формирует список пар слов с помощью file_word_pairs_read и
 * file_word_pairs_count, возвращая указатель на него.
 */
Words* wordlist_form(char* IFILE, int** order)
{
    file_word_pairs_count(IFILE);
    Words* wordlist = malloc(wordnum * sizeof(Words));
    (*order) = random_order(0, wordnum - 1);
    file_word_pairs_read(IFILE, wordlist);

    return wordlist;
}