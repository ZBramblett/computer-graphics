include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (rasterizer
  main.cpp 
  GLSL.cpp GLSL.h
  GLShape.cpp GLShape.h
  GLTriangle.cpp GLTriangle.h
)

target_link_libraries (rasterizer PRIVATE GLEW::GLEW)
target_link_libraries (rasterizer PRIVATE glfw)
target_link_libraries (rasterizer PRIVATE renderlib)

if(APPLE)
    target_link_libraries(rasterizer PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(rasterizer PRIVATE OpenGL::GL)
endif()

target_link_libraries (rasterizer PRIVATE PNG::PNG)
target_link_libraries (rasterizer PRIVATE ZLIB::ZLIB)

# Copy every shader into the build folder; re-copies when a source .glsl changes
file(GLOB SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.glsl)
foreach(SHADER ${SHADER_FILES})
  get_filename_component(SHADER_NAME ${SHADER} NAME)
  configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME} COPYONLY)
endforeach()

