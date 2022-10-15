#pragma once

#include "potentia-hal/interface/commander.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_pipeline.h"
#include "potentia-hal/vulkan/vk_surface.h"
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_handles.hpp>
#include "potentia-hal/interface/buffer.h"

class vk_commander : public commander {

public:
  vk_commander();
  void init(vk_pipeline* pipeline);
  void wait() override;
  void begin() override;
  void draw(uint32_t vertexCount) override;
  void end() override;
  void bind_vertex_buffer(buffer* buff) override;
protected:
  vk::CommandBuffer m_buffer;
  vk_device* vkDevice;
  vk_surface* vkSurface;
  vk_pipeline* pipeline;
  vk::Semaphore imageAquired;
  vk::ResultValue<uint32_t> currentBuffer;
};
