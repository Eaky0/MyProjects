#pragma once
#include <Shader.h>

class ShaderProgram {
private:
	unsigned int programId;
public:

	/*
	* Create an ShaderProgram
	*/
	ShaderProgram() {
		programId = glCreateProgram();
	}

	/*
	* Create an program and its shaders
	*/
	ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile) {
		programId = glCreateProgram();

		Shader vertexShader = Shader(vertexFile, GL_VERTEX_SHADER, programId);
		Shader fragmentShader = Shader(fragmentFile, GL_FRAGMENT_SHADER, programId);

		linkAttachedShaders();

		vertexShader.deleteShader();
		fragmentShader.deleteShader();
	}

	/*
	* Inisiale the program and links its shaders
	*/
	ShaderProgram(Shader vertex, Shader fragment) {
		programId = glCreateProgram();

		//glAttachShader(programId, vertexShader.getShader());
		//glAttachShader(programId, fragmentShader.getShader());
		glLinkProgram(programId);

		vertex.deleteShader();
		fragment.deleteShader();
	}

	void setupShaders(Shader vertex, Shader fragment) {
		glLinkProgram(programId);

		vertex.deleteShader();
		fragment.deleteShader();
	}

	/*
	* Get's the program id
	* @returns the id
	*/
	unsigned int getID() { return programId; }

	/*
	* We link the attached shaders to the program
	*/
	void linkAttachedShaders() { glLinkProgram(programId); }

	/*
	* Set's the program to be the one to be used
	*/
	void use() { glUseProgram(programId); }

	/*
	* Set a uniform vector
	* @param vec a vector of size 3
	* @param var is the variable name
	*/
	void setUniform3f(const char* var, const glm::vec3& vec) {
		unsigned int location = glGetUniformLocation(programId, var);
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void setUniform3f(const char* var, const float x, const float y, const float z) {
		unsigned int location = glGetUniformLocation(programId, var);
		glUniform3f(location, x, y, z);
	}

	void setFloat(const char* var, const float &x) {
		unsigned int location = glGetUniformLocation(programId, var);
		glUniform1f(location, x);
	}

	void setInt(const char* var, const int& x) {
		unsigned int location = glGetUniformLocation(programId, var);
		glUniform1i(location, x);
	}

	/*
	* Set a uniform matrix in the shader
	* @param matrix a vector of size 4 x 4 
	* @param var is the variable name
	*/
	void setUniformMatrix4fv(const char* var, const glm::mat4 &matrix) {
		unsigned int location = glGetUniformLocation(programId, var);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
};
