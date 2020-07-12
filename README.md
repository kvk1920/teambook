# teambook
### Установка и удаление cmake 3.18
[откуда устанавливать](https://cmake.org/download/)

[установка](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line)

[удаление](https://askubuntu.com/questions/942713/how-do-i-remove-cmake-after-installing-it-from-source)

### Сборка и запуск тестов
(необходим `cmake` версии >=3.18)
```bash
mkdir build
cd build
cmake ..
make
ctest --verbose
```
