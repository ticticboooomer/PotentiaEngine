#include "file_manager.h"
#include "io/file_desc.h"
#include <vector>
#include <filesystem>

std::vector<file_desc> file_manager::enumerate(std::string root) {
  auto dir_iter = std::filesystem::recursive_directory_iterator(root);
  std::vector<file_desc> result;
  for (const auto & file : dir_iter) {
    if (std::filesystem::is_directory(file)){
      continue;
    }
    result.push_back(describe(file));
  }
  return result;
}

file_desc file_manager::describe(std::filesystem::path file) {
  return {
    file.filename().string(),
    file.extension().string(),
    file.string()
  };
}

