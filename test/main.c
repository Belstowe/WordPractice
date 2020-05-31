#define CTEST_MAIN
#define CTEST_SEGFAULT

#include <ctest.h>

char* filename = "translate.txt"; //Название файла со списком

int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}