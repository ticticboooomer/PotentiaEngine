#pragma once
#include "potentia-core/pch.h"

class buffer {
public:
    enum usage
    {
        vertex,
        index,
        uniform
    };
    virtual void initialize(size_t size, usage usg) = 0;
    virtual void map(void* data) = 0;
};