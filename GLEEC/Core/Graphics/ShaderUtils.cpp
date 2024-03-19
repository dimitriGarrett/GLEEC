#include "ShaderUtils.h"

namespace GLEEC::Graphics
{
    inline std::string ShaderUtils::shaderClass(std::string_view filepath)
    {
        std::string temp(filepath);

#if GLEEC_WINDOWS
        for (char& c : temp)
        {
            if (c == '\\') c = '/';
        }
#endif

        return temp.substr(temp.find_last_of('/') + 1, 2);
    }

    inline size_t ShaderUtils::shaderClassIndex(std::string_view filepath)
    {
        return std::hash<std::string>{}(shaderClass(filepath));
    }

    inline std::string ShaderUtils::dslbFilepath(std::string_view shaderClass)
    {
        return "shader-dslb-" + std::string(shaderClass);
    }
}
