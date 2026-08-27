#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stb_image.h>
#include "common.h"

class Image {
public:
    ~Image();
    static std::unique_ptr<Image> LoadFromFile(const std::string& filePath);
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    int32_t GetChannelCount() const;
    const uint8_t* GetData() const;

private:
    int32_t m_width;
    int32_t m_height;
    int32_t m_channelCount;
    uint8_t* m_data;
    Image() = default;
    bool Init(const std::string& filePath);
};

#endif // __IMAGE_H__