#pragma once

#include "potentia-hal/interface/surface.h"
#include <potentia-core/pch.h>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

class vk_surface : public surface {
public:
  void pre_init() override;
  void initialize() override;
  vk::SurfaceKHR get_surface() const { return m_surface; };
  void destroy() override;
  vk::SurfaceFormatKHR get_surface_format();
  vk::Framebuffer get_framebuffer(size_t i) const { return m_frameBuffers[i]; };
  vk::Extent2D get_extent() const { return m_extent; };
  vk::SwapchainKHR get_swapchain() const { return m_swapChain; }
  vk::RenderPass get_render_pass() const { return m_renderPass; };
  size_t get_framebuffer_count() const { return m_frameBuffers.size(); };
protected:
  void init_depth_buffer();
  void init_render_pass();
  vk::SurfaceKHR m_surface;
  vk::SwapchainKHR m_swapChain;
  std::vector<vk::Image> m_images;
  std::vector<vk::ImageView> m_imageViews;
  std::vector<vk::Framebuffer> m_frameBuffers;
  vk::Image m_depthImage;
  vk::DeviceMemory m_depthMemory;
  vk::ImageView m_depthView;
  vk::RenderPass m_renderPass;
  vk::Extent2D m_extent;
};
