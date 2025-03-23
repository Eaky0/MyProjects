#pragma once
#include <glad/glad.h>
#include <type_traits>

class VertexBuffer {
private:
	unsigned int m_bufferID;

	//template<class T>
	//void initBuffer(T size, const void* data);
public:
	VertexBuffer();

	VertexBuffer(unsigned long long size, const void* data);

	void deleteBuffer();

	void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); }
	void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};