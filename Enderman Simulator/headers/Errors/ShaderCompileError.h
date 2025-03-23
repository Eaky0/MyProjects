/*
* author : Ieracitano Alessio
*/

#pragma once
#include <exception>
#include <string>

class ShaderCompileError : public std::exception {
private: 
	std::string message;
public:
	ShaderCompileError(const char* msg) { message = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + (std::string) msg; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); }
};