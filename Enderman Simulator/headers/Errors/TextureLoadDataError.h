/*
* author : Ieracitano Alessio
*/

#pragma once
#include <exception>
#include <string>

class TextureLoadDataError : public std::exception {
private:
	std::string message;
public:
	TextureLoadDataError() { message = "ERROR::TEXTURE::LOAD::DATA_LOADING_FAILED\n"; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); }
};