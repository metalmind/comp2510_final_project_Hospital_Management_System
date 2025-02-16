cmake_minimum_required(VERSION 3.30)
project(Assignment C)

set(CMAKE_C_STANDARD 23)

add_executable(Assignment src/main.c
                          src/menu.c
        src/patient.c
        src/patient.h
        src/tools.c
        src/tools.h
        src/schedule.c
        src/schedule.h)
