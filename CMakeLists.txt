cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  Potentia
  VERSION 0.0.1.0
  LANGUAGES CXX)

file(GLOB_RECURSE ENGINE_FILES "src/**/*.h" "src/**/*.cpp")
add_library(PotentiaEngine ${ENGINE_FILES})
target_include_directories(PotentiaEngine PUBLIC "./src/")
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(PotentiaEngine PUBLIC Eigen3::Eigen)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(PotentiaEngine PUBLIC glfw)
find_package(glm CONFIG REQUIRED)
target_link_libraries(PotentiaEngine PUBLIC glm::glm)
find_package(Vulkan REQUIRED)
target_link_libraries(PotentiaEngine PUBLIC Vulkan::Vulkan)
target_link_libraries(PotentiaEngine PUBLIC Vulkan::Headers)
add_subdirectory(./samples/)
add_subdirectory(./tools)
