project(lambda_lang)

add_library(llang Ast.cpp)

target_include_directories(
    llang
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)