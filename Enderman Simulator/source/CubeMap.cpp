#include <CubeMap.h>

CubeMap::CubeMap() {
	glGenTextures(1, &id);
	loadBuffers();

	bindTexture();
	setupWrapping_and_filtering();
	loadFaces();

	unbindBuffer();
}


void CubeMap::bindBuffer() {
	glBindVertexArray(VAO);
}

void CubeMap::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void CubeMap::unbindBuffer() {
	glBindVertexArray(0);
}

void CubeMap::unbindTexture() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::loadBuffers() {
	glGenVertexArrays(1, &VAO);
	bindBuffer();
	
	VBO = VertexBuffer(sizeof(vertices), &vertices);
	EBO = IndexBuffer(sizeof(indices), &indices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//vertices coords
	glEnableVertexAttribArray(0);

	VBO.unbind();
	unbindBuffer();
	EBO.unbind();
}

void CubeMap::loadFaces() {
	const unsigned int FACES = 6;
	const std::string faces[6] = {
		"right.jpg",  "left.jpg",
		"top.jpg",    "bottom.jpg",
		"front.jpg",  "back.jpg",
	};
	const unsigned int CUBE_MAP_DIRECTION[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,  //right
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,  //left
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,  //top
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,  //bottem
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,  //front
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,  //back
	};

	for (int i = 0; i < FACES; i++) {
		loadFace(faces[i].c_str(), CUBE_MAP_DIRECTION[i]);
	}
}

void CubeMap::loadFace(const char* file, const unsigned int& type) {
	int width, height, bytePerPixel;
	unsigned char* data;

	loadData(file, data, &width, &height, &bytePerPixel);
	GLenum TYPE = getDataType(bytePerPixel);

	stbi_set_flip_vertically_on_load(false);
	glTexImage2D(type, 0, TYPE, width, height, 0, TYPE, GL_UNSIGNED_BYTE, data);
	
	stbi_image_free(data);
}

void CubeMap::loadData(const char* file, unsigned char*& data, int* width, int* height, int* bytePerPixel) {
	data = stbi_load(file, width, height, bytePerPixel, 0);
	if (data == NULL) throw new TextureLoadDataError();
}

GLenum CubeMap::getDataType(const int& bytePerPixel) {

	GLenum format = GL_RGB;
	if (bytePerPixel == 3) format = GL_RGB;
	else if (bytePerPixel == 4) format = GL_RGBA;

	return format;
}

void CubeMap::setupWrapping_and_filtering() {
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::draw() {
	bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	unbind();
}

void CubeMap::bind() {
	bindBuffer();
	bindTexture();
}

void CubeMap::unbind() {
	unbindBuffer();
	unbindTexture();
}