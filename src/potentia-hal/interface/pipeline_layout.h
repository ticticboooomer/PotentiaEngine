#pragma once

#include "potentia-hal/interface/shader.h"
#include <memory>
#include <potentia-core/pch.h>

class pipeline_layout {
  public:
  virtual void initialize() = 0;
  virtual void destroy() = 0;
  virtual void finalize() = 0;
  virtual shader* create_shader() = 0;
  virtual void init_vertex_desc(size_t stride) = 0;
};

