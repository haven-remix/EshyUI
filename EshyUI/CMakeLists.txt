# CMakeList.txt : EshyUI

add_library(EshyUI STATIC
    "EshyUI.h" "EshyUI.cpp"
    "Entity.h" "Entity.cpp"
    "IndexBuffer.h" "IndexBuffer.cpp"
    "Renderer.h" "Renderer.cpp"
    "Shader.h" "Shader.cpp"
    "Texture.h" "Texture.cpp"
    "Util.h"
    "VertexArray.h" "VertexArray.cpp"
    "VertexBuffer.h" "VertexBuffer.cpp"
    "stb/stb_image.cpp"
)

add_compile_definitions(GLEW_STATIC)

target_include_directories(EshyUI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/detail
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/ext
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/gtc
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/gtx
    ${CMAKE_CURRENT_SOURCE_DIR}/glm/simd
    ${CMAKE_CURRENT_SOURCE_DIR}/stb
    ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include
)

target_link_libraries(EshyUI PUBLIC
    ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew32s.lib
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/glfw3.lib
    opengl32
)