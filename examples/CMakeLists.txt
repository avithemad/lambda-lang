project(lambda_lang)
add_executable(ast_test ast_test.cpp)
add_executable(lexer_test lexer_test.cpp)
add_executable(parser_test parser_test.cpp)

target_link_libraries(lexer_test
    PRIVATE 
    llang)
target_link_libraries(ast_test
    PRIVATE 
    llang)
target_link_libraries(parser_test
    PRIVATE 
    llang)