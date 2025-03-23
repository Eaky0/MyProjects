/*
* author : Ieracitano Alessio
*/

#pragma once
#include <exception>
#include <string>

class WindowCreateError : public std::exception {
private:
	std::string message;
public:
	WindowCreateError() { message = "ERROR::WINDOW::CREATE::CREATING_FAILED\n"; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); }
};