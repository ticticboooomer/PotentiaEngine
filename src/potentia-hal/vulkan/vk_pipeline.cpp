#include "vk_pipeline.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/interface/commander.h"
#include "potentia-hal/vulkan/vk_commander.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_pipeline_layout.h"
#include "potentia-hal/vulkan/vk_shader.h"
#include "potentia-hal/vulkan/vk_surface.h"
#include <array>
#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_structs.hpp>

void vk_pipeline::initialize(std::shared_ptr<pipeline_layout> layout) {
  auto vkLayout = reinterpret_cast<vk_pipeline_layout *>(layout.get());
  vkLayout->finalize();

  auto surface = hal_factory::instance()->get_surface();
  auto vkSurface = reinterpret_cast<vk_surface*>(surface.get());
  std::vector<vk::PipelineShaderStageCreateInfo> shaderCreateInfo;
  for (const auto &shader : vkLayout->get_shaders()) {
    shaderCreateInfo.push_back(shader->get_stage_info());
  }
  m_layout = vkLayout->get_layout();
  auto binding = vkLayout->get_vertex_binding();
  vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
      vk::PipelineVertexInputStateCreateFlags(), 1, &binding, 1,
      vkLayout->get_vertex_layout().data());

  vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
      vk::PipelineInputAssemblyStateCreateFlags(),
      vk::PrimitiveTopology::eTriangleList);

  vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
      vk::PipelineViewportStateCreateFlags(), 1, nullptr, 1, nullptr);

  vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
      vk::PipelineRasterizationStateCreateFlags(), // flags
      false,                                       // depthClampEnable
      false,                                       // rasterizerDiscardEnable
      vk::PolygonMode::eFill,                      // polygonMode
      vk::CullModeFlagBits::eBack,                 // cullMode
      vk::FrontFace::eClockwise,                   // frontFace
      false,                                       // depthBiasEnable
      0.0f,                                        // depthBiasConstantFactor
      0.0f,                                        // depthBiasClamp
      0.0f,                                        // depthBiasSlopeFactor
      1.0f                                         // lineWidth
  );

  vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
      vk::PipelineMultisampleStateCreateFlags(), // flags
      vk::SampleCountFlagBits::e1                // rasterizationSamples
                                                 // other values can be default
  );

  vk::StencilOpState stencilOpState(vk::StencilOp::eKeep, vk::StencilOp::eKeep,
                                    vk::StencilOp::eKeep,
                                    vk::CompareOp::eAlways);
  vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
      vk::PipelineDepthStencilStateCreateFlags(), // flags
      true,                                       // depthTestEnable
      true,                                       // depthWriteEnable
      vk::CompareOp::eLessOrEqual,                // depthCompareOp
      false,                                      // depthBoundTestEnable
      false,                                      // stencilTestEnable
      stencilOpState,                             // front
      stencilOpState                              // back
  );

  vk::ColorComponentFlags colorComponentFlags(
      vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
      vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
  vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
      false,                  // blendEnable
      vk::BlendFactor::eZero, // srcColorBlendFactor
      vk::BlendFactor::eZero, // dstColorBlendFactor
      vk::BlendOp::eAdd,      // colorBlendOp
      vk::BlendFactor::eZero, // srcAlphaBlendFactor
      vk::BlendFactor::eZero, // dstAlphaBlendFactor
      vk::BlendOp::eAdd,      // alphaBlendOp
      colorComponentFlags     // colorWriteMask
  );
  vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
      vk::PipelineColorBlendStateCreateFlags(), // flags
      false,                                    // logicOpEnable
      vk::LogicOp::eNoOp,                       // logicOp
      pipelineColorBlendAttachmentState,        // attachments
      {{1.0f, 1.0f, 1.0f, 1.0f}}                // blendConstants
  );

  std::array<vk::DynamicState, 2> dynamicStates = {vk::DynamicState::eViewport,
                                                   vk::DynamicState::eScissor};
  vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
      vk::PipelineDynamicStateCreateFlags(), dynamicStates);

  vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo(
      vk::PipelineCreateFlags(),             // flags
      shaderCreateInfo,                      // stages
      &pipelineVertexInputStateCreateInfo,                     // pVertexInputState
      &pipelineInputAssemblyStateCreateInfo, // pInputAssemblyState
      nullptr,                               // pTessellationState
      &pipelineViewportStateCreateInfo,      // pViewportState
      &pipelineRasterizationStateCreateInfo, // pRasterizationState
      &pipelineMultisampleStateCreateInfo,   // pMultisampleState
      &pipelineDepthStencilStateCreateInfo,  // pDepthStencilState
      &pipelineColorBlendStateCreateInfo,    // pColorBlendState
      &pipelineDynamicStateCreateInfo,       // pDynamicState
      vkLayout->get_layout(),                // layout
      vkSurface->get_render_pass()
  );

  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  
  vk::Result res;

  std::tie(res, m_pipeline) = vkDevice->get_device().createGraphicsPipeline(nullptr, graphicsPipelineCreateInfo);
}

std::shared_ptr<commander> vk_pipeline::get_commander() {
  auto commander = std::make_shared<vk_commander>();
  commander->init(this);
  return commander;
}

void vk_pipeline::destroy() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  vkDevice->get_device().destroyRenderPass(m_renderPass);
  vkDevice->get_device().destroyPipeline(m_pipeline);
}
