add_library(renderlib STATIC
    vec3.h
    ray.h
    Framebuffer.h
    Framebuffer.cpp
)


target_include_directories(renderlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})