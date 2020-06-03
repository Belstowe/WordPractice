#include "ui.h"
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
void align_string(char* str, unsigned screen_width)
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
            }
            else
                token = &(token[sym]);

            last_space_position = sym = index = 0;
        }
    }
}