#ifndef __COMMON_H__
#define __COMMON_H__

#include <fstream>
#include <optional>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

std::optional<std::string> LoadFile(const std::string& filePath);

#endif // __COMMON_H__