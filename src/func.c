#define filename "translate.txt"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "func.h"

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

typedef struct {
    char first[200];
    char second[200];
} Words;

void ReadWords(char* IFILE, Words* w, int q)
{
    int i;
    FILE* f;
    if ((f = fopen(IFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    for (i = 0; i < 18; i++)
        fscanf(f, "%s %s", ((w[i]).first), ((w[i]).second));
}

int sum(char* mass, int i, Words* w, int q)
{
    int k = 0;
    if (q == 1) {
        if (strcmp(mass, w[i].second) == 0) {
            k = k + 5;
            printf("True\t");
        } else {
            printf("Falls\t");
        }
    }
    if (q == 2) {
        if (strcmp(mass, w[i].first) == 0) {
            k = k + 5;
            printf("True\t");
        } else {
            printf("Falls\t");
        }
    }

    return k;
}

int check()
{
    int i, j, q, k = 0;
    printf("Выберите анг-рус-1\t рус-англ-2\t введите цифру\n");
    scanf("%d", &q);

    char mass2[100];
    Words w[18];
    ReadWords(filename, w, q);

    if (q == 1) {
        for (j = 0; j < 10; j++) {
            i = getrand(1, 17);
            printf("\n%d I: %s\t\n", j + 1, w[i].first);
            printf("Введите рус \n");
            scanf("%s", mass2);
            k += sum(mass2, i, w, q);
        }
    }
    if (q == 2) {
        for (j = 0; j < 10; j++) {
            i = getrand(1, 17);
            printf("\n%d I: %s\t\n", j + 1, w[i].second);
            printf("Введите англ\n");
            scanf("%s", mass2);
            k += sum(mass2, i, w, q);
        }
    }
  
    return k;
}