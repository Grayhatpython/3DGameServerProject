#pragma once

#include <string>
#include <memory>
#include <functional>

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <optional>

inline std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        SPDLOG_ERROR("Failed to open file: {}", filename);
        return {};
    }
    std::stringstream text;

    text << fin.rdbuf();
    return text.str();
}
