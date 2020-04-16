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

uint32_t* random_order(size_t num) {
    uint32_t* temp_arr = malloc(num*sizeof(int));
    if (temp_arr == NULL)
        return NULL;

    for (uint32_t i = 0; i < num; i++)
        temp_arr[i] = i;

    for (uint32_t i = 0; i < num - 1; i++) {
        uint32_t j = (uint32_t)getrand(i, num);
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
    printf("Выберите:\n"\
           "1. С английского на русский.\n"\
           "2. С русского на английский.\n"\
           "Для выбора введите нужную цифру.\n"\
           "Если вы ошиблись программой или хотите что-то исправить, выйдите из программы, введя любой другой символ.\n");
    if (scanf("%d", &q) == 0)
        return 0;
    else if ((q > 2) || (q == 0))
        return 0;

    char input[MAX_STRING_SIZE];
    word_count(filename);
    Words w[wordnum];
    read_words(filename, w);

    if (q == 1) {
        for (int j = 0; j < tasks; j++) {
            int i = getrand(0, wordnum-1);
            printf("\n%d:\t %s\n", j + 1, w[i].first);
            printf("Введите перевод на русский:\t ");
            scanf("%s", input);
            k += sum(input, i, w, q);
        }
    }
    if (q == 2) {
        for (int j = 0; j < tasks; j++) {
            int i = getrand(0, wordnum-1);
            printf("\n%d:\t %s\n", j + 1, w[i].second);
            printf("Введите перевод на английский:\t ");
            scanf("%s", input);
            k += sum(input, i, w, q);
        }
    }
  
    return k;
}