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
    const int expected = 4;

    ASSERT_EQUAL(expected, wl_size(wordlist_form(filename)));
}

CTEST(extract_word_list, checking_word_list)
{
    Wordlist* wordlist = wordlist_form(filename);
    ASSERT_NOT_NULL(wordlist);

    ASSERT_STR("illuminate", wl_get(wordlist, 0)->pair->translate_from);
    ASSERT_STR("излучать", wl_get(wordlist, 0)->pair->translate_to);
    ASSERT_STR("test", wl_get(wordlist, 1)->pair->translate_from);
    ASSERT_STR(
            "тест|испытание|испытать|тестировать",
            wl_get(wordlist, 1)->pair->translate_to);
    ASSERT_STR("solid|hard", wl_get(wordlist, 2)->pair->translate_from);
    ASSERT_STR("твёрдый|твердый", wl_get(wordlist, 2)->pair->translate_to);
    ASSERT_STR("bite the bullet", wl_get(wordlist, 3)->pair->translate_from);
    ASSERT_STR("стиснуть зубы", wl_get(wordlist, 3)->pair->translate_to);
}

CTEST(extra_string_func, getting_proper_char_count)
{
    const char str1[] = "solid|hard";
    const char str2[] = "тест/испытание/испытать/тестировать";
    const char str3[] = "стиснуть зубы";
    ASSERT_EQUAL(1, strcnt(str1, '|'));
    ASSERT_EQUAL(3, strcnt(str2, '/'));
    ASSERT_EQUAL(0, strcnt(str3, '|'));
    ASSERT_EQUAL(1, strcnt(str3, ' '));
}

CTEST(extra_string_func, proper_substr_functioning)
{
    const char str1[] = "тест|испытание|испытать|тестировать";
    const char* substr1
            = extract_random_substr(str1, "|"); // случайная подстрока
    const char substr2[] = "испытывать"; // не подстрока, похожая
    const char substr3[]
            = "%%\\ab|c"; // не подстрока, рандомная, включает делим

    ASSERT_EQUAL(0, substrcmp(substr1, str1, "|"));
    ASSERT_NOT_EQUAL(0, substrcmp(substr2, str1, "|"));
    ASSERT_NOT_EQUAL(0, substrcmp(substr3, str1, "|"));
}

CTEST(list_operations, proper_working_list_operations)
{
    Wordlist* wordlist = wl_init();

    for (unsigned i = 1; i < 50; i++)
        wl_append(wordlist);

    ASSERT_NOT_NULL(wl_get(wordlist, 0));
    ASSERT_NOT_NULL(wl_get(wordlist, 40));
    ASSERT_NULL(wl_get(wordlist, 50));
    ASSERT_EQUAL(50, wl_size(wordlist));
}