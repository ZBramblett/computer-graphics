add_library(renderlib STATIC
    vec3.h
    ray.h
    Framebuffer.h
    Framebuffer.cpp
)


target_include_directories(renderlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(renderlib PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(renderlib PRIVATE PNG::PNG)