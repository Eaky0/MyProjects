/*
* Author : Ieracitano Alessio
*/

#pragma once
/*------------- INCLUDES -------------*/
#include <string>
#include <iostream>
#include <fstream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <Errors/ShaderCompileError.h>
/*------------- INCLUDES -------------*/


/*
* This shader is a helper class to initialize shaders
*/
class Shader{
private: 
	GLuint m_ID;

	/*
	* We setup shader using an file
	* @param path Is the path that points to the given file
	* @param type IS the type of shader we are tyring to read
	*/
	void setupShader(const std::string& path);

	/*
	* Compiles the shader
	*/
	void compile(const std::string& content);

	/*
	* Checks if an error occurs during compiling
	* @pre compile function has been called
	*/
	void errorCheck();

	/*
	* We parse the shaderfile.
	*/
	void parseShader(const std::string& path, std::string& shaderContents);

public:
	Shader(const std::string& path, const GLenum& type, const GLuint &program);

	/*
	* Deletes the shader
	*/
	void deleteShader() { glDeleteShader(m_ID); }

	/*
	* Return the shader id
	*/
	int getShader() const {
		return m_ID;
	}
};