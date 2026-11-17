include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)
target_link_libraries (glfwExample PRIVATE renderlib)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

# Copy every shader into the build folder; re-copies when a source .glsl changes
file(GLOB SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.glsl)
foreach(SHADER ${SHADER_FILES})
  get_filename_component(SHADER_NAME ${SHADER} NAME)
  configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME} COPYONLY)
endforeach()

