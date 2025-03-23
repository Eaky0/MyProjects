/*
* author : Ieracitano Alessio
*/

#pragma once
#include <exception>
#include <string>

class GLADinitializeError : public std::exception {
private:
	std::string message;
public:
	GLADinitializeError() { message = "ERROR::GLAD::INIT::INITIALIZED_FAILED\n"; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); }
};