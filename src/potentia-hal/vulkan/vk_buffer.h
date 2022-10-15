#pragma once
#include "potentia-hal/interface/buffer.h"
#include <vulkan/vulkan.hpp>
#include "vk_device.h"

class vk_buffer : public buffer
{
public:
    void initialize(size_t size, usage usg) override;
    void map(void *data) override;
    vk::Buffer get_buffer() const { return m_buffer; };

protected:
    uint32_t find_memory_type(vk_device *dev, uint32_t typeBits, vk::MemoryPropertyFlags requirementMask);
    vk::Buffer m_buffer;
    vk::MemoryRequirements m_requirements;
    vk::DeviceMemory m_memory;
    size_t m_localSize;
};