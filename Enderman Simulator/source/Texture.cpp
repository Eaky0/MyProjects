#include <Texture.h>

void Texture::setupTextureSettings() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_EQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_EQUAL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_EQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_EQUAL);
}

void Texture::loadData(const char* file, unsigned char*& data) {
	data = stbi_load(TexResourcePath.c_str(), &width, &height, &nrChannels, 0);
	if (data == NULL) throw new TextureLoadDataError();
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const char* file) {

	TexResourcePath = std::string(file);

	unsigned char* data;
	loadData(file, data);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = GL_RGB;
	if (nrChannels == 3) format = GL_RGB;
	else if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
		GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}
