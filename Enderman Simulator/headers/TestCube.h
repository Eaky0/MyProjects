#pragma once
#include <Entity.h>
#include <VertexBuffer.h>
#include <ShaderProgram.h>




class TestCube {
private:
    VertexBuffer VBO;
    glm::mat4 model;

    bool held = false;

    ShaderProgram lightShader;
    unsigned int VAO, EBO;

    glm::vec3 worldPos = glm::vec3(0.0f, -67.0f, -10.0f);
    glm::vec3 * centroid = &worldPos;

    glm::vec3 front[4] = {
    *centroid + glm::vec3(-0.5f, -0.5f, -0.5f), // linksonder
    *centroid + glm::vec3(0.5f, -0.5f, -0.5f),  // rechtsonder
    *centroid + glm::vec3(0.5f, 0.5f, -0.5f),   // rechtsboven
    *centroid + glm::vec3(-0.5f, 0.5f, -0.5f)   // linksboven
    };

    glm::vec3 back[4] = {
    *centroid + glm::vec3(-0.5f, -0.5f, 0.5f), // linksonder
    *centroid + glm::vec3(0.5f, -0.5f, 0.5f),  // rechtsonder
    *centroid + glm::vec3(0.5f, 0.5f, 0.5f),   // rechtsboven
    *centroid + glm::vec3(-0.5f, 0.5f, 0.5f)   // linksboven
    };

    glm::vec3 up[4] = {
    *centroid + glm::vec3(-0.5f, 0.5f, -0.5f), // linksachter
    *centroid + glm::vec3(0.5f, 0.5f, -0.5f),  // rechtsachter
    *centroid + glm::vec3(0.5f, 0.5f, 0.5f),   // rechtsvoor
    *centroid + glm::vec3(-0.5f, 0.5f, 0.5f)   // linksvoor
    };

    glm::vec3 bottom[4] = {
    *centroid + glm::vec3(-0.5f, -0.5f, -0.5f), // linksonder
    *centroid + glm::vec3(0.5f, -0.5f, -0.5f),  // rechtsonder
    *centroid + glm::vec3(0.5f, -0.5f, 0.5f),   // rechtsboven
    *centroid + glm::vec3(-0.5f, -0.5f, 0.5f)   // linksboven
    };

    glm::vec3 left[4] = {
    *centroid + glm::vec3(-0.5f, -0.5f, -0.5f), // linksonderachter
    *centroid + glm::vec3(-0.5f, -0.5f, 0.5f),  // linksondervoor
    *centroid + glm::vec3(-0.5f, 0.5f, 0.5f),   // linksbovenvoor
    *centroid + glm::vec3(-0.5f, 0.5f, -0.5f)   // linksbovenachter
    };

    glm::vec3 right[4] = {
    *centroid + glm::vec3(0.5f, -0.5f, -0.5f), // rechtsonderachter
    *centroid + glm::vec3(0.5f, -0.5f, 0.5f),  // rechtsondervoor
    *centroid + glm::vec3(0.5f, 0.5f, 0.5f),   // rechtsbovenvoor
    *centroid + glm::vec3(0.5f, 0.5f, -0.5f)   // rechtsbovenachter
    };


    float vertices[180] = {
        // positions         // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  //left  bottem   back
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  //right bottem   back
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  //right top      back
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  //right top      back
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  //left  top      back
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  //left  bottem   behnd
                               
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, //left   bottem    front
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f, //right  bottem    front
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f, //right  top       front
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f, //right  top       front
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f, //left   top       front
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, //left   bottem    front
                              
        -0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //left   top       front
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f, //left   top       back
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //left   bottem    back
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //left   bottem    back
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, //left   top       front
        -0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //left   top       front
                              
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //right  top      front
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f, //right  top      back
         0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //right  bottem   back
         0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //right  bottem   back
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, //right  bottem   front
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //right  top      front
                              
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //left   bottem   back
         0.5f, -0.5f, -0.5f,  1.0f,  1.0f, //right  bottem   back
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f, //right  bottem   front
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f, //right  bottem   front
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, //left   bottem   front
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, //left   bottem   back
                              
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, //left   top      back
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f, //right  top      back
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //right  top      front
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f, //right  top      front
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, //left   top      front
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f  //left   top      back
    };


    void CalcEdges(glm::vec3 (&side)[4]);

public:

    /*
    * Creates an moon object
    */
    TestCube();

    /*
    * Loads the buffers
    */
    void loadBuffers();

    /*
    * Draw the cube
    */
    void draw();

    bool Interactable(glm::vec3 visual);

    void AdjustPosition(glm::vec3 visual, glm::vec3 Direction);

    bool isBeingHeld() { return held; };

    void setHeld(bool dec) { held = dec; };


    /*
    * Return the model matrix
    */
    glm::mat4 getModel() { return model; }
    void setModel(glm::mat4 m) { model = m; };

    ShaderProgram getShaderProgram() { return lightShader; }

    unsigned int getVAO() { return VAO; }
};

