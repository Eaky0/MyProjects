#pragma once


#include <MeshMap.h>
#include <Shader.h>
#include <Window.h>
#include <Camera.h>

class Simulator {
private:
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;

	Window simWindow;
	Camera cam;
	MeshMap map;


	void processInput(GLFWwindow* window);

	void mouseMovement(GLFWwindow* window, double xpos, double ypos);

	void zoomProcess(GLFWwindow* window, double xoffset, double yoffset);


public:
	Simulator();
};