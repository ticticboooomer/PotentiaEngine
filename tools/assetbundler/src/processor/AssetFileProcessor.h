#pragma once

#include "../common.h"
#include <string>
#include <memory>

class AssetFileProcessor {
  public:
  virtual bool IsFileType(const std::string& file) = 0;
  virtual TaggedBundleSegment Process(const std::string& file) = 0;
};
