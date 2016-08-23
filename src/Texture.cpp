#include "Texture.hpp"

#include <SFML/Graphics.hpp>


Texture::Texture(uint32_t width, uint32_t height,
                 GLenum format, GLenum wrapS, GLenum wrapT,
                 void* data, GLenum dataFormat, GLenum dataType) :
	_textureId(0), _width(width), _height(height)
{
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, dataFormat, dataType, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(void) {
	if (_textureId)
		glDeleteTextures(1, &_textureId);
}

Texture::Texture(Texture&& other) {
	_textureId = other._textureId;
	other._textureId = 0;

	_width = other._width;
	_height = other._height;
}

Texture& Texture::operator=(Texture&& other) {
	if (_textureId)
		glDeleteTextures(1, &_textureId);

	_textureId = other._textureId;
	other._textureId = 0;

	_width = other._width;
	_height = other._height;

	return *this;
}

Texture::operator GLuint() const {
	return _textureId;
}

void Texture::setSize(uint32_t width, uint32_t height) {
	_width = width;
	_height = height;
}

unsigned Texture::width(void) const {
	return _width;
}

unsigned Texture::height(void) const {
	return _height;
}

void Texture::loadFromFile(const std::string& fileName) {
	sf::Image img;
	img.loadFromFile(fileName);
	auto is = img.getSize();
	printf("%u, %u\n", is.x, is.y);
	//if (is.x != _width || is.y != _height)
		//return;

	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, is.x, is.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
}

void Texture::update(void* data, GLenum srcFormat, GLenum destFormat) {
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, destFormat, _width, _height, 0,
		srcFormat, GL_UNSIGNED_BYTE, data);
}
