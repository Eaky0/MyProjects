/*
* Author : Ieracitano Alessio
*/

#pragma once
//----------------------------------//
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Errors/WindowCreateError.h>
#include <Errors/GLADinitializeError.h>
//----------------------------------//

class Window {
private:
//------------Member---------------//
	GLFWwindow* m_window;
	const int SCR_WIDTH;
	const int SCR_HEIGHT;
	const char *titel;
//------------Functions-----------//

	/*
	* Create the window instance
	* @pre glfw has been initialized
	*/
	void createWindow() {
		m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, titel, NULL, NULL);

		if (m_window == NULL) {
			glfwTerminate();
			throw new WindowCreateError();
		}
	}

	/*
	* We inizialize GLAD
	* @throws GLADinitializeError
	*/
	void initGlAD() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw new GLADinitializeError();
	}

public:


	/*
	* Creates an window instance
	* @throws WindowCreateError incase the winodw couldn't be build
	*/
	Window(const int SRC_WIDTH, const int SRC_HEIGHT, const char *windowTitel) : SCR_WIDTH(SRC_WIDTH), SCR_HEIGHT(SRC_HEIGHT), titel(windowTitel) {
		if (!glfwInit()) 
			throw new std::runtime_error("glfw cannot be initialized");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		//Create the window instance
		createWindow();
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Make the context of the window the main context of the current thread
		glfwMakeContextCurrent(m_window);
		initGlAD();

		// Set the callback for resizing the window
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow * window, int width, int height) { 
													glViewport(0, 0, width, height); }
		);
	}

	/*
	* Returns the glfw window
	*/
	GLFWwindow* getGLFWWindow() const {
		return m_window;
	}

	/*
	* Checks if the winodw is closed
	* @return true incase the window is closed
	*/
	bool closed() { return glfwWindowShouldClose(m_window); }



};