add_subdirectory(one_lipid)
add_subdirectory(many_lipid)
add_subdirectory(periodic)
add_subdirectory(phase)

add_executable(stabilizer stabilizer.cpp)
target_link_libraries(stabilizer cgmd)
