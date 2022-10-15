#pragma once

#include "commander.h"
#include "pipeline_layout.h"
#include <potentia-core/pch.h>

class pipeline {
public:
  virtual void initialize(std::shared_ptr<pipeline_layout> layout) = 0;
  virtual void destroy() = 0;
  virtual std::shared_ptr<commander> get_commander() = 0;
};
