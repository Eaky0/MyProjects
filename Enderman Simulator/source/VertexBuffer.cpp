#include <VertexBuffer.h>

VertexBuffer::VertexBuffer() : m_bufferID(0) {}


VertexBuffer::VertexBuffer(unsigned long long size, const void* data) {
	glGenBuffers(1, &m_bufferID);
	bind();

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::deleteBuffer() {
	glDeleteBuffers(1, &m_bufferID);
}