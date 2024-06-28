project(lambda_lang)
add_executable(ast_test ast_test.cpp)
target_link_libraries(ast_test 
    PRIVATE 
    llang)