#include "ui.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

/* utf8_strlen
 * Считывает количество реальных (видимых) символов в строке str и возвращает
 * его.
 */
unsigned utf8_strlen(const char* str)
{
    unsigned len = 0;
    for (unsigned i = 0; str[i] != '\0'; i++) {
        if (str[i] & 0x80)        // 1*******
            if (!(str[i] & 0x40)) // *0******
                continue; // 10****** - байты, кодирующие символы размером более
                          // 1 байта; оттого их считать не надо

        len++;
    }

    return len;
}

/* align_string
 * Для правильного центрирования строки, ввиду особенностей работы и символа
 * '\n', и случая выхода за рамки консоли (указатель всегда начинает слева), мы
 * должны свести строку к общему виду, исключив второй случай. Для этого мы
 * заменяем последний пробел, если строка выходит за рамки окна, на '\n'.
 *
 * Принимает на вход строку str (которая впоследствии видоизменяется) и ширину
 * окна screen_width.
 */
void align_string(char str[], unsigned screen_width)
{
    unsigned last_space_position = 0;
    char* token = str;
    unsigned index = 0;

    for (unsigned sym = 0; token[sym] != '\0'; sym++) {
        if (token[sym] & 0x80) {        // 1*******
            if (!(token[sym] & 0x40)) { // *0******
                continue; // 10****** - байты, кодирующие символы размером более
            } // 1 байта; оттого их считать не надо
        }

        if (token[sym] == '\n') {
            token = &(token[sym]);
            last_space_position = sym = index = 0;
            continue;
        }

        if (token[sym] == ' ')
            last_space_position = sym;

        index++;
        if (index >= screen_width) {
            if (last_space_position != 0) {
                token[last_space_position] = '\n';
                token = &(token[last_space_position]);
            } else
                token = &(token[sym]);

            last_space_position = sym = index = 0;
        }
    }
}

/* split_align_string
 * Функция делит строку str на подстроки, такие, что:
 * Вмещаются во всю ширину окна консоли screen_width;
 * Содержат цельные слова;
 * Сохраняют прежние переносы на новые строки.
 * Возвращает в substr массив указателей на получившиеся подстроки, а также их
 * число.
 *
 * Перед использованием данной подпрограммы нет необходимости дополнительно
 * вызывать align_string, однако выделять память для substr необходимо.
 */
unsigned split_align_string(char str[], unsigned screen_width, char** substr)
{
    align_string(str, screen_width);
    unsigned count = 0;

    char* token = strtok(str, "\n");

    while (token != NULL) {
        substr[count] = token;
        count++;
        token = strtok(NULL, "\n");
    }

    return count;
}

/* halign
 * Возвращает колонну, с которой начнётся строка.
 * В зависимости от аргумента align ('l', 'c', 'r') строка может быть слева, по
 * центру или справа соответственно.
 */
unsigned halign(const char* str, const char align, const unsigned width)
{
    switch (align) {
    case 'l':
        return 0;

    case 'c':
        return (width - utf8_strlen(str)) / 2;

    case 'r':
        return (width - utf8_strlen(str));
    }

    return 0;
}

/* valign
 * Возвращает строку, с которой начнётся строка.
 * Аргументы num и total необходимы для учёта множества строк - первый
 * обозначает индекс строки и начинается с 0, а второй обозначает число строк.
 * В зависимости от аргумента align ('u', 'c', 'b') строка может
 * быть сверху, по центру или снизу соответственно.
 */
unsigned
valign(const char align,
       const unsigned height,
       const unsigned num,
       const unsigned total)
{
    switch (align) {
    case 'u':
        return num;

    case 'c':
        return (height / 2) + num - ((total + 1) / 2);

    case 'b':
        return height + num - total;
    }

    return 0;
}

/* border_print
 * Печатает в пределах определённой рамки (включая пограничные координаты)
 * текст, учитывая горизонтальное и вертикальное выравнивания.
 */
void border_print(
        char text[],
        const unsigned up_y,
        const unsigned left_x,
        const unsigned bottom_y,
        const unsigned right_x,
        const char horizontal,
        const char vertical)
{
    const unsigned width = right_x - left_x + 1;
    const unsigned height = bottom_y - up_y + 1;

    char** substrings = malloc(height * sizeof(char*));
    unsigned count = split_align_string(text, width, substrings);

    for (unsigned i = 0; i < count; i++)
        mvprintw(
                valign(vertical, height, i, count) + up_y,
                halign(substrings[i], horizontal, width) + left_x,
                substrings[i]);
}