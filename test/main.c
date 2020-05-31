#define CTEST_MAIN
#define CTEST_SEGFAULT

#include <ctest.h>

size_t wordnum = 0; //Количество слов в списке
char* filename = "translate.txt";     //Название файла со списком

int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}