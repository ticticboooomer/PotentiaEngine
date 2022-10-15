#pragma once

#include "potentia-hal/interface/pipeline.h"
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

class vk_pipeline : public pipeline {
public:
  void initialize(std::shared_ptr<pipeline_layout> layout) override;
  void destroy() override;
  std::shared_ptr<commander> get_commander() override;
  void init_vertex_input(size_t stride);
  vk::Pipeline get_pipeline() const {return m_pipeline; }; 
  vk::PipelineLayout get_layout() const {return m_layout; }

protected:
  vk::PipelineVertexInputStateCreateInfo vertexInputState;
  vk::RenderPass m_renderPass;
  vk::Pipeline m_pipeline;
  vk::PipelineLayout m_layout;
};
