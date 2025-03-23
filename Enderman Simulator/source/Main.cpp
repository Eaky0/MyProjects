
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>

/*-------own classes-------*/
#include <Shader.h>
#include <Window.h>
#include <Camera.h>
#include <MeshMap.h>
#include <ShaderProgram.h>
#include <Object.h>
#include <CoolCube.h>
#include <Lamp.h>
#include <TestCube.h>
#include <CubeMap.h>
#include <IndexBuffer.h>
#include <Moon.h>
/*-------------------------*/

void renderLoop(Window w);
void DrawTrees(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& tree, MeshMap& map, int renderdistance);
void DrawBushes(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& bush, MeshMap& map, int Random1, int Random2, int renderdistance);
void DrawSkeletonEntities(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& Skeleton, MeshMap& map, int Random1, int Random2, int renderdistance);
void processInput(GLFWwindow*);
void mouseMovement(GLFWwindow* window, double xpos, double ypos);
void zoomProcess(GLFWwindow* window, double xoffset, double yoffset);
void drawCube(TestCube& cube, const glm::mat4& projection, Moon& moon, Lamp& lamp, const Texture& textCube, const Texture& specular);
void drawlamp(Lamp &lamp, const glm::mat4 &projection);
void drawMoon(Moon& moon, const glm::mat4& projection);
void setupGlobalLight(ShaderProgram& shader, glm::vec3 LightColor);
void setupLampLight(ShaderProgram& shader, Lamp& moon);
void setupObjectMaterial(ShaderProgram& shader);

//Window settings
const unsigned int WINDOW_WIDTH = 900;
const unsigned int WINDOW_HEIGHT = 700;

Camera cam = Camera();

void setupWindow(Window &simWindow) {
    glfwSetCursorPosCallback(simWindow.getGLFWWindow(), mouseMovement);
    glfwSetScrollCallback(simWindow.getGLFWWindow(), zoomProcess);

}

int main() {
    Window simWindow = Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Sim");
    setupWindow(simWindow);
    
    glEnable(GL_DEPTH_TEST);
    
    renderLoop(simWindow);

    glfwTerminate();
    return 0;
}

void clearBuffers() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawTerrain(Texture &grassTexture, Texture &rockTexture, Texture &grassSpecTexture, Texture &rockSpecTexture, MeshMap &map) {
    // bind correct texture to texture units
    glActiveTexture(GL_TEXTURE0);
    grassTexture.bind();
    glActiveTexture(GL_TEXTURE1);
    rockTexture.bind();
    glActiveTexture(GL_TEXTURE2);
    grassSpecTexture.bind();
    glActiveTexture(GL_TEXTURE3);
    rockSpecTexture.bind();

    map.draw();

    //unbind all textures
    rockSpecTexture.unbind();
    glActiveTexture(GL_TEXTURE2);
    grassSpecTexture.unbind();
    glActiveTexture(GL_TEXTURE1);
    rockTexture.unbind();
    glActiveTexture(GL_TEXTURE0);
    grassTexture.unbind();
}

void loadSkybox(ShaderProgram &shader, CubeMap &skybox, glm::mat4 projection) {
    glDepthFunc(GL_LEQUAL);
    shader.use();

    glm::mat4 U_VP = projection * glm::mat4(glm::mat3(cam.getView()));
    shader.setUniformMatrix4fv("U_VP", U_VP);

    skybox.draw();
    glDepthFunc(GL_LESS);
}

void cameraSetup(MeshMap &map, Window &wind, TestCube &cube) {
    glm::vec3 currentCamPos = cam.getCameraPos();
    cam.setHeight(map.getHeightOf(currentCamPos.x, currentCamPos.z));
    cam.moveCamera(wind.getGLFWWindow());


    if (cube.Interactable(cam.getVisualPos() + cam.getDirection())) {
        cam.CameraObjectInteraction(wind.getGLFWWindow(), &cube);
    }
    else if (cube.isBeingHeld()) {
        cam.CameraObjectInteraction(wind.getGLFWWindow(), &cube);
    }

    cam.setSpeedParameters();
    cam.setView();
}

void renderLoop(Window wind) {
    glEnable(GL_DEPTH_TEST);

    //Skybox
    ShaderProgram skyboxShader = ShaderProgram("SkyboxVertexShader.txt", "SkyboxFragmentShader.txt");
    skyboxShader.use();
    skyboxShader.setInt("cubemap", 0);

    CubeMap skybox = CubeMap();

    //Objects
    ShaderProgram ObjectShader("ObjectVertexShader.txt", "ObjectFragmentShader.txt");

    ObjectLoader Tree("Models\\Tree\\Tree.fbx");
    ObjectLoader Bush("Models\\Bush\\Bush01.fbx");
    ObjectLoader Skeleton("Models\\Skeleton\\Spooky_Skeleton.fbx");
    ObjectLoader Pole("Models\\Lichtpaal\\Lightpole.obj");


    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 mvp;
    //Generate Random Numbers for tree rendering:
    std::random_device rd;
    std::mt19937 gen(rd());
    int minNum = 1;
    int maxNum = 10;
    std::uniform_int_distribution<> dist(minNum, maxNum);

    int randomNumber = 0, randomNumber2 = 0, randomNumber3 = 0, randomNumber4 = 0;
    while (randomNumber == randomNumber3 && randomNumber2 == randomNumber4) {
        randomNumber = dist(gen) * 15;
        randomNumber2 = dist(gen) * 15;
        randomNumber3 = dist(gen) * 15;
        randomNumber4 = dist(gen) * 15;
    }

    //Distance needed from camera to objects to render
    float renderdistance = 1000.0f;

    //Terrain
    ShaderProgram TerrainShader = ShaderProgram("VertexShader.txt", "FragmentShader.txt");
    TerrainShader.use();

    //Terrain map
    MeshMap map = MeshMap("iceland_heightmap.png");

    //Terrain Textures
    Texture grassTexture = Texture("grassy_d.png"), grassSpecTexture = Texture("grassy_s.png");
    Texture rockTexture = Texture("rock.jpg"), rockSpecTexture = Texture("rockSpecular.jpg");

    TerrainShader.setInt("GrassyTextureSample", 0);
    TerrainShader.setInt("rockTexture", 1);
    TerrainShader.setInt("GrassySpecularTexture", 2);
    TerrainShader.setInt("rockSpecularTexture", 3);

    //Objects
    Lamp lamp = Lamp();
    lamp.loadBuffers();

    Moon moon = Moon();
    moon.loadBuffers();

    TestCube cube = TestCube();
    Texture textCube = Texture("LuckyBlock.png");
    Texture hightlighted_textCube = Texture("HighlightedLuckyBlock.png");
    Texture textCubeSpecular = Texture("container3.png");

    cube.loadBuffers();

    while (!wind.closed()){   
        processInput(wind.getGLFWWindow());
        clearBuffers();
        cameraSetup(map, wind, cube);

        //Set the Model view projection matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(cam.getFovValue()),
            (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 30000.0f);
        glm::mat4 mvp = projection * cam.getView() * model;

        //Set terrainshader
        TerrainShader.use();
        TerrainShader.setUniformMatrix4fv("U_MVP", mvp);
        TerrainShader.setUniformMatrix4fv("model", model);
        TerrainShader.setUniform3f("cameraPos", cam.getCameraPos());

        //Set light properties
        setupGlobalLight(TerrainShader, moon.getColor());    //moonlight blue : glm::vec3(0.839215f, 0.862745f, 0.890196f)
        setupLampLight(TerrainShader, lamp);

        //draw terrain
        drawTerrain(grassTexture, rockTexture, grassSpecTexture, rockSpecTexture, map);




        //Draw Objects
        if (cube.isBeingHeld()) {
            cube.AdjustPosition(cam.getVisualPos(), cam.getDirection());
        }

        if (cube.Interactable(cam.getVisualPos() + cam.getDirection()) && !cube.isBeingHeld()) {
            drawCube(cube, projection, moon, lamp, hightlighted_textCube, textCubeSpecular);
        }
        else {
            drawCube(cube, projection, moon, lamp, textCube, textCubeSpecular);
        }

        drawlamp(lamp, projection);
        drawMoon(moon, projection);

        

        ////Draw Trees
        DrawTrees(ObjectShader, projection, Tree, map, renderdistance);

        ////Draw Bushes
        DrawBushes(ObjectShader, projection, Bush, map, randomNumber, randomNumber2, renderdistance);

        ///Draw Skeletons 

        ShaderProgram s_shader = moon.getShaderProgram();
        DrawSkeletonEntities(s_shader, projection, Skeleton, map, randomNumber3, randomNumber4, renderdistance);


        //Draw a lantern:
        ObjectShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.0f, -120.0f, 45.0f));
        mvp = projection * cam.getView() * model;
        ObjectShader.setUniformMatrix4fv("U_MVP", mvp);

        Pole.DrawObject(&ObjectShader);



        //SkyBox
        loadSkybox(skyboxShader, skybox, projection);

        //Get ready for next loop
        glfwSwapBuffers(wind.getGLFWWindow());
        glfwPollEvents();
    }
}

void DrawTrees(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& tree, MeshMap& map, int renderdistance) {
    //Draw Trees

    obj.use();

    int dividend = 50;
    int dividend2 = 100;

    glm::mat4 model;
    glm::mat4 mvp;

    glm::vec3 currentCamPos = cam.getCameraPos();


    for (int i = 0; i < map.getHeight(); i++) {


        if (i % dividend2 == 0) {


            if (dividend2 == 100) {
                dividend2 = 50;
            }
            else {
                dividend2 = 100;
            }

            for (int j = 5; j < map.getWidth(); j += 5) {

                if (j % dividend == 0) {

                    if (dividend == 50) {
                        dividend = 100;
                    }
                    else {
                        dividend = 50;
                    }



                    float x = i - ((float)map.getHeight()) / 2;
                    float z = j - ((float)map.getWidth()) / 2;
                    float y = map.getHeightOf(x, z);



                    float d = sqrt(pow(z - currentCamPos.z, 2) + pow(x - currentCamPos.x, 2));


                    if (d < renderdistance && y < -100)
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(x, y, z));
                        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
                        mvp = projection * cam.getView() * model;

                        obj.setUniformMatrix4fv("U_MVP", mvp);
                        tree.DrawObject(&obj);

                    }
                }
            }
        }
        
    }

}

void DrawBushes(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& bush, MeshMap &map, int Random1, int Random2, int renderdistance) {
    //Draw Bushes

    obj.use();

    glm::mat4 model;
    glm::mat4 mvp;

    glm::vec3 currentCamPos = cam.getCameraPos();



    for (int i = 0; i < map.getHeight(); i++) {

        if (i % Random1 == 0) {

            for (int j = 2; j < map.getWidth(); j += 2) {

                if (j % Random2 == 0) {

                    float x = i - ((float)map.getHeight()) / 2;
                    float z = j - ((float)map.getWidth()) / 2;
                    float y = map.getHeightOf(x, z);


                    float d = sqrt(pow(z - currentCamPos.z, 2) + pow(x - currentCamPos.x, 2));


                    if (d < renderdistance && y < -100)
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(x, y, z));
                        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
                        mvp = projection * cam.getView() * model;

                        obj.setUniformMatrix4fv("U_MVP", mvp);
                        bush.DrawObject(&obj);

                    }
                }
            }
        }
    }
}



void DrawSkeletonEntities(ShaderProgram& obj, const glm::mat4& projection, ObjectLoader& Skeleton, MeshMap& map, int Random1, int Random2, int renderdistance) {
    //Draw Bushes

    obj.use();

    glm::mat4 model;
    glm::mat4 mvp;

    glm::vec3 currentCamPos = cam.getCameraPos();



    for (int i = 0; i < map.getHeight(); i++) {

        if (i % Random1 == 0) {

            for (int j = 2; j < map.getWidth(); j += 2) {

                if (j % Random2 == 0) {

                    float x = i - ((float)map.getHeight()) / 2;
                    float z = j - ((float)map.getWidth()) / 2;
                    float y = map.getHeightOf(x, z);


                    float d = sqrt(pow(z - currentCamPos.z, 2) + pow(x - currentCamPos.x, 2));


                    if (d < renderdistance && y < -100)
                    {
                        model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(x, y, z));
                        model = glm::scale(model, glm::vec3(0.0125f, 0.0125f, 0.0125f));
                        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.0f, 1.0f, 0.0f));
                        mvp = projection * cam.getView() * model;

                        obj.setUniformMatrix4fv("U_MVP", mvp);

                        Skeleton.DrawObject(&obj);

                    }
                }
            }
        }
    }

}

void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}

void mouseMovement(GLFWwindow* window, double xpos, double ypos)
{

    // Adjust the camera's view based on the offset
    cam.lookingAround(window, xpos, ypos);
}

void zoomProcess(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.zooming(window, yoffset);
}

void drawCube(TestCube &cube, const glm::mat4& projection, Moon& moon, Lamp &lamp, const Texture &textCube, const Texture &specular) {
    ShaderProgram ObjectShader = cube.getShaderProgram();
    ObjectShader.use();

    glm::mat4 mvp3 = projection * cam.getView() * cube.getModel();

    //ObjectShader.setUniform3f("lightSource_pos", moon.getWorldPos()); //set incase lamp
    ObjectShader.setUniform3f("cameraPos", cam.getCameraPos());

    //setup global light & object material
    ObjectShader.setUniform3f("lamp.posistion", lamp.getWorldPos());
    ObjectShader.setUniform3f("lamp.prop.color", glm::vec3(1.0f, 0.81960784313f, 0.278431372549019f));    //flame yellow :  1.0f, 0.81960784313f, 0.278431372549019f
    ObjectShader.setUniform3f("lamp.prop.ambient", 0.3f, 0.3f, 0.3f);
    ObjectShader.setUniform3f("lamp.prop.diffuse", 1.0f, 1.0f, 1.0f);
    ObjectShader.setUniform3f("lamp.prop.specular", 0.8f, 0.8f, 0.8f);

    setupGlobalLight(ObjectShader, moon.getColor()); 
    setupObjectMaterial(ObjectShader);

    ObjectShader.setUniformMatrix4fv("U_MVP", mvp3);
    ObjectShader.setUniformMatrix4fv("model", cube.getModel());
 
    //bind the textures
    glActiveTexture(GL_TEXTURE0);
    textCube.bind();
    glActiveTexture(GL_TEXTURE1);
    specular.bind();
    
    //draw the cube
    cube.draw();

    //unbind all
    specular.unbind();
    glActiveTexture(GL_TEXTURE0);
    textCube.unbind();
}

void setupGlobalLight(ShaderProgram &shader, glm::vec3 LightColor) {
    shader.setUniform3f("moon.prop.color", LightColor);
    shader.setUniform3f("moon.direction", -0.2f, -1.0f, -0.3f); //-0.5, -1.0, -0.5
    shader.setUniform3f("moon.prop.ambient", 0.0f, 0.0f, 0.0f);
    shader.setUniform3f("moon.prop.diffuse", 0.3f, 0.3f, 0.3f);
    shader.setUniform3f("moon.prop.specular", 0.5f, 0.5f, 0.5f);
}

void setupLampLight(ShaderProgram& shader, Lamp&moon) {
    shader.setUniform3f("lightCube.posistion", moon.getWorldPos());
    shader.setUniform3f("lightCube.prop.color", glm::vec3(1.0f, 0.81960784313f, 0.278431372549019f));    //flame yellow :  1.0f, 0.81960784313f, 0.278431372549019f
    shader.setUniform3f("lightCube.prop.ambient", 0.3f, 0.3f, 0.3f);
    shader.setUniform3f("lightCube.prop.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setUniform3f("lightCube.prop.specular", 0.8f, 0.8f, 0.8f);
}

void setupObjectMaterial(ShaderProgram& shader) {
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    shader.setFloat("material.shininess", 32.0f);
}

void drawlamp(Lamp&moon, const glm::mat4 &projection) {
    ShaderProgram moonShader = moon.getShaderProgram();
    moonShader.use();

    moonShader.setUniform3f("lampColor", moon.getColor());
    glm::mat4 mvp2 = projection * cam.getView() * moon.getModel();
    moonShader.setUniformMatrix4fv("U_MVP", mvp2);
    moon.draw();
}

void drawMoon(Moon& moon, const glm::mat4& projection) {
    ShaderProgram moonShader = moon.getShaderProgram();
    moonShader.use();

    moonShader.setUniform3f("lampColor", moon.getColor());
    glm::mat4 mvp2 = projection * cam.getView() * moon.getModel();
    moonShader.setUniformMatrix4fv("U_MVP", mvp2);
    moon.draw();
}
