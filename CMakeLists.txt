cmake_minimum_required(VERSION 3.0.0)
project(PhysicSimu VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall -O3")


# if (APPLE)

#     include_directories(
#         /usr/local/include
#         /opt/local/include
#         /opt/homebrew/include
#     )

#     link_directories(
#         /usr/local/lib
#         /opt/local/lib
#         /opt/homebrew/lib
#     )
# endif()

# 不设置会出现 Undefined symbols错误，主要是因为GLFW3的动态库没有链接上
set(CMAKE_OSX_ARCHITECTURES "arm64")

# 设置头文件，源文件，第三方文件路径
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

# opengl
find_package(OpenGL REQUIRED)

# eigen3
find_package(Eigen3 REQUIRED)

# glfw3
find_package(glfw3 REQUIRED)

# glm
find_package(glm REQUIRED)

# glew
find_package(GLEW REQUIRED)

# glad
set(GLAD_INCLUDE_DIR "${DEP_DIR}/glad/include")

# stbImage
set(STBIMAGE_INCLUDE_DIR "${DEP_DIR}/stbImage")

# imgui
set(IMGUI_INCLUDE_DIR "${DEP_DIR}/imgui")
set(IMGUI_INCLUDE_BACKEND_DIR "${DEP_DIR}/imgui/backends")

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)


# Vulkan
set(Vulkan_INCLUDE_DIR "/Users/crystalized/dev_envir/VulkanSDK/macOS/include")
set(Vulkan_LIBRARY "/Users/crystalized/dev_envir/VulkanSDK/macOS/lib")
find_package(Vulkan REQUIRED)
message(${Vulkan_FOUND})

# Assimp
find_package(Assimp REQUIRED)




# 设置头文件路径和源文件路径
# FIXME 必须用下面3种include才能编译通过？？
file(GLOB SRC_FILES 
"${SRC_DIR}/*"
"${DEP_DIR}/**.cpp"

if(apple)
"${DEP_DIR}/imgui/*.cpp"
"${DEP_DIR}/imgui/backends/imgui_impl_glfw.cpp"
"${DEP_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
endif
)

file(GLOB INCLUDE_FILES 
"${INCLUDE_DIR}/*"
"${DEP_DIR}/**.h"
)

# include(CTest)
# enable_testing()

# 输出可执行文件
add_executable(PhysicSimu ${INCLUDE_FILES} ${SRC_FILES})

# 编译选项
# target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)

# 可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


# 程序安装包文件输出设置
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE
        ${INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIRS}
        ${GLAD_INCLUDE_DIR}
        ${glm_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${STBIMAGE_INCLUDE_DIR}
        ${Vulkan_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_INCLUDE_BACKEND_DIR}

)

target_link_libraries ( ${PROJECT_NAME} 
    PRIVATE 
        ${PRJ_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
		Eigen3::Eigen
        glfw 
        GLEW::glew_s
        ${EXTRA_LIBS}
        assimp::assimp
)