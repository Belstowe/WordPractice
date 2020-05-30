# WordPractice [![Build Status](https://travis-ci.org/Belstowe/WordPractice.svg?branch=master)](https://travis-ci.org/github/Belstowe/WordPractice)

**WordPractice** — программа для заучивания иноязычных слов. 

## Применение
WordPractice запускается из консоли следующим образом:
```sh
& ./wrdprct [<your_file_name.txt>|translate.txt]
```
Т.е. при отсутствии аргумента с названием файла по умолчанию используется список `translate.txt`.

## Работа программы
* В качестве интерфейса используется консоль. Также ради более сложного оформления используется библиотека `ncurses`.
* На вход подаётся список в формате `.txt`, где каждая строчка имеет формат `[слово_заучиваемое] [перевод_на_родной]`.
* Программа приветствует и спрашивает пользователя, сколько итераций ему требуется для повторения списка и какой способ ему необходим - перевод с заучиваемого или с родного.
* Затем программа заданное количество итераций подбирает слово из списка и спрашивает к нему перевод.
* Когда процесс заканчивается, программа выдаёт количество удачно определённых слов и выходит.

Среди текущего функционала имеется:
* Чтение произвольного списка формата `.txt` произвольного размера;
* Строго чтение двух слов из строки - первое с заучиваемого, второе с родного;
* Возможность выбрать 10, 15 либо 20 итераций;
* Режим, где пользователь печатает слово-перевод.

## Планы
* Усложнение списка для более широкого функционала, такого как:
** Возможность записывать синонимы для оригинальных слов и варианты перевода для переведённых;
** Возможность использовать целые словосочетания (включающие в себя пробелы).
* Возможность локализации программы на другие языки с помощью `.ini` файлов;
* Выравнивание текста по центру;
* Новый режим выбирать соответствие слова с одним из четырёх выборов;
* Кроссплатформенность через использование CMake.