#include <ui.h>

#include <ctest.h>

CTEST(ui_assist, correct_utf8_string_length)
{
    ASSERT_EQUAL(6, utf8_strlen("Hello!"));
    ASSERT_EQUAL(7, utf8_strlen("Привет."));
}