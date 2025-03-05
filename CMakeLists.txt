cmake_minimum_required(VERSION 3.10)
project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# turn on automatic processing MOC/UIS/RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(RESOURCES resources/resources.qrc)

# find Qt6 and needed modules
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets)

# recursively collecting all .cpp, .hpp and .ui from dirs(including subdirs)
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.hpp")

# create executable file
add_executable(Chess
  ${SRC_FILES}
  ${HEADER_FILES}
  ${RESOURCES}
)

# copy engine from project to build
add_custom_command(TARGET Chess POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_SOURCE_DIR}/engines/stockfish # your executable engines file in current dir
  $<TARGET_FILE_DIR:Chess>
)

# link dir with headers
target_include_directories(Chess PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
)

# link needed Qt modules
target_link_libraries(Chess PRIVATE
  Qt6::Core
  Qt6::Widgets
  Qt6::SvgWidgets
)
