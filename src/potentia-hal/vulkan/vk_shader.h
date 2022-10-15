#pragma once
#include "potentia-hal/interface/shader.h"
#include <potentia-core/pch.h>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

class vk_shader : public shader {
public:
  void init_from_file(const std::string &path) override;
  void destroy() override;
  type get_type() override { return m_type; };
  void set_type(type type) override { m_type = type; };
  vk::PipelineShaderStageCreateInfo get_stage_info() const;
protected:
  vk::ShaderModule module;
  type m_type;
};
