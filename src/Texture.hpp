#ifndef TEXTURE_HPP
#define TEXTURE_HPP


#include <cstdint>
#include <string>
#include <GL/glew.h>


class Texture {
public:
    Texture(uint32_t width, uint32_t height, GLenum format = GL_RGBA,
            GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE, void* data = nullptr,
            GLenum dataFormat = GL_RGBA, GLenum dataType = GL_UNSIGNED_BYTE);
    ~Texture(void);

    Texture(Texture&&);
    Texture& operator=(Texture&&);
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;

    operator GLuint() const;

    void setSize(uint32_t width, uint32_t height);

    unsigned width(void) const;
    unsigned height(void) const;

    void loadFromFile(const std::string& fileName);
    void update(void* data, GLenum srcFormat, GLenum destFormat = GL_RGBA);

private:
    GLuint		_textureId;
    uint32_t	_width;
    uint32_t	_height;
};


#endif // TEXTURE_HPP
