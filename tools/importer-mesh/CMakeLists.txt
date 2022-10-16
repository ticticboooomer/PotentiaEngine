project(PotentiaTools_MeshImporter)

file (GLOB_RECURSE SRC_FILES "./src/*/*.h" "./src/*/*.cpp" "./src/*.h" "./src/*.cpp")
add_executable(PotentiaTool_ImporterMesh ${SRC_FILES})
target_include_directories(PotentiaTool_ImporterMesh PUBLIC "./src")
find_package(assimp CONFIG REQUIRED)
target_link_libraries(PotentiaTool_ImporterMesh PRIVATE assimp::assimp)