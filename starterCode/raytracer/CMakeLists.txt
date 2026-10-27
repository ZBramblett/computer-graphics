include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(image
main.cpp
)


target_link_libraries(image PRIVATE renderlib cs4212-util)