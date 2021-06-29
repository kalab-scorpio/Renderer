cmake_minimum_required(VERSION "3.17")

# name of this example project
project(opengl)

set(CMAKE_CXX_STANDARD 14)

# find_package( OpenGL REQUIRED )

# find_package(glm REQUIRED)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#m is a library for glm
set(LIBS glfw GL GLEW m)


# tell the build to include the headers from OpenCV
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION .)
configure_file(${CMAKE_SOURCE_DIR}/res/shader/Basic.glsl res/shader/Basic.glsl)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX}/res)
# file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/stb_image/*.h")
	# "${CMAKE_SOURCE_DIR}/include" )

# specify the executable target to be
# file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION .)
# file(COPY ${CMAKE_SOURCE_DIR}/src/vendor DESTINATION .)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# tell it to link the executable target against OpenCV
target_link_libraries(${PROJECT_NAME} ${LIBS} )
