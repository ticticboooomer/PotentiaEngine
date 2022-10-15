#pragma once
#include <potentia-core/pch.h>

class g_runnable {
public:
  virtual void setup() = 0;
  virtual void tick() = 0;
  virtual void render() = 0;
  virtual void cleanup();
};
