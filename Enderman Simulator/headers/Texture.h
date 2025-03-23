#pragma once
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Errors/TextureLoadDataError.h>


enum Texturetype
{
	DIFFUSE, SPECULAR, NORMAL
};



class Texture {
private:
	GLuint textureID;	//or unsigned int
	int width, height, nrChannels;
	Texturetype TexType;
	std::string TexResourcePath;

	/*
	* We set the texture settings
	* @pre a texture has been binded
	*/
	void setupTextureSettings();

	/*
	* Loads the data from an file
	* @param file the file name
	* @param data location where we wish to keep the open data
	*/
	void loadData(const char* file, unsigned char*& data);




public:

	/*
	* Creates an empty instance
	*/
	Texture() : textureID(0), width(0), height(0), nrChannels(0) {}

	/*
	* Creates & loads an Texture
	* @param file the file we wish to read in as an texture
	*/
	Texture(const char* file);

	/*
	* We cleanup the texture
	*/
	~Texture();

	/*
	* Binds the texture
	*/
	void bind() const;

	/*
	* unbinds the texture
	*/
	void unbind() const;


	void setPath(const char* file) { TexResourcePath = file; };
	std::string getPath() { return TexResourcePath; };

	GLuint getID() const { return textureID; };

	void setID(GLuint id) { textureID = id; };

	void setType(Texturetype T) {TexType = T;};
	Texturetype getType() { return TexType; };


};