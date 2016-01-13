file(GLOB CPP_FILES *.cpp)
file(GLOB HPP_FILES *.hpp)

add_library(cgmd SHARED ${CPP_FILES} ${HPP_FILES})

add_subdirectory(potential)
target_link_libraries(cgmd potential)
