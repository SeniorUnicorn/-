# OOP-Game

Консольная игра, реализованная с использованием ООП, курсовая работа за 1-ый семестр 2-го курса.

Принцип работы:
Активная фигура (дом) перемещается по экрану с помощью стрелок на клавиатуре, 
при столкновении с красным шаром понижается уровень фигуры (визуальное изменение), 
при минимальном уровне размер фигуры уменьшается. При столкновении с зеленым шаром 
уровень фигуры (визуальное изменение), при максимальном уровне размер фигуры увеличивается. 
При столкновении с фиолетовым шаром дом переходит в новое состояние -- без крыши. 
После столкновения шар перемещается в новое случайное место. Выход из игры по кнопке Esc.

Примечание:
Алгоритм предотвращения выхода фигур за пределы консольного окна не реализован, поэтому
возможно исчезновение второстепенных фигур или выход активной фигуры за пределы консольного окна.

/*----------------------------------------------------------------------*\
|                                                                        |
|      Project type:  Win32 Console Application                          |
|      Project name:  Учебная практика                                   |
|      File name   :  КР Аджалова 207Б.cpp                               |
|      Language    :  cpp MSVS 2019                                      |
|      Programmers :  M30-207Б-19                                        |
|                     Аджалова Севиль Фархадовна                         |
|      Created     :  18.09.2020                                         |
|      Modified by :  29.11.2020                                         |
|      Comment     :  Консольная игра                                    |
|                                                                        |
|--------- Ф А Й Л Ы   В   Д И Р Е К Т О Р И И   П Р О Е К Т А ----------|
|                                                                        |
|   "Classes.h"       - объявление классов и прототипы функций           |
|   "Classes.cpp"     - реализация методов классов и функций             |
|   "GetConlWin.h"    - инициализация дескриптора консольного окна       |
|   "GetConlWin.cpp"  - методы для инициализации дескриптора окна        |
|   "ClassDiagram.cd" - диаграмма классов                                |
|                                                                        |
\-----------------------------------------------------------------------*/
