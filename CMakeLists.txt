cmake_minimum_required(VERSION 3.30)
project(Assignment C)

set(CMAKE_C_STANDARD 23)

add_executable(Assignment src/main.c
               src/menu.c
               src/patient.c
               inc/patient.h
               src/tools.c
               inc/tools.h
               src/schedule.c
               inc/schedule.h
               inc/doctor.h
               src/doctor.c)
