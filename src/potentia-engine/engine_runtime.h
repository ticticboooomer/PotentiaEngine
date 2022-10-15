#pragma once

#include "potentia-core/pch.h"
#include <memory>

class engine_runtime {
public:
  engine_runtime();
  void run();
  static std::shared_ptr<engine_runtime> create_instance();
protected:
};
