#include "vk_commander.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_surface.h"
#include <cstdint>
#include <iostream>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include "vk_buffer.h"

vk_commander::vk_commander(): currentBuffer(vk::Result::eSuccess, 0u) {

}
void vk_commander::init(vk_pipeline *pipeline) {
  this->pipeline = pipeline;
  auto device = hal_factory::instance()->get_device();
  vkDevice = reinterpret_cast<vk_device *>(device.get());
  auto surface = hal_factory::instance()->get_surface();
  vkSurface = reinterpret_cast<vk_surface *>(surface.get());

  m_buffer = vkDevice->create_command_buffer();
}

void vk_commander::wait() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  vkDevice->get_device().waitIdle();
}

void vk_commander::begin() {
  wait();
  imageAquired =
      vkDevice->get_device().createSemaphore(vk::SemaphoreCreateInfo());
  currentBuffer = vkDevice->get_device().acquireNextImageKHR(
      vkSurface->get_swapchain(), 100000000, imageAquired, nullptr);
  assert(currentBuffer.result == vk::Result::eSuccess);
  assert(currentBuffer.value < vkSurface->get_framebuffer_count());
  m_buffer.reset(vk::CommandBufferResetFlags(0));
  m_buffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlags()));
  std::array<vk::ClearValue, 2> clearValues;
  clearValues[0].color =
      vk::ClearColorValue(std::array<float, 4>({{0.2f, 0.5f, 0.2f, 0.2f}}));
  clearValues[1].depthStencil = vk::ClearDepthStencilValue(1.0f, 0);
  vk::RenderPassBeginInfo renderPassBeginInfo(
      vkSurface->get_render_pass(),
      vkSurface->get_framebuffer(currentBuffer.value),
      vk::Rect2D(vk::Offset2D(0, 0), vkSurface->get_extent()), clearValues);
  m_buffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
  m_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics,
                        pipeline->get_pipeline());

  m_buffer.setViewport(
      0, vk::Viewport(
             0.0f, 0.0f, static_cast<float>(vkSurface->get_extent().width),
             static_cast<float>(vkSurface->get_extent().height), 0.0f, 1.0f));
  m_buffer.setScissor(0,
                      vk::Rect2D(vk::Offset2D(0, 0), vkSurface->get_extent()));
}

void vk_commander::end() {
  m_buffer.endRenderPass();
  m_buffer.end();
  vk::Fence drawFence =
      vkDevice->get_device().createFence(vk::FenceCreateInfo());

  vk::PipelineStageFlags waitDestinationStageMask(
      vk::PipelineStageFlagBits::eColorAttachmentOutput);
  vk::SubmitInfo submitInfo(imageAquired, waitDestinationStageMask, m_buffer);
  vkDevice->get_graphics_queue().submit(submitInfo, drawFence);
  while (vk::Result::eTimeout ==
         vkDevice->get_device().waitForFences(drawFence, VK_TRUE, 100000000))
    ;
  auto swapchain = vkSurface->get_swapchain();
  vk::Result result = vkDevice->get_present_queue().presentKHR(
      vk::PresentInfoKHR({}, swapchain, currentBuffer.value));
}

void vk_commander::draw(uint32_t vertexCount) {
  m_buffer.draw(3, 1, 0, 0);
}


void  vk_commander::bind_vertex_buffer(buffer* buff) {
  m_buffer.bindVertexBuffers(0, ((vk_buffer*)buff)->get_buffer(), {0});
}