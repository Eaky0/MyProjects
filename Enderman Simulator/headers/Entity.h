#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

class Entity {
private:
	glm::mat4 model;
	glm::mat4 scale;
	glm::vec3 coords;

public:
	virtual void setModel(glm::mat4 model);
	virtual void setScale(glm::mat4 coords);
	virtual void setCoordinates(glm::vec3 coords);

	glm::mat4 getModel();
	virtual void foo() = 0;
};