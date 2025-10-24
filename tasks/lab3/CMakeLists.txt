# ===================================================================
# ===================================================================

# Минимальная версия CMake для сборки проекта
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(Lab03_OOP)

# Устанавливаем стандарт C++17 (для noexcept, override и других фич)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем папку include в пути поиска заголовочных файлов
# Это позволяет писать #include "Figure.h" вместо #include "../include/Figure.h"
include_directories(include)

# ===================================================================
# БИБЛИОТЕКА С КЛАССАМИ ФИГУР
# ===================================================================
# Создаем статическую библиотеку geometry_lib
# Она будет использоваться и в основной программе, и в тестах
# Это избегает дублирования компиляции
add_library(geometry_lib
    src/Figure.cpp      # Базовый класс
    src/Square.cpp      # Класс квадрата
    src/Rectangle.cpp   # Класс прямоугольника
    src/Trapezoid.cpp   # Класс трапеции
    src/Array.cpp       # Динамический массив
)

# ===================================================================
# ОСНОВНАЯ ПРОГРАММА
# ===================================================================
# Создаем исполняемый файл lab03 из main.cpp
add_executable(lab03 main.cpp)

# Линкуем библиотеку geometry_lib к основной программе
target_link_libraries(lab03 geometry_lib)

# ===================================================================
# GOOGLE TESTS
# ===================================================================
# Включаем систему тестирования
enable_testing()

# Подключаем Google Test через FetchContent (скачивается автоматически)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Для Windows: предотвращаем конфликты runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Скачиваем и делаем доступным Google Test
FetchContent_MakeAvailable(googletest)

# Создаем исполняемый файл с тестами
add_executable(tests tests/test_geometry.cpp)

# Линкуем к тестам:
# - geometry_lib (наши классы)
# - gtest_main (Google Test с готовой функцией main)
target_link_libraries(tests geometry_lib gtest_main)

# Регистрируем тесты в CTest (можно запускать через ctest)
include(GoogleTest)
gtest_discover_tests(tests)