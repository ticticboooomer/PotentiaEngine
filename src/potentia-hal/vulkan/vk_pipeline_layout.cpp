#include "vk_pipeline_layout.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/interface/shader.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_shader.h"
#include <memory>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

void vk_pipeline_layout::destroy()
{
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  vkDevice->get_device().destroyPipelineLayout(m_layout);
  vkDevice->get_device().destroyDescriptorSetLayout(m_descSetLayout);
}

void vk_pipeline_layout::finalize()
{
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  std::vector<vk::DescriptorSetLayoutBinding> bindings;
  m_descSetLayout = vkDevice->get_device().createDescriptorSetLayout(vk::DescriptorSetLayoutCreateInfo(vk::DescriptorSetLayoutCreateFlags(), bindings));
  m_layout = vkDevice->get_device().createPipelineLayout(vk::PipelineLayoutCreateInfo(vk::PipelineLayoutCreateFlags(), m_descSetLayout));
}
shader *vk_pipeline_layout::create_shader()
{
  auto shader = new vk_shader();
  m_shaders.push_back(shader);
  return shader;
}

void vk_pipeline_layout::initialize()
{
}

void vk_pipeline_layout::init_vertex_desc(size_t stride)
{
  vertexInputBindingDescription = vk::VertexInputBindingDescription(0, stride);
  vertexInputAttributeDescriptions = {
      vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32A32Sfloat, 0)};
}
