#include "func.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* wl_append
* Добавляет в конец списка элемент и возвращает его
*/
Wordlist *wl_append(Wordlist *root)
{   
    Wordlist *current = root;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = malloc(sizeof(Wordlist));
    current->next->pair = malloc(sizeof(Words));
    current->next->next=NULL;
    return current->next;
}

/* wl_get
* Получает элемент по индексу в списке и возвращает этот элемент
*/
Wordlist *wl_get(Wordlist *root, unsigned index)
{
    Wordlist *current = root;
    for(unsigned i=0; (i<index) && (current!=NULL); i++){
        current = current->next;
    }
    return current;
}



/* wl_size
* Измерение длины списка и ее вывод
*/
unsigned wl_size(Wordlist *root)
{   
    unsigned counter = 0;
    for(Wordlist* current = root; current!=NULL; current=current->next, counter++);
    return counter;
}


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

/* file_word_pairs_read
 * Считывает пары слов в списке и возвращает их список
 */
Wordlist* file_word_pairs_read(char* IFILE)
{   
    unsigned flag = 0;
    
    Wordlist* root = malloc(sizeof(Wordlist));
    root->pair = malloc(sizeof(Words));
    root->next=NULL;
    int start;
    start = 0;
    Words* curpair = NULL;

    FILE* f;
    if ((f = fopen(IFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
        char c;
        while ((c = fgetc(f)) !=EOF){
            switch (c) {
                case ':':
                    if (flag == 3) {
                        break;
                    }

                    flag = 1;
                    if (curpair == NULL){
                        curpair = root->pair;
                    }
                    else{
                        curpair = wl_append(root)->pair;
                    }
                break;
                
                case '=':
                    if (flag == 3) {
                        break;
                    }

                    flag = 2;
                    curpair->translate_from[start]='\0';
                    start=0;
                break;

                case ';':
                    if (flag == 3) {
                        break;
                    }

                    flag = 0;
                    curpair->translate_to[start]='\0';
                    start=0;
                break;

                case '/':
                    if (flag == 0) {
                        flag = 3;
                    }
                break;

                case '.':
                    if (flag == 3) {
                        break;
                    }
                    fclose(f);
                    return root;

                default :
                    if (flag == 1) {
                        if ((c != ' ') && (c != '\n')) {
                            
                            curpair->translate_from[start++] = c;
                        }
                    }
                    else if (flag == 2) {
                        if ((c != ' ') && (c != '\n')) {
                            
                            curpair->translate_to[start++] = c;
                        }
                    }
                    else if (flag == 3) {
                        if (c == '\n') {
                            flag=0;
                        }
                    }
                break;
            }
    }
    

    fclose(f);
    return root;
}

/* wordlist_form
 * Формирует список пар слов с помощью file_word_pairs_read и
 * file_word_pairs_count, возвращая указатель на него.
 */
Wordlist* wordlist_form(char* IFILE)
{
    


    return file_word_pairs_read(IFILE);
}