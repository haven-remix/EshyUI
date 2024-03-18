# CMakeList.txt : Sandbox

add_executable(Sandbox "main.cpp")

target_include_directories(Sandbox PUBLIC
    ${CMAKE_SOURCE_DIR}/EshyUI
    ${CMAKE_SOURCE_DIR}/EshyUI/glm
    ${CMAKE_SOURCE_DIR}/EshyUI/glm/detail
    ${CMAKE_SOURCE_DIR}/EshyUI/glm/ext
    ${CMAKE_SOURCE_DIR}/EshyUI/glm/gtc
    ${CMAKE_SOURCE_DIR}/EshyUI/glm/gtx
    ${CMAKE_SOURCE_DIR}/EshyUI/glm/simd
    ${CMAKE_SOURCE_DIR}/EshyUI/stb
    ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include
)

target_link_libraries(Sandbox PUBLIC
    ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew32s.lib
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/glfw3.lib
    opengl32
    EshyUI
)