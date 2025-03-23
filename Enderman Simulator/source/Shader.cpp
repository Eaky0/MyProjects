#include <Shader.h>
#include <sstream>

Shader::Shader(const std::string& path, const GLenum& type, const GLuint& program) : m_ID(0) {
	m_ID = glCreateShader(type);
	setupShader(path);

	glAttachShader(program, m_ID);
}

void Shader::setupShader(const std::string & path) {
	std::string shaderContents;

	try
	{
		parseShader(path, shaderContents);
		compile(shaderContents);
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	} 
	catch (ShaderCompileError e) {
		std::cout << e.what() << std::endl;
	}
}

void Shader::parseShader(const std::string& path, std::string& shaderContents) {
    std::ifstream shaderfile(path);
    if (!shaderfile.is_open()) {
        throw std::ifstream::failure("ERROR::SHADER::FILE_NOT_OPEN");
    }

    std::stringstream shaderStream;
    shaderStream << shaderfile.rdbuf();
    shaderfile.close();

    shaderContents = shaderStream.str();
}

void Shader::compile(const std::string &content) {
	//convert string to char
	const char* cnt = content.c_str();

	glShaderSource(m_ID, 1, &cnt, NULL);
	glCompileShader(m_ID);

	errorCheck();
}

void Shader::errorCheck() {
	int succes;
	char infoLog[512];
	glGetShaderiv(m_ID, GL_COMPILE_STATUS, &succes);

	if (!succes) {
		glGetShaderInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		throw new ShaderCompileError(infoLog);
	}
}