#include "hal_factory.h"
#include "potentia-engine/levels/level_manager.h"
#include "potentia-hal/interface/pipeline.h"
#include "potentia-hal/interface/pipeline_layout.h"
#include "potentia-hal/vulkan/vk_buffer.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_pipeline.h"
#include "potentia-hal/vulkan/vk_pipeline_layout.h"
#include "potentia-hal/vulkan/vk_surface.h"
#include "potentia-hal/vulkan/vk_window.h"
#include <memory>

void hal_factory::initialize() {
  m_window = std::make_shared<vk_window>();
  m_surface = std::make_shared<vk_surface>();
  m_device = std::make_shared<vk_device>();
  m_window->initialize();
  m_device->init_physical();
  m_surface->pre_init();
  m_device->initialize();
  m_surface->initialize();
}

void hal_factory::destroy() {
  m_surface->destroy();
  m_device->destroy();
  m_window->destroy();
}

void hal_factory::run() {
  while (!m_window->should_close()) {
    glfwPollEvents();
    level_manager::instance()->run_for_active([](g_level *level) {
      level->tick();
      level->render();
    });
  }
}

std::shared_ptr<pipeline_layout> hal_factory::create_pipeline_layout() {
  auto layout = std::make_shared<vk_pipeline_layout>();
  layout->initialize();
  return layout;
}

std::shared_ptr<pipeline>
hal_factory::create_pipeline(std::shared_ptr<pipeline_layout> layout) {
  std::shared_ptr<vk_pipeline> pipeline = std::make_shared<vk_pipeline>();
  pipeline->initialize(layout);
  return pipeline;
}

std::shared_ptr<buffer> hal_factory::create_buffer(size_t size,
                                                   buffer::usage usg) {
  std::shared_ptr<vk_buffer> buffer = std::make_shared<vk_buffer>();
  buffer->initialize(size, usg);
  return buffer;
}
