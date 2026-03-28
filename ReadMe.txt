Программа сортировки и фильтрации адресов.

Сборка из директории labTwo:
                ./clear_build.sh


Для запуска используется следующая команда:
./ipFilter filtration <тип фильтрации> in <входной файл> out <вывод>
Типы фильрации:
    first - Фильрация по первому октету. После данного типа пишется одно число. Прим: "filtration first 34".
    first-second - Фильрация по двум первым октетам. После него пишется два числа через запятую без пробелов. Прим: "filtration first-second 34,45".
    any - Фильтрация по наличию числа в любом октете адреса. После данного типа пишется одно число. Прим: "filtration any 34".
    none - Не использовать фильтрацию.


Вывод:
    console - Вывод результатов будет осуществляться в консоль.
    путь файла - Вывод результатов будет осуществляться в файл. Если файла с таким названием нет, он будет создан.


!!!ВАЖНО для проверяющего:
    Так как программа парсит аргументы из командной строки и сортирует по типу, то "cat ip_filter.tsv | ipFilter | md5sum" верно не сработает.
    Нужно запустить сразу все фильтрации а далее проверить хеш.
    Верная команда:
    { 
  ./ipFilter filtration none in ip_filter.tsv out console; 
  ./ipFilter filtration first 1 in ip_filter.tsv out console; 
  ./ipFilter filtration first-second 46,70 in ip_filter.tsv out console; 
  ./ipFilter filtration any 46 in ip_filter.tsv out console; 
    } | md5sum