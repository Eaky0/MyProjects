#include <IndexBuffer.h>

IndexBuffer::IndexBuffer() : m_bufferID(0) {}

IndexBuffer::IndexBuffer(unsigned int count, const void* data) {
	glGenBuffers(1, &m_bufferID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

void IndexBuffer::deleteBuffer() {
	glDeleteBuffers(1, &m_bufferID);
}