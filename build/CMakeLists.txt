cmake_minimum_required(VERSION 3.12)

set(PR_NAME "FixedPoint")

project(${PR_NAME})

add_executable(${PR_NAME}
	../src/fixedpoint.c
	../src/main.c
	../src/tables.c)

target_include_directories(${PR_NAME} PRIVATE ../include)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()