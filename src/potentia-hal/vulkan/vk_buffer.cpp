#include "vk_buffer.h"

#include "potentia-hal/hal_factory.h"

void vk_buffer::initialize(size_t size, usage usg)
{
    m_localSize = size;
    auto bufferUsage = vk::BufferUsageFlagBits::eVertexBuffer;
    if (usg == index)
    {
        bufferUsage = vk::BufferUsageFlagBits::eIndexBuffer;
    }
    else if (usg == uniform)
    {
        bufferUsage = vk::BufferUsageFlagBits::eUniformBuffer;
    }
    auto vkDevice = reinterpret_cast<vk_device *>(hal_factory::instance()->get_device().get());
    m_buffer = vkDevice->get_device().createBuffer(vk::BufferCreateInfo(vk::BufferCreateFlags(), size, bufferUsage));
    m_requirements = vkDevice->get_device().getBufferMemoryRequirements(m_buffer);
    uint32_t memoryTypeIndex = find_memory_type(vkDevice, m_requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    m_memory = vkDevice->get_device().allocateMemory(vk::MemoryAllocateInfo(m_requirements.size, memoryTypeIndex));
}

void vk_buffer::map(void *data)
{
    auto vkDevice = reinterpret_cast<vk_device *>(hal_factory::instance()->get_device().get());
    vkDevice->get_device().bindBufferMemory(m_buffer, m_memory, 0);
    uint8_t *pData = static_cast<uint8_t *>(vkDevice->get_device().mapMemory(m_memory, 0, m_requirements.size));
    memcpy(pData, data, m_requirements.size);
    vkDevice->get_device().unmapMemory(m_memory);
}

uint32_t vk_buffer::find_memory_type(vk_device *dev, uint32_t typeBits, vk::MemoryPropertyFlags requirementMask)
{
    auto memoryProperties = dev->get_mem_properties();
    uint32_t typeIndex = uint32_t(~0);
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((typeBits & 1) && ((memoryProperties.memoryTypes[i].propertyFlags & requirementMask) == requirementMask))
        {
            typeIndex = i;
            break;
        }
        typeBits >>= 1;
    }
    assert(typeIndex != uint32_t(~0));
    return typeIndex;
}
