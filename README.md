# material_lib - Хапков Михаил

## Общее описание ПО и ссылки

Библиотека предназначена для создания и рендеринга разных типов поверхностей шестиугольных тайлов. Тестовое приложение будет содержать окно с рендером одной шестиугольной плитки, у которой можно менять внешний вид, переключая возможные наборы пресетов (например: трава, снег, вода). Оно будет запускаться с разными аргументами командной строки, позволяя выбирать один из пресетов, предложенных разработчиком.

[Командный репозиторий](https://github.com/nv3033/3rd-sem)

## Предназначение

Предназначается разработчикам, которые хотят менять внешний вид плиток, составляющих карту шестиугольников, для создания более разнообразного и реалистичного ландшафта. Или создавать и накладывать материалы для произвольных геометрических объектов. 

## Возможности и функции

Одна часть библиотеки будет отвечать за рендер внешнего вида поверхности. С помощью чего пользователь сможет менять внешний вид тайла. 
Другая часть ПО предоставит возможность создания собственных материалов для поверхностей, предлагая свои текстуры и настраивая другие параметры.

API библиотеки предполагается похожим на функционал материалов, который предоставляется продвинутыми инструментами для работы с 3d графикой (unity, blender). Но в упрощенном виде. (Скажем, созданием материала будет являться передача в функцию адреса текстуры и значений параметров. Возвращаемым объектом будет специальный тип. )

Основной задачей является создание возможности наложения на шестиугольную плитку текстуры, задание некоторых свойств, которые вместе с освещением влияют на вид таких как: roughness, transparency, smoothness. По мере выполнения основной задачи будут подключаться по очереди задачи из секции "Дополнительный функционал". Если предыдующие части будут выполнены и ещё останется срок на выполнение других. 

## Дополнительный функционал

1.  Создание инструментов для анимирования некоторых материалов. Например, для создания подвижной жидкости.
2. Добавление функционала для микрорельефа текстуры, визуальной иллюзии неровностей, не меняя геометрии объекта (за счет карт высот)
3. Возможность вращать плитку в 3d для рассмотрения с разных углов
4. Изменение освещенности ambient, diffuse, specular light.
5. Если останется время, то с помощью библиотеки для виджетов можно будет реализовать выбор режима через кнопки в окне самого приложения.