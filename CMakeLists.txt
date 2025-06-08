cmake_minimum_required(VERSION 3.31)
project(Taller3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller3 main.cpp
        Estudiante.cpp
        Estudiante.h
        Instructor.cpp
        Instructor.h
        NodoABB_Instructores.cpp
        NodoABB_Instructores.h
        NodoAVL_Estudiantes.cpp
        NodoAVL_Estudiantes.h
        estudiantes.csv
        instructores.csv
        Sistema.h
        Sistema.cpp)
