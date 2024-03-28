#include "ShaderResourceManager.h"
#include "Core/Graphics/Renderer/ShaderManager.h"

namespace GLEEC::Graphics
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    std::vector<VkDescriptorBufferBindingInfoEXT>
        ShaderResourceManager::internalBindings = {};

    Internal::Graphics::vk::Sampler ShaderResourceManager::sampler = {};
#endif

    std::vector<ShaderResource> ShaderResourceManager::resources = {};

    inline void ShaderResourceManager::init()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        sampler = Internal::Graphics::vk::createSampler(
            GPUManager::activeGPU.device);
#endif
    }

    inline void ShaderResourceManager::destroy()
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::destroySampler(
            GPUManager::activeGPU.device, sampler);
#endif

        for (ShaderResource& resource : resources)
        {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            Internal::Graphics::vk::destroyDescriptorBuffer(
                GPUManager::activeGPU.allocator, resource.descriptorBuffer);
#endif
        }
    }

#if GLEEC_GRAPHICS_BACKEND
    inline Internal::Graphics::vk::DescriptorBuffer createDescriptorBuffer(
        VkDescriptorType type, VkDescriptorSetLayout layout)
    {
        return { Internal::Graphics::vk::createDescriptorBuffer(
            GPUManager::activeGPU.device.physicalDevice,
            GPUManager::activeGPU.device,
            GPUManager::activeGPU.allocator,
            type, 0,
            layout) };
    }

    inline VkDescriptorBufferBindingInfoEXT prepareDescriptorBufferBinding(
        const ShaderResource& resource)
    {
        VkDescriptorBufferBindingInfoEXT info = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_BUFFER_BINDING_INFO_EXT,
        };

        info.address = resource.descriptorBuffer.address;

        constexpr VkBufferUsageFlags exclude =
            ~VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

        info.usage = resource.descriptorBuffer.buffer.usage & exclude;

        return info;
    }

    inline ShaderResource ShaderResourceManager::addBinding(
        const ShaderResource& resource)
    {
        resources.push_back(resource);

        internalBindings.emplace_back(prepareDescriptorBufferBinding(resource));

        return resource;
    }
#endif

    inline ShaderResource ShaderResourceManager::createUniformBufferShaderResource(
        const Shaders& shaders, uint32_t set)
    {
        return addBinding({
            internalBindings.size(), shaders.shaderClass, set,
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            createDescriptorBuffer(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                shaders.layouts[set])
#endif
        });
    }

    inline uint32_t ShaderResourceManager::addUniformBuffer(ShaderResource& resource,
        const Buffer& buffer)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        return resource.offsets[buffer.buffer] = Internal::Graphics::vk::
            getUniformBufferDescriptor(
                GPUManager::activeGPU.device.physicalDevice,
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.allocator,
                resource.descriptorBuffer, buffer.buffer);
#endif
    }

    inline ShaderResource ShaderResourceManager::createCombinedImageShaderResource(
        const Shaders& shaders, uint32_t set)
    {
        return addBinding({
            internalBindings.size(), shaders.shaderClass, set,
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
            createDescriptorBuffer(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                shaders.layouts[set])
#endif
        });
    }

    inline uint32_t ShaderResourceManager::addCombinedImage(ShaderResource& resource,
        const Texture& texture)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        return resource.offsets[texture.image] = Internal::Graphics::vk::
            getCombinedImageSamplerDescriptor(
                GPUManager::activeGPU.device.physicalDevice,
                GPUManager::activeGPU.device,
                GPUManager::activeGPU.allocator,
                resource.descriptorBuffer, sampler, texture.imageView);
#endif
    }

    inline void ShaderResourceManager::use(const FrameData& frame,
        const ShaderResource& resource, uint32_t offset)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::cmdSetGraphicsPipelineDescriptorBufferOffsets(
            frame.commandBuffer,
            ShaderManager::getShaders(resource.shaderClass).pipelineLayout,
            resource.set, 1, resource.index, offset);
#endif
    }

    inline void ShaderResourceManager::use(const FrameData& frame,
        const ShaderResource& resource, const void* data)
    {
        use(frame, resource, resource.offsets.at(data));
    }

    inline void ShaderResourceManager::use(const FrameData& frame,
        const ShaderResource& resource, const Buffer& buffer)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        use(frame, resource, buffer.buffer);
#endif
    }

    inline void ShaderResourceManager::use(const FrameData& frame,
        const ShaderResource& resource, const Texture& texture)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        use(frame, resource, texture.image);
#endif
    }

    inline void ShaderResourceManager::bind(const FrameData& frame)
    {
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
        Internal::Graphics::vk::cmdBindDescriptorBuffers(frame.commandBuffer,
            internalBindings);
#endif
    }
}
