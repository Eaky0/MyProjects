#pragma once
#include <glad/glad.h>

class IndexBuffer {
private:
	unsigned int m_bufferID;
	unsigned int count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int count, const void* data);

	void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID); }
	void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	void deleteBuffer();
	
};