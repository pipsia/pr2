cmake_minimum_required(VERSION 3.10)
project(PracticalWork2 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

set(SOURCES
    src/main.c
    src/users.c
    src/processes.c
    src/help.c
    src/log.c
    src/errors.c
    src/utils.c
)

add_executable(practical_work_2 ${SOURCES})
