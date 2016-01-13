file(GLOB CPP_FILES *.cpp)
file(GLOB HPP_FILES *.hpp)

add_library(cgmd SHARED ${CPP_FILES} ${HPP_FILES})

add_subdirectory(potential)
add_subdirectory(model)
target_link_libraries(cgmd potential)
target_link_libraries(cgmd model)
