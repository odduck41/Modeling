# ОТЧЁТ

1) Создана система управления курсами иностранного языка. Есть возможность добавить индивидуальный курс, характеризующийся языком изучения, уровнем, стоимостью и группу, характеризующуюся изучения, уровнем, стоимостью, интенсивностью и количеством занятий в неделю. По истечении двух недель производится пересчет, т.е. удаляются пользователи, не посещающие или не оплачивающие занятия, а также рассматриваются заявки, поданные за 2 недели, в которых указана фамилия пользователя, желаемый язык, уровень и интенсивность. Система формирует и переформирует группы так, чтобы численность людей в группе оставалась близкой к 7 людям в группе.
2) ![image](https://github.com/user-attachments/assets/25810daf-9e6c-483c-ae8f-7cdf0dc3e31e)
3) Текстовые спецификации основных классов системы:
   1) Класс Group – это обобщение группы. Содержит методы:
      + get_language() – возвращает язык группы
      + get_level() – возвращает уровень группы
      + get_cost() – возвращает стоимость группы
      + set_language(Language) – устанавливает язык
      + set_level(Level) – устанавливает уровень
      + set_cost(int) – устанавливает стоимость
   2) Класс NonIndividual – группа, в которой к-во учеников >= 5. Содержит методы:
      + add(Consumer*) – добавить пользователя
      + remove(Consumer*) – удалить пользователя
      + get_consumers() – получить вектор пользователей данного курса
      + recount() – пересчитать пользователей и удалить тех, кто не посещает или не оплачивает. Вызывается по истечении двухнедельного периода
      + day() – прибавить один день
      + addDays(int) – прибавить некоторое к-во дней
      + get_intensity() – получить интенсивность курса
      + get_amount() – получить стоимость курса
   3) Класс Individual – индивидуальная группа. Содержит методы:
      + get_intensity() – получить интенсивность курса
      + get_amount() – получить стоимость курса
   4) Класс Consumer. Содержит методы:
      + get_surname() – получить фамилию
      + pay(int) – оплатить определенную сумму
      + visit() – посетить занятие
      + checkAmount(long long) – проверить, оплачивается ли курс
      + checkVisits() – проверить, посещается ли курс
  
4) Для программирования использовался язык С++. Для написания кода использовалась среда разработки XCode, а так же IDE Clion. Для реализации использовались библиотеки string, utility, iostream, vector, map, random, для отладки – chrono и thread. Для фронта использовались библиотеки QT и SFML. 
5) Программа имеет следующую файловую структуру:
```
├── include/
│   ├── Application.h
│   ├── Canvas.h
│   ├── Drawable.h
│   ├── Modeling.h
│   ├── QSFMLCanvas.h
│   └── Utility.h
├── src/
│   ├── Application.cpp
│   ├── Canvas.cpp
│   ├── Drawable.cpp
│   ├── Modeling.cpp
│   ├── QSFMLCanvas.cpp
│   └── main.cpp
├── .gitignore
├── CMakeLists.txt
└── LICENSE
```
6) ...
7) 
8) [тык](https://github.com/odduck41/Modeling)
