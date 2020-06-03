#ifndef MENUS_H
#define MENUS_H

enum Menu {
    Main,       // Главное меню
    Variant,    // Выбор режима "игры"
    Difficulty, // Выбор числа итераций
    ModeRuToEn, // Перевод с родного на заучиваемый
    ModeEnToRu, // Перевод с заучиваемого на родной
    Resolution, // Просьба сменить разрешение на большее
    Exit        // Выход из программы
};

void menu_call(enum Menu menu_type);

#endif