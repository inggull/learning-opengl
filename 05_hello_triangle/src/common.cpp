#include "common.h"

std::optional<std::string> LoadFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        spdlog::error("Failed to open file \"{}\"", filePath);
        return {};
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string content;
    content.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&content[0], size);

    return content;
}