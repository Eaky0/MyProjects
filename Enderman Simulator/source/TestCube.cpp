#include "TestCube.h"



TestCube::TestCube() : VAO(0), EBO(0), lightShader(ShaderProgram("ObjectVertexShader.txt", "ObjectFragmentShader.txt")) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, worldPos);
	//model = glm::scale(model, glm::vec3(10.0f));
}

void TestCube::loadBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO = VertexBuffer(sizeof(vertices), vertices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);	//vertices coords
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));	//texture coords
	glEnableVertexAttribArray(1);

	//unbind
	glBindVertexArray(0);
}

void TestCube::draw() {
	//bind
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//unbind
	glBindVertexArray(0);

}


bool TestCube::Interactable(glm::vec3 visual) {


	//Looking at it from its front?
	if (visual.x >= front[0].x && visual.y >= front[0].y && visual.z >= front[0].z &&
		visual.x <= front[1].x && visual.y >= front[1].y && visual.z >= front[1].z &&
		visual.x <= front[2].x && visual.y <= front[2].y && visual.z >= front[2].z &&
		visual.x >= front[3].x && visual.y <= front[3].y && visual.z >= front[3].z) {
		return true;
	}

	//Looking at it from its back?
	else if (visual.x >= back[0].x && visual.y >= back[0].y && visual.z <= back[0].z &&
		visual.x <= back[1].x && visual.y >= back[1].y && visual.z <= back[1].z &&
		visual.x <= back[2].x && visual.y <= back[2].y && visual.z <= back[2].z &&
		visual.x >= back[3].x && visual.y <= back[3].y && visual.z <= back[3].z) {
		return true;
	}

	//Looking at it from above?
	else if (visual.x >= up[0].x && visual.y <= up[0].y && visual.z >= up[0].z &&
		visual.x <= up[1].x && visual.y <= up[1].y && visual.z >= up[1].z &&
		visual.x <= up[2].x && visual.y <= up[2].y && visual.z <= up[2].z &&
		visual.x >= up[3].x && visual.y <= up[3].y && visual.z <= up[3].z) {
		return true;
	}

	//Looking at it from underneath?
	else if (visual.x >= bottom[0].x && visual.y >= bottom[0].y && visual.z >= bottom[0].z &&
		visual.x <= bottom[1].x && visual.y >= bottom[1].y && visual.z >= bottom[1].z &&
		visual.x <= bottom[2].x && visual.y >= bottom[2].y && visual.z <= bottom[2].z &&
		visual.x >= bottom[3].x && visual.y >= bottom[3].y && visual.z <= bottom[3].z) {
		return true;
	}

	//Looking at it from its left?
	else if (visual.x >= left[0].x && visual.y >= left[0].y && visual.z >= left[0].z &&
		visual.x >= left[1].x && visual.y >= left[1].y && visual.z <= left[1].z &&
		visual.x >= left[2].x && visual.y <= left[2].y && visual.z <= left[2].z &&
		visual.x >= left[3].x && visual.y <= left[3].y && visual.z >= left[3].z) {
		return true;
	}

	//Looking it from its right?
	else if (visual.x <= right[0].x && visual.y >= right[0].y && visual.z >= right[0].z &&
		visual.x <= right[1].x && visual.y >= right[1].y && visual.z <= right[1].z &&
		visual.x <= right[2].x && visual.y <= right[2].y && visual.z <= right[2].z &&
		visual.x <= right[3].x && visual.y <= right[3].y && visual.z >= right[3].z) {
		return true;
	}
	else {
		return false;
	}

}




void TestCube::AdjustPosition(glm::vec3 visual, glm::vec3 Direction) {
	worldPos = visual + Direction + glm::vec3(0.0, -0.5, 0.0);

	model = glm::mat4(1.0);
	model = glm::translate(model, worldPos);

	//std::cout << "w_x = " << (worldPos.x) << ",  w_y = " << (worldPos.y) << ", w_z = " << (worldPos.z) << std::endl;

	//std::cout << "x = " << (visual.x) << ",  y = " << (visual.y) << ", z = " << (visual.z) << std::endl;



	// Calculate edges for each side
	CalcEdges(front);
	CalcEdges(back);
	CalcEdges(up);
	CalcEdges(bottom);
	CalcEdges(left);
	CalcEdges(right);
}

void TestCube::CalcEdges(glm::vec3(&side)[4]) {

	side[0] = worldPos + glm::vec3(-0.5f, -0.5f, -0.5f);
	side[1] = worldPos + glm::vec3(0.5f, -0.5f, -0.5f);
	side[2] = worldPos + glm::vec3(0.5f, 0.5f, -0.5f);
	side[3] = worldPos + glm::vec3(-0.5f, 0.5f, -0.5f);

}