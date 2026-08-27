#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "common.h"
#include "Image.h"

class Texture {
public:
    ~Texture();
    static std::unique_ptr<Texture> Create(std::shared_ptr<Image> image);
    GLuint Get();
    void Bind();

private:
    GLuint m_texture;
    Texture() = default;
    void Init(std::shared_ptr<Image> image);
};

void SetFilter(GLenum minFilter, GLenum magFilter);
void SetWrap(GLenum wrapS, GLenum wrapT);
void SetTexture(std::shared_ptr<Image> image);

#endif // __TEXTURE_H__