#pragma once
#include <Entity.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Moon {
private:
    glm::vec3 worldPos;
    glm::vec3 color;
    glm::mat4 model;

    VertexBuffer VBO;
    IndexBuffer EBO;
    unsigned int VAO;

    ShaderProgram lightShader;

    float vertices[24] = {
        -0.5f, -0.5f,  0.5f,    //front bottem left //0           2- - - - - - 7
        -0.5f, -0.5f, -0.5f,    //back bottem left  //1          /|           /|
        -0.5f,  0.5f, -0.5f,    //back top left     //2         3- - - - - - 6 |
        -0.5f,  0.5f,  0.5f,    //front top left    //3         | |          | |
         0.5f, -0.5f, -0.5f,    //back bottem right  //4        | 1- - - - - |-4
         0.5f, -0.5f,  0.5f,    //front bottem right //5        |/           |/ 
         0.5f,  0.5f,  0.5f,    //front top right    //6        0- - - - - - 5
         0.5f,  0.5f, -0.5f,    //back top right     //7
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

public:

    /*
    * Creates an moon object
    */
    Moon();

    /*
    * Loads the buffers
    */
    void loadBuffers();

    /*
    * Draw the object
    */
    void draw();

    /*
    * Return the model matrix
    */
    glm::mat4 getModel() { return model; }

    ShaderProgram getShaderProgram() { return lightShader; }

    unsigned int getVAO() { return VAO; }

    glm::vec3 getWorldPos() { return worldPos; }

    glm::vec3 getColor() { return color; }
};