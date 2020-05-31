#include <func.h>

#include <ctest.h>

#include <stdio.h>

extern char* filename;

CTEST(proper_working_assist, random_order_no_repeats)
{
    int* order = random_order(0, 19);
    ASSERT_NOT_NULL(order);

    for (int i = 0; i < 19; i++)
        for (int j = i + 1; j <= 19; j++)
            ASSERT_NOT_EQUAL(order[i], order[j]);
}

CTEST(extract_word_list, checking_right_list_size)
{
    const int expected = 25;

    ASSERT_EQUAL(expected, file_word_pairs_count(filename));
}

CTEST(extract_word_list, checking_word_list)
{
    const int wordnum = file_word_pairs_count(filename);
    Words* wordlist = file_word_pairs_read(filename, wordnum);
    FILE* f = fopen(filename, "r");
    char buf_string[MAX_STRING_SIZE];

    ASSERT_NOT_NULL(wordlist);
    ASSERT_NOT_NULL(f);
    ASSERT_NOT_NULL(buf_string);

    for (int i = 0; i < wordnum; i++) {
        fscanf(f, "%s", buf_string);
        ASSERT_STR(buf_string, (wordlist[i]).translate_from);
        fscanf(f, "%s", buf_string);
        ASSERT_STR(buf_string, (wordlist[i]).translate_to);
    }
}