#ifndef UI_H
#define UI_H

unsigned utf8_strlen(const char* str);
void align_string(char* str, unsigned screen_width);
unsigned split_align_string(char* str, unsigned screen_width, char** substr);

#endif