cmake_minimum_required(VERSION 3.10)
project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку MOC/UIS/RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(RESOURCES resources/resources.qrc)

# Находим Qt6 и нужные модули
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets)

# Рекурсивно собираем все .cpp, .hpp и .ui из папок(включая поддиректории)
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.hpp")

# Создаём исполняемый файл
add_executable(Chess
  ${SRC_FILES}
  ${HEADER_FILES}
  ${RESOURCES}
)

# Подключаем папку с заголовками
target_include_directories(Chess PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
)

# Линкуем нужные модули Qt
target_link_libraries(Chess PRIVATE
  Qt6::Core
  Qt6::Widgets
  Qt6::SvgWidgets
)
