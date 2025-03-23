#include "CoolCube.h"

CoolCube::CoolCube() : VAO(0), EBO(0), ObjectShader(ShaderProgram("ObjectVertexShader.txt", "ObjectFragmentShader.txt")) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(100.0f, -50.0f, 0.0f));
	model = glm::scale(model, glm::vec3(50.0f));
}

void CoolCube::loadBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO = VertexBuffer(sizeof(vertices), vertices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);	//vertices coords
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	//texture coords
	glEnableVertexAttribArray(1);
}

void CoolCube::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}