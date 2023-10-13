# Тестовое задание YADRO

### Структура
Проект разбит на два модуля - src и test. В каждом свой CMake. 
Также есть корневой CMakeLists.txt, агрегирующий оба модуля.

### Тестирование
Для unit-тестов используется библиотека GoogleTest. Для тестов алгоритма сортировки 
реализованы два класса MemoryTape и MemoryTapeSorter. Также тестируется кастомный парсер.  


### Парсинг
Для парсинга аргументов командной строки и файлов конфигурации используются самописные
парсеры. При необходимости можно было бы воспользоваться парсерами из библиотеки boost, 
например Boost.Program_options

Конфигурационный файл должен иметь следующую структуру
```
ReadDelay=0
WriteDelay=0
MoveTapeDelay=0
MaxMemoryElements=4
```

Где MaxMemoryElements - сколько элементов мы можем держать в памяти.

### Запуск программы
```
tape -in=input.txt -out=output.txt -cfg=config.txt
```

### Основные классы
**Tape** - абстрактный класс, все методы чистые виртуальные.  
**FileTape, MemoryTape** - реализации класса Tape

**TapeSorter** - абстрактный класс с базовой логикой сортировки  
**FileTapeSorter, MemoryTapeSorter** - конкретные реализации TapeSorter

### Алгоритм сортировки
Пусть N - размер ленты, M - размер памяти, тогда нам понадобится N/M дополнительных 
ленточных файлов для реализации алгоритма сортировки. Алгоритм:  
1. Загрузим M элементов в память, отсортируем и запишем во временную ленту. 
Повторим N/M раз. Получим N/M доп. лент.
2. Имея N/M отсортированных лент, можем применить MergeSort снизу вверх: 
возьмем 1 и 2 (3 и 4 итд) ленты, будем сравнивать их элементы по левому указателю 
и меньший записывать в буффер размера M, инкрементируя соответствующий указатель ленты. 
Как только буффер заполнится, запишем его в новую ленту. На этом этапе из N/M лент 
получим N/2M лент. Повторим, пока не останется лишь одна лента.  

Асимптотика по времени O(nlogn), память O(1)

### Многопоток
Можно заметить, что операции слияния лент независимые - это делает 
их неплохим кандидатом для параллельного вычисления. Для этого 
воспользуемся std::async, std::future, запуская каждую операцию 
слияния двух лент в новом потоке, и далее дождемся результатов.


