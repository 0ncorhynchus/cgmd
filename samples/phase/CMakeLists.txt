set(EXECUTABLES
    fluid
    gel
    unstable)
foreach(EXECUTABLE ${EXECUTABLES})
    add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)
    target_link_libraries(${EXECUTABLE} cgmd)
endforeach(EXECUTABLE)
file(COPY initial_structure.xyz DESTINATION .)
