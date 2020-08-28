# Spell-Checker
Этот репозиторий содержит исходный код програмы **Spell-Checker**. Spell-Checker — это программа для нахождения ошибок в написаном тексте.
## Использование
При первом запуске наеобходимо собрать Docker-контейнер.  
```
docker build . -t cpp-build-base:0.2.1
```
Запуск Docker-контейнера с помощью ***bash***:
```
docker run --rm -it -w //src -v /${PWD}://src cpp-build-base:0.2.1
```
Запуск Docker-контейнера в командной строке ***Windows***:
```
docker run --rm -it -w //src -v /${PWD}://src cpp-build-base:0.2.1
```
Компиляция решения на ***C++***:
```
clang++ -o spell_checker_solution spell_checker_solution.cpp
```
Запуск скомпилированного решения с передачей пути к файлу:
```
./spell_checker_solution path_to_file.txt
```
В случае, если путь файла указан не будет, то входным файлом по-умолчанию будет считаться файл `input.txt`, расположенный в корневой папке.
## Необходимое ПО
Для работы необходим Docker:  
* Для ***Linux***: 
```
$ sudo apt install -y docker-ce
```
* Для ***Windows*** можно скачать с оффициального сайта www.docker.com .
