project(lambda_lang)

add_library(llang 
            Ast.cpp 
            PrinterAstVisitor.cpp 
            Lexer.cpp
            Parser.cpp
            )

target_include_directories(
    llang
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)