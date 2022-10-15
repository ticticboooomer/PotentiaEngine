#pragma once

#include <potentia-core/pch.h>

class surface {
  public:
  virtual void pre_init() = 0;
    virtual void initialize() = 0; 
    virtual void destroy() = 0;
};
