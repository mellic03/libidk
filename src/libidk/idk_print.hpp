#pragma once
#include <print>
#include "idk_glm.hpp"

template <>
struct std::formatter<glm::vec2> : std::formatter<std::string> {
    auto format(glm::vec2 v, format_context &ctx) const {
        return formatter<string>::format(
            std::format("[{}, {}]", v.x, v.y), ctx
        );
    }
};

template <>
struct std::formatter<glm::vec3> : std::formatter<std::string> {
    auto format(glm::vec3 v, format_context &ctx) const {
        return formatter<string>::format(
            std::format("[{}, {}, {}]", v.x, v.y, v.z), ctx
        );
    }
};

template <>
struct std::formatter<glm::vec4> : std::formatter<std::string> {
    auto format(glm::vec4 v, format_context &ctx) const {
        return formatter<string>::format(
            std::format("[{}, {}, {}, {}]", v.x, v.y, v.z, v.w), ctx
        );
    }
};


