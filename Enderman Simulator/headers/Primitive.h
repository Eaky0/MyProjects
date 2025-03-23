#pragma once


#include <glad/glad.h> 


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <ShaderProgram.h>
#include <Texture.h>
#include <string>
#include <vector>
#include <VertexBuffer.h>


struct PrimitiveVertex {
	glm::vec3 posCoordinates;
	glm::vec3 normCoordinates;
	glm::vec2 texCoordinates;
};



class Primitive {
public:
	Primitive(const std::vector<PrimitiveVertex> V, const std::vector<unsigned int> I, const std::vector<Texture> T);
	void initBuffers();
	void DrawPrimitive(ShaderProgram * program);


	ShaderProgram objShader;


	std::vector<PrimitiveVertex> * getVertices();
	std::vector<unsigned int> * getIndices();
	std::vector<Texture> * getTextures();

	unsigned int * getVAO();
	unsigned int * getVBO();
	unsigned int * getEBO();
private:
	unsigned int VAO, VBO, EBO;
	std::vector<PrimitiveVertex> m_V;
	std::vector<unsigned int> m_I;
	std::vector<Texture> m_T;

};