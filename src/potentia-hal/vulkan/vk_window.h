#pragma once

#include <GLFW/glfw3.h>
#include <potentia-core/pch.h>
#include <potentia-hal/interface/window.h>
#include <vulkan/vulkan_structs.hpp>

class vk_window : public window {
public:
  void initialize() override;
  void destroy() override;
  bool should_close() override;
  GLFWwindow *get_window() const { return m_window; };
  vk::Extent2D get_size() const { return m_size; };

protected:
  void init_surface();
  GLFWwindow *m_window;
  vk::Extent2D m_size;
};
