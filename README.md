[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino\_KB

**This is a library for Arduino IDE by iArduino.ru. It allows to work with [1x4](https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-4-knopki.html), [3x4](https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-3x4-knopki.html), [4x4V2](https://iarduino.ru/shop/Expansion-payments/klaviatura-4-x4-knopki-v2.html), [4x4](https://iarduino.ru/shop/Sensory-Datchiki/klaviatura-4-4-knopki.html) keyboards**

**Данная библиотека для Arduino IDE от [iArduino.ru](https://iarduino.ru) позволяет работать с модулями: [Эластичная клавиатура 4 кнопки](https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-4-knopki.html), [Эластичная клавиатура 3x4 кнопки](https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-3x4-knopki.html), [Клавиатура 4 x4 кнопки V2](https://iarduino.ru/shop/Expansion-payments/klaviatura-4-x4-knopki-v2.html) и [Эластичная клавиатура 4 x4 кнопки](https://iarduino.ru/shop/Sensory-Datchiki/klaviatura-4-4-knopki.html)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте в нашем уроке [Подключение клавиатуры 4x4 и пьезоизлучателя к Arduino](https://lesson.iarduino.ru/page/urok-13-podklyuchenie-klaviatury-4-4-i-pezoizluchatelya-k-arduino/)


| Модель | Ссылка на магазин |
|---|---|
| <p>Эластичная клавиатура 4 кнопки</p> <img src="https://iarduino.ru/img/catalog/7e899d452c1ee8c75d4281daf895a4b5.jpg" width="350px"></img>| https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-4-knopki.html |
| <p>Эластичная клавиатура 3x4 кнопки</p> <img src="https://iarduino.ru/img/catalog/0b2820edd8efe7a85f554004434c2f0b.jpg" width="350px"></img>| https://iarduino.ru/shop/Expansion-payments/elastichnaya-klaviatura-3x4-knopki.html |
| <p>Клавиатура 4 x4 кнопки V2</p> <img src="https://iarduino.ru/img/catalog/3111111111111111111111111111111111111111111111111.jpg" width="350px"></img>| https://iarduino.ru/shop/Expansion-payments/klaviatura-4-x4-knopki-v2.html |
| <p>Эластичная клавиатура 4x4 кнопки</p> <img src="https://iarduino.ru/img/catalog/2111111111111111111111111111111111.jpg" width="350px"></img>| https://iarduino.ru/shop/Sensory-Datchiki/klaviatura-4-4-knopki.html |


## Назначение функций:

### Подключение библиотеки:

```C++
#include <iarduino_KB.h>
iarduino_KB ОБЪЕКТ(вывод 1 [,вывод 2 ... [, вывод N]]); // Указываются № выводов arduino подключенных к выводам клавиатуры
```

**В библиотеке реализованы 2 функции:**

```C++
ОБЪЕКТ.begin();
```

- Назначение: Инициализация клавиатуры
- Синтаксис: **begin**(параметр);
- Параметры:
  - KB1 - для эластичной клавиатуры 4x4
  - KB2 - для кнопочной клавиатуры 4x4
  - KB3 - для эластичной клавиатуры 3x4
  - KB4 - для эластичной клавиатуры 1x4
- Возвращаемые значения: Нет
- Примечание: Вызывается 1 раз в начале кода.

```C++
ОБЪЕКТ.check();
```

- Назначение: Определение нажимаемой/отпускаемой/удерживаемой кнопки
- Синтаксис: **check**([ параметр ]);
- Параметры:
  - KEY\_PRESS - функция будет возвращать true пока удерживается кнопка
  - KEY\_DOWN - функция вернёт true только при нажатии на кнопку
  - KEY\_UP - функция вернёт true только при отпускании кнопки
- Возвращаемые значения: bool **true** - есть нажимаемая/отпускаемая/удерживаемая кнопка, или **false** - нет нажимаемых/отпускаемых/удерживаемых кнопок
- Примечание: Вызов функции без параметра, равносилен вызову функции с параметром KEY\_PRESS

**Переменные:**

Указанные переменные доступны для чтения после возврата **true** функцией **check**

```C++
ОБЪЕКТ.getNum;
```

- значение кнопки в 16-ричной системе счисления: 0=0, 1=1, 2=2, 3=3, 4=4, 5=5, 6=6, 7=7, 8=8, 9=9, A=10, B=11, C=12, D=13, \*=E=14, #=F=15.

```C++
ОБЪЕКТ.getChar; 
```

- символ указанный на кнопке в виде типа char. если кнопка не имеет обозначений, то выводит символы "0"-"9", "A"-"Z" (слева на право, сверху вниз)

## Пример:

```C++
#include <iarduino_KB.h>            // Подключаем библиотеку для работы с матричной клавиатурой
iarduino_KB KB(9,8,7,6,5,4,3,2);    // Объявляем переменную для работы с матричной клавиатурой,
                                    // указывая номера arduino подключенные к шлейфу клавиатуры, начиная с первого вывода шлейфа.
                                    // Количество параметров соответствует количеству подключенных выводов клавиатуры
void setup()
{
    Serial.begin(9600);              // инициируем подключение к COM-порту на скорости 9600 бод
    KB.begin(KB1);                   // указываем тип клавиатуры
}

void loop()
{
    if(KB.check(KEY_DOWN )){         // если нажимается   кнопка, то ...
//  if(KB.check(KEY_UP   )){         // если отпускается  кнопка, то ...
//  if(KB.check(KEY_PRESS)){         // если удерживается кнопка, то ...
        Serial.print(KB.getNum);     // отправляем символ кнопки в последовательный порт (для вывода цифры кнопки используйте KB.getNum )
        Serial.print(" = \"");
        Serial.print(KB.getChar);    // отправляем символ кнопки в последовательный порт
        Serial.println("\"");
    }
}
```
