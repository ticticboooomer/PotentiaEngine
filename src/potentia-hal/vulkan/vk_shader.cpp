#include "vk_shader.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/vulkan/vk_device.h"
#include <fstream>
#include <string>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
#include <filesystem>

void vk_shader::init_from_file(const std::string& path) {
	auto absPath = std::filesystem::absolute(path).string();
	std::ifstream file(absPath, std::ios::ate | std::ios::binary);

	size_t fileSize = file.tellg();
	std::vector<unsigned int> buffer(fileSize);

	file.seekg(0);
	file.read((char*)buffer.data(), fileSize);

	file.close();

	vk::ShaderModuleCreateInfo createInfo(vk::ShaderModuleCreateFlags(),
		buffer.size(), buffer.data());
	auto device = hal_factory::instance()->get_device();
	auto vkDevice = reinterpret_cast<vk_device*>(device.get());
	module = vkDevice->get_device().createShaderModule(createInfo);
}

void vk_shader::destroy() {
	auto device = hal_factory::instance()->get_device();
	auto vkDevice = reinterpret_cast<vk_device*>(device.get());
	vkDevice->get_device().destroyShaderModule(module);
}

vk::PipelineShaderStageCreateInfo vk_shader::get_stage_info() const {
	auto shaderType = vk::ShaderStageFlagBits::eFragment;
	if (m_type == vertex) {
		shaderType = vk::ShaderStageFlagBits::eVertex;
	}
	vk::PipelineShaderStageCreateInfo createInfo(vk::PipelineShaderStageCreateFlags(), shaderType, module, "main", nullptr);
	return createInfo;
}

