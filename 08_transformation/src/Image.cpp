#include "Image.h"

Image::~Image() {
    stbi_image_free(m_data);
    spdlog::info("Destroy image");
}

std::unique_ptr<Image> Image::LoadFromFile(const std::string& filePath) {
    auto image = std::unique_ptr<Image>(new Image);
    if (!image->Init(filePath)) {
        return nullptr;
    }
    return image;
}

bool Image::Init(const std::string& filePath) {
    // 이미지 파일과 OpenGL은 이미지의 시작점이 상하 대칭 관계에 있기 때문에 불러온 이미지 파일을 상하 반전시켜야 한다
    stbi_set_flip_vertically_on_load(true);

    m_data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channelCount, 0);
    if (!m_data) {
        spdlog::error("Failed to load image \"{}\"", filePath);
        return false;
    }

    return true;
}

int32_t Image::GetWidth() const {
    return m_width;
}

int32_t Image::GetHeight() const {
    return m_height;
}

int32_t Image::GetChannelCount() const {
    return m_channelCount;
}

const uint8_t* Image::GetData() const {
    return m_data;
}