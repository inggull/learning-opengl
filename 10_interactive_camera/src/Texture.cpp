#include "Texture.h"

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
    spdlog::info("Destroy texture({})", m_texture);
}

std::unique_ptr<Texture> Texture::Create(std::shared_ptr<Image> image) {
    auto texture = std::unique_ptr<Texture>(new Texture);
    texture->Init(image);
    return texture;
}

void Texture::Init(std::shared_ptr<Image> image) {
    glGenTextures(1, &m_texture);
    spdlog::info("Create texture({})", m_texture);
    // bind and set default filter and wrap option
    glBindTexture(GL_TEXTURE_2D, m_texture);
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    SetTexture(image);
}

GLuint Texture::Get() {
    return m_texture;
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void SetFilter(GLenum minFilter, GLenum magFilter) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void SetWrap(GLenum wrapS, GLenum wrapT) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

void SetTexture(std::shared_ptr<Image> image) {
    GLenum format;

    switch (image->GetChannelCount()) {
    case 1:
        format = GL_RED;
        break;

    case 2:
        format = GL_RG;
        break;

    case 3:
        format = GL_RGB;
        break;

    default:
        format = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, format, GL_UNSIGNED_BYTE, image->GetData());
    glGenerateMipmap(GL_TEXTURE_2D);
}