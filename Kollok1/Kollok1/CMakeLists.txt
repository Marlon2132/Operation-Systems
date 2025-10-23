# CMakeList.txt: проект CMake для Kollok1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Kollok1 "Kollok1.cpp" "Kollok1.h" "FactorialClass.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kollok1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
