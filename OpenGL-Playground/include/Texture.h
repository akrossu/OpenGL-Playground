#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string& path, bool flipVertically);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	unsigned int getTextureID() const { return textureID; }

private:
	unsigned int textureID;
	int width, height, channels;
};