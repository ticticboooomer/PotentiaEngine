project(PotentiaTools_AssetBundling)

file (GLOB_RECURSE ASSET_BUNDLER_FILES "./src/*/*.h" "./src/*/*.cpp" "./src/*.h" "./src/*.cpp")
add_executable(PotentiaTool_AssetBundler ${ASSET_BUNDLER_FILES})
target_include_directories(PotentiaTool_AssetBundler PUBLIC "./src")
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(PotentiaTool_AssetBundler PRIVATE CLI11::CLI11)
