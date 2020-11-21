#ifndef FUNC_H
#define FUNC_H

#define MAX_STRING_SIZE 256

typedef struct {
    char translate_from[MAX_STRING_SIZE];
    char translate_to[MAX_STRING_SIZE];
} Words;

typedef struct t_wordlist {
    Words *pair;
    struct t_wordlist *next;
} Wordlist;

int get_random_int(int min, int max);
unsigned strcnt(char *str, char chr);
char *extract_random_substr(char *str, char *delim);
int substrcmp(char *str1, char *str2, char *delim);
Wordlist *wl_append(Wordlist *root);
Wordlist *wl_get(Wordlist *root, unsigned index);
unsigned wl_size(Wordlist *root);
int* random_order(const int min, const int max);
Wordlist* wordlist_form(char* IFILE);

#endif