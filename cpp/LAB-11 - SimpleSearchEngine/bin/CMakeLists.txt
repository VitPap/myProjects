add_executable(labwork11 main.cpp)

target_link_libraries(labwork11 PRIVATE Builder Parser Searcher)
target_include_directories(labwork11 PUBLIC ${PROJECT_SOURCE_DIR})