cmake_minimum_required(VERSION 3.16)

project(ExamTEX C)

add_executable(examtex main.c
        ADT/adt.h ADT/adt.c
        GeneralUtils/general_utils.h GeneralUtils/general_utils.c
        ParserUtils/utils.h ParserUtils/utils.c
        Generation/generation.h Generation/generation.c)

