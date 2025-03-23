#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <Errors/TextureLoadDataError.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <string>

class CubeMap {
private:
	GLuint id;
	float vertices[24] = {
        -1.0f, -1.0f,  1.0f,    //front bottem left //0           2- - - - - - 7
        -1.0f, -1.0f, -1.0f,    //back bottem left  //1          /|           /|
        -1.0f,  1.0f, -1.0f,    //back top left     //2         3- - - - - - 6 |
        -1.0f,  1.0f,  1.0f,    //front top left    //3         | |          | |
         1.0f, -1.0f, -1.0f,    //back bottem right  //4        | 1- - - - - |-4
         1.0f, -1.0f,  1.0f,    //front bottem right //5        |/           |/ 
         1.0f,  1.0f,  1.0f,    //front top right    //6        0- - - - - - 5
         1.0f,  1.0f, -1.0f,    //back top right     //7
	};
	int indices[36] = {
        //right
        4, 5, 6,
        6, 7, 4,
        //left side
        0, 1, 2,
        2, 3, 0,
        //top
        2, 7, 6,
        6, 3, 2,
        //bottem
        1, 0, 4,
        4, 0, 5,
        //front
        0, 3, 6,
        6, 5, 0,
        //back
        2, 1, 4, 
        4, 7, 2,
	};

	VertexBuffer VBO;
    IndexBuffer EBO;
    unsigned int VAO;

    //functions
	void loadFaces();

	void loadFace(const char* file, const unsigned int& type);

	void loadData(const char* file, unsigned char*& data, int *width, int *height, int *bytePerPixel);

    void bindBuffer();
    void bindTexture();

    void unbindBuffer();
    void unbindTexture();

	GLenum getDataType(const int& bytePerPixel);

public:
	CubeMap();

    void loadBuffers();

	void setupWrapping_and_filtering();

    void bind();

    void unbind();

    void draw();

    unsigned int getVAO() { return VAO;  }
};