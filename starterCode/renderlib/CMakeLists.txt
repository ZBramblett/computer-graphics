add_library(renderlib INTERFACE
    vec3.h
    ray.h
    FrameBuffer.h
)
target_include_directories(renderlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})