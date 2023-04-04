#include "vk_window.h"
#include "GLFW/glfw3.h"
#include "potentia-core/config/config_strings.h"

void vk_window::initialize() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  m_window = glfwCreateWindow(
      1500, 1000,
      config_strings::instance()->get_value(game_window_title).c_str(), nullptr,
      nullptr);
  m_size = vk::Extent2D(1920, 1068);
}

bool vk_window::should_close() { return glfwWindowShouldClose(m_window); }

void vk_window::destroy() {

}
