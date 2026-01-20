cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(Mini_Projekt_C___Interpreter)

set(CMAKE_CXX_STANDARD 17)

set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(WITH_DEMO OFF CACHE BOOL "" FORCE)

add_subdirectory(external/antlr4-runtime)

include_directories(.)
include_directories(src)
include_directories(src/interpreter)
include_directories(src/runtime)

file(GLOB_RECURSE ANTLR_GEN_SOURCES
        ${CMAKE_SOURCE_DIR}/gen/*.cpp
)

add_executable(Mini_Projekt_C___Interpreter
        ${ANTLR_GEN_SOURCES}

        src/interpreter/Interpreter.cpp
        src/interpreter/Interpreter.h
        src/runtime/Cell.h
        src/runtime/StackFrame.h
        src/runtime/Value.h
        src/main.cpp
        src/ast/AST.h
        src/interpreter/ReturnSignal.h
        src/ast/ASTBuilder.cpp
        src/ast/ASTBuilder.h
        src/ast/AST.cpp)


target_include_directories(Mini_Projekt_C___Interpreter PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/gen
        ${CMAKE_SOURCE_DIR}/external/antlr4-runtime/runtime/src
)

target_link_libraries(Mini_Projekt_C___Interpreter
        antlr4_static
)

target_sources(Mini_Projekt_C___Interpreter PRIVATE
        src/semantic/SemanticChecker.cpp
        src/semantic/SemanticChecker.h
        src/semantic/SymbolTable.h
        src/semantic/Type.h
)

