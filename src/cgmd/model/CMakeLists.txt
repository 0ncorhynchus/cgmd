file(GLOB CPP_FILES *.cpp)
file(GLOB HPP_FILES *.hpp)

add_library(model SHARED ${CPP_FILES} ${HPP_FILES})
