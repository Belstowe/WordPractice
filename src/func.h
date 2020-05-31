#ifndef FUNC_H
#define FUNC_H

#define MAX_STRING_SIZE 256

typedef struct {
    char translate_from[MAX_STRING_SIZE];
    char translate_to[MAX_STRING_SIZE];
} Words;

int get_random_int(int min, int max);
int* random_order(const int min, const int max);
int file_word_pairs_count(char* IFILE);
Words* file_word_pairs_read(char* IFILE, const int wordnum);
Words* wordlist_form(char* IFILE, int** order);

#endif