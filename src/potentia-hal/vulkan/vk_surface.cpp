#include "vk_surface.h"
#include "glm/common.hpp"
#include "potentia-core/error.h"
#include "potentia-hal/hal_factory.h"
#include "potentia-hal/vulkan/vk_device.h"
#include "potentia-hal/vulkan/vk_window.h"
#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/glm.hpp>
#include <limits>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>


void vk_surface::pre_init() {
    VkSurfaceKHR surface;

  auto wind = hal_factory::instance()->get_window();
  auto vkWindow = reinterpret_cast<vk_window *>(wind.get());

  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  auto result = glfwCreateWindowSurface(static_cast<VkInstance>(vkDevice->get_instance()),
                          vkWindow->get_window(), nullptr, &surface);
  m_surface = vk::SurfaceKHR(surface);
}

void vk_surface::initialize() {
  auto wind = hal_factory::instance()->get_window();
  auto vkWindow = reinterpret_cast<vk_window *>(wind.get());

  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  auto formats = vkDevice->get_physical().getSurfaceFormatsKHR(m_surface);
  assert(!formats.empty());

  vk::Format format = (formats[0].format == vk::Format::eUndefined)
                          ? vk::Format::eB8G8R8A8Unorm
                          : formats[0].format;
  auto surfaceCaps =
      vkDevice->get_physical().getSurfaceCapabilitiesKHR(m_surface);

  vk::Extent2D swapChainExtent;

  if (surfaceCaps.currentExtent.width == std::numeric_limits<uint32_t>::max()) {
    swapChainExtent.width =
        glm::clamp(vkWindow->get_size().width, surfaceCaps.minImageExtent.width,
                   surfaceCaps.maxImageExtent.width);
    swapChainExtent.height = glm::clamp(vkWindow->get_size().height,
                                        surfaceCaps.minImageExtent.height,
                                        surfaceCaps.maxImageExtent.height);
  } else {
    swapChainExtent = surfaceCaps.currentExtent;
  }

  auto swapChainPresentMode = vk::PresentModeKHR::eFifo;

  auto preTransform = (surfaceCaps.supportedTransforms &
                       vk::SurfaceTransformFlagBitsKHR::eIdentity)
                          ? vk::SurfaceTransformFlagBitsKHR::eIdentity
                          : surfaceCaps.currentTransform;
  vk::CompositeAlphaFlagBitsKHR compositeAlpha =
      (surfaceCaps.supportedCompositeAlpha &
       vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
          ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
      : (surfaceCaps.supportedCompositeAlpha &
         vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
          ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
      : (surfaceCaps.supportedCompositeAlpha &
         vk::CompositeAlphaFlagBitsKHR::eInherit)
          ? vk::CompositeAlphaFlagBitsKHR::eInherit
          : vk::CompositeAlphaFlagBitsKHR::eOpaque;

  vk::SwapchainCreateInfoKHR swapChainCreateInfo(
      vk::SwapchainCreateFlagsKHR(), m_surface, surfaceCaps.minImageCount,
      format, vk::ColorSpaceKHR::eSrgbNonlinear, swapChainExtent, 1,
      vk::ImageUsageFlagBits::eColorAttachment, vk::SharingMode::eExclusive, {},
      preTransform, compositeAlpha, swapChainPresentMode, true, nullptr);

  uint32_t queueFamilyIndices[2] = {vkDevice->get_graphics_qfi(),
                                    vkDevice->get_present_qfi()};

  if (vkDevice->get_graphics_qfi() != vkDevice->get_present_qfi()) {
    swapChainCreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
    swapChainCreateInfo.queueFamilyIndexCount = 2;
    swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
  }

  m_swapChain = vkDevice->get_device().createSwapchainKHR(swapChainCreateInfo);

  std::vector<vk::Image> swapChainImages =
      vkDevice->get_device().getSwapchainImagesKHR(m_swapChain);
  init_depth_buffer();
  init_render_pass();
  std::vector<vk::ImageView> imageViews;
  imageViews.reserve(swapChainImages.size());
  vk::ImageViewCreateInfo imageViewCreateInfo(
      {}, {}, vk::ImageViewType::e2D, format, {},
      {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

  vk::ImageView attachments[3];
  attachments[1] = m_depthView;

  vk::FramebufferCreateInfo framebufferCreateInfo(
        vk::FramebufferCreateFlags(), m_renderPass, m_depthView ? 2 : 1, attachments, swapChainExtent.width, swapChainExtent.height, 1 );
  for (auto image : swapChainImages) {
    imageViewCreateInfo.image = image;
      auto view = vkDevice->get_device().createImageView(imageViewCreateInfo);
    imageViews.push_back(view);
      attachments[0] = view;
    m_frameBuffers.push_back(vkDevice->get_device().createFramebuffer(framebufferCreateInfo));
  }

  m_images = swapChainImages;
  m_imageViews = imageViews;
  m_extent = swapChainExtent;
}

void vk_surface::init_depth_buffer() {

  const vk::Format format = vk::Format::eD16Unorm;
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  vk::FormatProperties formatProps =
      vkDevice->get_physical().getFormatProperties(format);

  vk::ImageTiling tiling;
  if (formatProps.linearTilingFeatures &
      vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
    tiling = vk::ImageTiling::eLinear;
  } else if (formatProps.optimalTilingFeatures &
             vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
    tiling = vk::ImageTiling::eOptimal;
  } else {
    THROW_P000003;
  }
  auto wind = hal_factory::instance()->get_window();
  auto vkWindow = reinterpret_cast<vk_window *>(wind.get());

  vk::ImageCreateInfo imageCreateInfo(
      vk::ImageCreateFlags(), vk::ImageType::e2D, format,
      vk::Extent3D(vkWindow->get_size(), 1), 1, 1, vk::SampleCountFlagBits::e1,
      tiling, vk::ImageUsageFlagBits::eDepthStencilAttachment);

  m_depthImage = vkDevice->get_device().createImage(imageCreateInfo);

  vk::PhysicalDeviceMemoryProperties memoryProps =
      vkDevice->get_physical().getMemoryProperties();
  vk::MemoryRequirements memoryReqs =
      vkDevice->get_device().getImageMemoryRequirements(m_depthImage);

  uint32_t typeBits = memoryReqs.memoryTypeBits;
  uint32_t typeIndex = ~0;

  for (uint32_t i = 0; i < memoryProps.memoryTypeCount; i++) {
    if ((typeBits & 1) && ((memoryProps.memoryTypes[i].propertyFlags &
                            vk::MemoryPropertyFlagBits::eDeviceLocal) ==
                           vk::MemoryPropertyFlagBits::eDeviceLocal)) {
      typeIndex = i;
      break;
    }
    typeBits >>= 1;
  }
  assert(typeIndex != ~0);
  vk::DeviceMemory depthMemory = vkDevice->get_device().allocateMemory(
      vk::MemoryAllocateInfo(memoryReqs.size, typeIndex));

  vkDevice->get_device().bindImageMemory(m_depthImage, depthMemory, 0);

  m_depthView = vkDevice->get_device().createImageView(vk::ImageViewCreateInfo(
      vk::ImageViewCreateFlags(), m_depthImage, vk::ImageViewType::e2D, format,
      {}, {vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1}));
}

void vk_surface::destroy() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  auto dev = vkDevice->get_device();
  dev.destroyRenderPass(m_renderPass);
  dev.destroyImageView(m_depthView);
  dev.freeMemory(m_depthMemory);
  dev.destroyImage(m_depthImage);

  for (auto imgV : m_imageViews) {
    dev.destroyImageView(imgV);
  }

  dev.destroySwapchainKHR(m_swapChain);
  vkDevice->get_instance().destroySurfaceKHR(m_surface);
}

vk::SurfaceFormatKHR vk_surface::get_surface_format() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());

  auto formats = vkDevice->get_physical().getSurfaceFormatsKHR(m_surface);

  auto pickedFormat = formats[0];
  if (formats.size() == 1) {
    if (formats[0].format == vk::Format::eUndefined) {
      pickedFormat.format = vk::Format::eB8G8R8A8Unorm;
      pickedFormat.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
    }
  } else {
    // request several formats, the first found will be used
    vk::Format requestedFormats[] = {
        vk::Format::eB8G8R8A8Unorm, vk::Format::eR8G8B8A8Unorm,
        vk::Format::eB8G8R8Unorm, vk::Format::eR8G8B8Unorm};
    vk::ColorSpaceKHR requestedColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
    for (size_t i = 0;
         i < sizeof(requestedFormats) / sizeof(requestedFormats[0]); i++) {
      vk::Format requestedFormat = requestedFormats[i];
      auto it = std::find_if(formats.begin(), formats.end(),
                             [requestedFormat, requestedColorSpace](
                                 vk::SurfaceFormatKHR const &f) {
                               return (f.format == requestedFormat) &&
                                      (f.colorSpace == requestedColorSpace);
                             });
      if (it != formats.end()) {
        pickedFormat = *it;
        break;
      }
    }
  }
  assert(pickedFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear);
  return pickedFormat;
}

void vk_surface::init_render_pass() {
  auto device = hal_factory::instance()->get_device();
  auto vkDevice = reinterpret_cast<vk_device *>(device.get());
  auto surfaceFormat = get_surface_format().format;
  auto depthFormat = vk::Format::eD16Unorm;

  std::array<vk::AttachmentDescription, 2> attachmentDescriptions;
  attachmentDescriptions[0] = vk::AttachmentDescription(
      vk::AttachmentDescriptionFlags(), surfaceFormat,
      vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear,
      vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare,
      vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined,
      vk::ImageLayout::ePresentSrcKHR);
  attachmentDescriptions[1] = vk::AttachmentDescription(
      vk::AttachmentDescriptionFlags(), depthFormat,
      vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear,
      vk::AttachmentStoreOp::eDontCare, vk::AttachmentLoadOp::eDontCare,
      vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined,
      vk::ImageLayout::eDepthStencilAttachmentOptimal);
  vk::AttachmentReference colorReference(
      0, vk::ImageLayout::eColorAttachmentOptimal);
  vk::AttachmentReference depthReference(
      1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

  vk::SubpassDescription subpass(vk::SubpassDescriptionFlags(),
                                 vk::PipelineBindPoint::eGraphics, {},
                                 colorReference, {}, &depthReference);

  m_renderPass =
      vkDevice->get_device().createRenderPass(vk::RenderPassCreateInfo(
          vk::RenderPassCreateFlags(), attachmentDescriptions, subpass));
}
