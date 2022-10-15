#pragma once

#include "potentia-hal/interface/pipeline_layout.h"
#include "potentia-hal/vulkan/vk_shader.h"
#include <vector>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

class vk_pipeline_layout : public pipeline_layout {
public:
  void initialize() override;
  void destroy() override;
  void finalize() override;
  void init_vertex_desc(size_t stride) override;
  vk::PipelineLayout get_layout() const { return m_layout; };
  shader *create_shader() override;
  std::vector<vk_shader*> get_shaders() const { return m_shaders; };
  vk::VertexInputBindingDescription get_vertex_binding() const {return vertexInputBindingDescription;};
  std::array<vk::VertexInputAttributeDescription, 1> get_vertex_layout() const {return vertexInputAttributeDescriptions; };

protected:
  vk::DescriptorSetLayout m_descSetLayout;
  vk::PipelineLayout m_layout;
  std::vector<vk_shader*> m_shaders;
  vk::VertexInputBindingDescription vertexInputBindingDescription;
  std::array<vk::VertexInputAttributeDescription, 1>
      vertexInputAttributeDescriptions;
};
