# I still suck at writing cmake files.
# So this is mostly ChatGPT generated.

cmake_minimum_required(VERSION 3.10)
project(LogicParser C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src/)

add_executable(LogicParser
    src/Utils/DynamicBuffer.c
    src/Utils/StringUtils.c

    src/Shared/Operators.c

    src/Scanners/StringScanner.c
    src/Scanners/TokenScanner.c

    src/Lexer/Token.c
    src/Lexer/Lexer.c

    src/Parser/AST.c
    src/Parser/Parser.c
  
    src/Interpreter/EnvEntry.c
    src/Interpreter/Env.c
    src/Interpreter/ExpressionEvaluator.c
    src/Interpreter/TruthTable.c

    src/Main.c
)

target_compile_options(LogicParser PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Werror
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-unused-but-set-variable
    -Wno-unused-imports
)

