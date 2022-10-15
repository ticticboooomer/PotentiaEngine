#pragma once

#include <potentia-core/pch.h>

class device {
  public:
    virtual void initialize() = 0;
    virtual void init_physical() = 0;
    virtual void destroy() = 0;
    
};
