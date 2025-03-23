/*
* author : Ieracitano Alessio
*/

#pragma once
#include <exception>
#include <string>

class MeshLoadingError : public std::exception {
private:
	std::string message;
public:
	MeshLoadingError() { message = "ERROR::MESHMAP::DATA::LOADING_FAILED\n"; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); }
};