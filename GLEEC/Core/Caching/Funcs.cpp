#include "Funcs.h"

namespace GLEEC::Caching
{
#if GLEEC_GRAPHICS_BACKEND == GRAPHICS_BACKEND_VK
    inline Internal::Graphics::vk::ShaderBinary loadCachedShader(
        std::ifstream& file, const CachedHeader& header)
    {
        Internal::Graphics::vk::ShaderBinary shader = {};

        shader.codeType = VK_SHADER_CODE_TYPE_BINARY_EXT;

        shader.code.resize(header.size);

        file.read(shader.code.data(), header.size);

        return shader;
    }

    inline Internal::Graphics::vk::ShaderBinary loadLoadedShader(
        std::ifstream& file, std::string_view filepath)
    {
        return Internal::Graphics::vk::readSPIRV(filepath);
    }

    inline void writeShader(std::ofstream& file,
        const Internal::Graphics::vk::ShaderBinary& cache)
    {
        file.write(cache.code.data(), cache.code.size());
    }

    // instead of destroying the shader cache, destroy the shader later
    inline void destroyShader(
        const Internal::Graphics::vk::ShaderBinary& cache)
    {
        // ...
    }

    inline Graphics::DescriptorSets loadCachedDescriptorSetBindings(
        std::ifstream& file, const CachedHeader& header)
    {
        Graphics::DescriptorSets layouts = {};

        size_t size = 0;
        while (size < header.size)
        {
            CachedHeader dslbheader = {};
            file.read(reinterpret_cast<char*>(&dslbheader), sizeof(CachedHeader));
            size += sizeof(CachedHeader);

            // allow space for the binding number
            Graphics::DescriptorSetBindings bindings = {};

            bindings = std::vector<Internal::Graphics::vk::
                DescriptorSetBinding>(dslbheader.size 
                / sizeof(Internal::Graphics::vk::DescriptorSetBinding));

            file.read(reinterpret_cast<char*>(bindings.data()), dslbheader.size);

            size += dslbheader.size;

            layouts.emplace_back(bindings);
        }

        return layouts;
    }

    inline Graphics::DescriptorSets loadLoadedDescriptorSetBindings(
        std::ifstream& file, std::string_view filepath)
    {
        // nothing happens because reflection will be used later
        return {};
    }

    inline void writeDescriptorSetBindings(std::ofstream& file,
        const Graphics::DescriptorSets& bindings)
    {
        for (const auto& binding : bindings)
        {
            CachedHeader header = {};
            header.size = binding.size() *
                sizeof(Internal::Graphics::vk::DescriptorSetBinding);

            file.write(reinterpret_cast<const char*>(&header), sizeof(CachedHeader));

            file.write(reinterpret_cast<const char*>(binding.data()),
                header.size);
        }
    }

    inline void destroyDescriptorSetBindings(const Graphics::DescriptorSets&)
    {
        /* for (const auto& layout : layouts)
        {
            Internal::Graphics::vk::destroyDescriptorSetLayout(
                Graphics::GPUManager::activeGPU.device, layout);
        } */
    }
#endif
}
