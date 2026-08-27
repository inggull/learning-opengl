#ifndef __COMMON_H__
#define __COMMON_H__

#include <fstream>
#include <optional>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_NAME "Transformation"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

std::optional<std::string> LoadFile(const std::string& filePath);

#endif // __COMMON_H__