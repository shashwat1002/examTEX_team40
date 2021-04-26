cmake_minimum_required(VERSION 3.16)

project(ExamTEX C)

add_executable(examtex main.c
        ADT/adt.c ADT/adt.h
        ParserUtils/utils.c ParserUtils/utils.h)

