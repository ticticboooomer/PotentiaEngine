project(PotentiaTools_Importer)

file (GLOB_RECURSE SRC_FILES "./src/*/*.h" "./src/*/*.cpp" "./src/*.h" "./src/*.cpp")
add_executable(PotentiaTool_Importer ${SRC_FILES})
target_include_directories(PotentiaTool_Importer PUBLIC "./src")
find_package(assimp CONFIG REQUIRED)
target_link_libraries(PotentiaTool_Importer PRIVATE assimp::assimp)
