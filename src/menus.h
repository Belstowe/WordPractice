#ifndef MENUS_H
#define MENUS_H

enum Menu {
    Main,              // Главное меню
    Variant,           // Выбор режима "игры"
    Difficulty,        // Выбор числа итераций
    CustomDifficulty,  // Выбор произвольного числа итераций
    ModeRuToEn,        // Перевод с родного на заучиваемый
    ModeEnToRu,        // Перевод с заучиваемого на родной
    ModeTesting,       // Выбор из четрыех вариантов правильного ответа
    Resolution,        // Просьба сменить разрешение на большее
    Exit               // Выход из программы
};

void menu_call(enum Menu menu_type);

#endif