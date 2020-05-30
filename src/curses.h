#ifndef CURSES_H
#define CURSES_H

enum Menu {
    Main,       // Главное меню
    Variant,    // Выбор режима "игры"
    Difficulty, // Выбор числа итераций
    ModeRuToEn, // Перевод с родного на заучиваемый
    ModeEnToRu, // Перевод с заучиваемого на родной
    Exit        // Выход из программы
};

// void Menu(int* item);
// void Difficult(int* lvl);
// void Play(int* lvl, int* var);
// void Variant(int* var);
void menu_call(enum Menu menu_type);

#endif
