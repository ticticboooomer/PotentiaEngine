#include "common.h"
#include "io/file_desc.h"
#include <vector>
#include <filesystem>

class file_manager {
public:
  static std::vector<file_desc> enumerate(std::string root);
private:
  static file_desc describe(std::filesystem::path file);
};
