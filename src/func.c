#define MAX_STRING_SIZE 256

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "func.h"

extern char* filename;
extern size_t wordnum, tasks;

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

/* random_order
* Создаёт массив упорядоченных натуральных чисел от min по max, затем разбрасывает эти числа случайным образом.
* Возвращает получившийся массив размером (max - min + 1).
? Используется, чтобы избежать повторений в выборе элементов.
! max обязательно должен быть больше min, иначе функция вернёт NULL.
*/
int* random_order(const int min, const int max) {
    if (max - min <= 0)
        return NULL;

    const size_t range = max - min + 1;
    int* temp_arr = malloc(range*sizeof(int));
    if (temp_arr == NULL)
        return NULL;

    for (uint32_t i = 0; i < range; i++)
        temp_arr[i] = min + i;

    for (uint32_t i = 0; i < range - 1; i++) {
        uint32_t j = (uint32_t)getrand(i, range);
        temp_arr[j] += temp_arr[i];
        temp_arr[i] = temp_arr[j] - temp_arr[i];
        temp_arr[j] -= temp_arr[i];
    }

    return temp_arr;
}

typedef struct {
    char first[MAX_STRING_SIZE];
    char second[MAX_STRING_SIZE];
} Words;

void word_count(char* IFILE) {
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
};

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
            printf("ВЕРНО.\n");
        } else
            printf("НЕВЕРНО.\n"\
                   "Правильно: %s.\n",w[i].second);
    }
    if (q == 2) {
        if (strcmp(mass, w[i].first) == 0) {
            k++;
            printf("ВЕРНО.\n");
        } else
            printf("НЕВЕРНО.\n"\
                   "Правильно: %s.\n",w[i].first);
    }

    return k;
}

int check()
{
    int q, k = 0;
    printf("Добро пожаловать в Word Practice, программу для заучивания иноязычных слов!\n\n"\
           "Выберите:\n"\
           "1. С английского на русский.\n"\
           "2. С русского на английский.\n"\
           "Для выбора введите нужную цифру.\n"\
           "Если вы ошиблись программой или хотите что-то исправить, выйдите из программы, введя любой другой символ.\n");
    if (scanf("%d", &q) == 0)
        return 0;
    else if ((q > 2) || (q == 0))
        return 0;

    srand(time(0));
    char input[MAX_STRING_SIZE];
    word_count(filename);
    Words w[wordnum];
    read_words(filename, w);

    if (q == 1) {
        printf("Количество слов в списке: %zu.\n"\
               "Введите количество номеров (либо нажмите Enter, чтобы пройти все слова в списке): ",\
               wordnum);
        if (scanf("%zu",&tasks) == 0)
            tasks = wordnum;
        else if (tasks > wordnum) {
            printf("ОШИБКА: Вы не можете указать количество попыток выше количества слов!\n");
            return 0;
        }

        int* list = random_order(0,wordnum-1);
        for (int j = 0; j < tasks; j++) {
            printf("\n%d:\t %s\n", j+1, w[list[j]].first);
            printf("Введите перевод на русский:\t ");
            scanf("%s", input);
            k += sum(input, list[j], w, q);
        }
    }
    if (q == 2) {
        printf("Количество слов в списке: %zu.\n"\
               "Введите количество номеров (либо нажмите Enter, чтобы пройти все слова в списке): ",\
               wordnum);
        if (scanf("%zu",&tasks) == 0)
            tasks = wordnum;
        else if (tasks > wordnum) {
            printf("ОШИБКА: Вы не можете указать количество попыток выше количества слов!\n");
            return 0;
        }

        int* list = random_order(0,wordnum-1);
        for (int j = 0; j < tasks; j++) {
            printf("\n%d:\t %s\n", j+1, w[list[j]].second);
            printf("Введите перевод на английский:\t ");
            scanf("%s", input);
            k += sum(input, list[j], w, q);
        }
    }
  
    return k;
}