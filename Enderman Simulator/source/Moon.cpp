#include "Moon.h"

//Hoe groter y > 0, hoe meer het lichtbron naar beneden gaat
Moon::Moon() : VAO(0), lightShader(ShaderProgram("LightVertexShader.txt", "LightFragmentShader.txt")), worldPos(glm::vec3(-2000.0f, 1000.0f, -2500.0f)), color(glm::vec3(0.839215f, 0.862745f, 0.890196f)) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, worldPos);
	model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Moon::loadBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO = VertexBuffer(sizeof(vertices), vertices);
	EBO = IndexBuffer(sizeof(indices), indices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Moon::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//unbind all
	glBindVertexArray(0);
}