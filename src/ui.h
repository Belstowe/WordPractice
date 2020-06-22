#ifndef UI_H
#define UI_H

unsigned utf8_strlen(const char* str);
void align_string(char* str, unsigned screen_width);
unsigned split_align_string(char* str, unsigned screen_width, char** substr);
unsigned halign(const char* str, const char align, const unsigned width);
unsigned
valign(const char align,
       const unsigned height,
       const unsigned num,
       const unsigned total);
void border_print(
        char* text,
        const unsigned up_y,
        const unsigned left_x,
        const unsigned bottom_y,
        const unsigned right_x,
        const char horizontal,
        const char vertical);

#endif