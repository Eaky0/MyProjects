#include "Lamp.h"

//Hoe groter y > 0, hoe meer het lichtbron naar beneden gaat
Lamp::Lamp() : VAO(0), lightShader(ShaderProgram("LightVertexShader.txt", "LightFragmentShader.txt")), worldPos(glm::vec3(1.5f, -58.0f, -3.0f)), color(glm::vec3(1.0f, 0.81960784313f, 0.278431372549019f)) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, worldPos);
	model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
}

void Lamp::loadBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO = VertexBuffer(sizeof(vertices), vertices);
	EBO = IndexBuffer(sizeof(indices), indices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Lamp::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//unbind all
	glBindVertexArray(0);
}