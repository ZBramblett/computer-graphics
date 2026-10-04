add_library(renderlib STATIC
    rtweekend.h
    vec3.h
    ray.h
    Framebuffer.h
    Framebuffer.cpp
    Camera.h
    HitRecord.h
    Shape.h
    Sphere.h
    Sphere.cpp
    ShapeList.h
    ShapeList.cpp
    PerspectiveCamera.cpp
    Camera.cpp
    Triangle.h
    Triangle.cpp
    Scene.h
    Scene.cpp
    Shape.cpp
    Shader.h
    Shader.cpp
    SolidColorShader.cpp
)


target_include_directories(renderlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(renderlib PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(renderlib PRIVATE PNG::PNG)