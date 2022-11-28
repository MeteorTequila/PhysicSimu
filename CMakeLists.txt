cmake_minimum_required(VERSION 3.0.0)
project(PhysicSimu VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
# 不设置会出现 Undefined symbols错误，主要是因为GLFW3的动态库没有链接上
set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(glfw3 REQUIRED)

# 第三方文件目录
set(DEP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(GLAD_INCLUDE "${DEP_INCLUDE}/glad/include")
set(STBIMAGE_INCLUDE "${DEP_INCLUDE}/stbImage")

# 设置源文件和头文件目录
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")


# 源文件集合和头文件集合
file(GLOB SRC_DIR_FILES "${SRC_DIR}/*")
file(GLOB INCLUDE_DIR_FILES "${INCLUDE_DIR}/*")

# include(CTest)
# enable_testing()

add_executable(PhysicSimu ${INCLUDE_DIR_FILES} ${SRC_DIR_FILES})

# 设置exe输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE
        ${INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIRS}
        ${GLAD_INCLUDE}
        ${STBIMAGE_INCLUDE}
		
)

target_link_libraries ( ${PROJECT_NAME} 
    PRIVATE 
        ${PRJ_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
		Eigen3::Eigen
        glfw
		
)