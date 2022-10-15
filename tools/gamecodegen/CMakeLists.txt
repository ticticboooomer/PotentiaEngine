peoject(PotentiaTools_GameCodeGen)

file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*.cpp" "src/*/*.h" "src/*/*.cpp" )

add_executable(PotentiaTools_GameCodeGen ${SRC_FILES})
target_include_directories(PotentiaTools_GameCodeGen PUBLIC "./src")
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(PotentiaTools_GameCodeGen PRIVATE CLI11::CLI11)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(PotentiaTools_GameCodeGen PRIVATE assimp::assimp)
