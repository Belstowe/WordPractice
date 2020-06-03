#ifndef UI_H
#define UI_H

unsigned utf8_strlen(const char* str);
void align_string(char* str, unsigned screen_width);
unsigned split_align_string(char* str, unsigned screen_width, char** substr);
unsigned halign(const char* str, const char align, const unsigned width);
unsigned valign(const char align, const unsigned height);

#endif