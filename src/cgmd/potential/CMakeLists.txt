file(GLOB CPP_FILES *.cpp)
file(GLOB HPP_FILES *.hpp)

include_directories(../)
add_library(potential SHARED ${CPP_FILES} ${HPP_FILES})
