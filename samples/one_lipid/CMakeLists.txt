set(EXECUTABLE one_lipid)
add_executable(${EXECUTABLE} main.cpp)
target_link_libraries(${EXECUTABLE} cgmd)
file(COPY initial_structure.xyz DESTINATION .)
