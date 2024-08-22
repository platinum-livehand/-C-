project(sequence_search)

# 传统顺序查询
add_executable(${PROJECT_NAME} sequence_search.c)

# 带哨兵的顺序查询
add_executable(${PROJECT_NAME}_second sequence_search_second.c)