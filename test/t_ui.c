#include <ui.h>

#include <ctest.h>

CTEST(ui_assist, correct_utf8_string_length)
{
    ASSERT_EQUAL(6, utf8_strlen("Hello!"));
    ASSERT_EQUAL(7, utf8_strlen("Привет."));
}

CTEST(ui_assist, correctly_aligned_text)
{
	char test_string1[] = "Тестовая проверка тестирования";
	align_string(test_string1, 64); // При правильном исполнении переносы на новую строку появиться не должны.
	ASSERT_STR("Тестовая проверка тестирования", test_string1);

	char test_string2[] = "Тестовая проверка тестирования";
	align_string(test_string2, 10); // Здесь же каждый пробел должен быть замещён на '\n'.
	ASSERT_STR("Тестовая\nпроверка\nтестирования", test_string2);

	char test_string3[] = "Тестовая проверка тестирования";
	align_string(test_string3, 20); // Здесь же только последний пробел должен быть замещён на '\n'.
	ASSERT_STR("Тестовая проверка\nтестирования", test_string3);
}