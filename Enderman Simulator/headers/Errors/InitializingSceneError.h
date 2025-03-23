#include <string>
#include <exception>


class InitializingSceneError : public std::exception {

public:
	InitializingSceneError() { message = "ERROR::ASSIMP::COULD NOT READ THE OBJECT FILE\n"; }

	/* @override
	 * We return the error message
	*/
	const char* what() const throw() { return message.c_str(); };

private:
	std::string message;

};