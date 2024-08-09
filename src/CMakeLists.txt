project(source_file)  

set(PROJECT_SUBDIRECTORIES  
    hello_Linux  
    hello_data_structure  
    single_link_list  
    loop_link_list  
    double_link_list  
    double_loop_link_list  
    stack  
    queue  
    loop_queue  
    force_match  
    kmp  
    tree  
    tree_level_traverse  
    tree_non_recursive
    in_thread_tree
    pre_thread_tree
)  

foreach(project_subdir  ${PROJECT_SUBDIRECTORIES})  
    add_subdirectory(${project_subdir})  
endforeach()