#include "ui.h"
#include <stdlib.h>
#include <string.h>

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

//char* align_string(const char* base_str);