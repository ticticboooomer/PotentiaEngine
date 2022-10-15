#pragma once

#include <potentia-core/pch.h>
#include "buffer.h"

class commander {
public:
  virtual void wait() = 0;
  virtual void begin() = 0;
  virtual void end() = 0;
  virtual void draw(uint32_t vertexCount) = 0;
  virtual void bind_vertex_buffer(buffer* buff) = 0;
};
