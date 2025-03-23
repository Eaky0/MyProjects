#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <irrKlang/irrKlang.h>
#include <iostream>
#include <TestCube.h>



#define GRAVITATION -9.81

//@author Atakan Kumas

class Camera
{
public:


	/**
	* Constructor:
	* 
	* Used for initializing direction coordinates.
	*/
	Camera();

	//Destructor:
	~Camera();


	/**
	* LookingAround:
	* 
	* Adjusts camera according to mouse movement
	* 
	* @pre Player is moving the mouse
	* 
	* @param Window the defined window for the application
	* @param xpos The current x position of the camera.
	* @param ypos The current y position of the camera.
	* 
	* @post The camera looks around in some direction
	*/
	void lookingAround(GLFWwindow* window, double xpos, double ypos);

	/**
	* zooming:
	*
	* Adjusts camera according to zoom scrolling
	*
	* @pre Player is scrolling with their mouse
	* 
	* @param Window the defined window for the application
	* @param yoffset The offset in the up-direction of the camera.
	* 
	* @post The camera zooms in or out
	*/
	void zooming(GLFWwindow* window, double yoffset);


	/**
	* changeCameraPosition:
	*
	* Adjusts the position of the camera
	*
	* @param x x-direction of the camera
	* @param y y-direction of the camera
	* @param z z-direction of the camera
	*/
	void changeCameraPosition(float x, float y, float z);

	/**
	* getView:
	*
	* returns the View matrix.
	* 
	* @return glm::mat4 View matrix for converting world coordinates into view coordinates
	*/
	glm::mat4 getView();


	/**
	* setView:
	*
	* @pre Any kind of movement (i.e. keypress, mouse moves, scrolling) has been made.
	*
	*/
	void setView();

	/**
	* getFovValue:
	*
	* returns the current field of view for this camera.
	*
	* @return float field of view
	* 
	* @post projection matrix inside the renderloop gets adjusted according to the fov's value
	* causing a possible zoom effect.
	* 
	*/	
	float getFovValue();


	/**
	* moveCamera:
	*
	* Adjusts camera according to key presses (WASD, SPACE, BACKSPACE, W + SHIFT)
	*
	* @pre Player pressed one of the mentioned key(s)(-combinations) inside the function.
	*
	* @param Window the defined window for the application
	* @param yoffset The offset in the up-direction of the camera.
	*
	* @post The camera zooms in or out
	*/
	void moveCamera(GLFWwindow* window);

	void CameraObjectInteraction(GLFWwindow* window, TestCube* c);

	/**
	* setSpeedParameters:
	*
	* Calculates and assigns time between 2 frames and the previous calculated frame.
	*
	*/
	void setSpeedParameters();

	/**
	* setSpeed
	*
	* Changes the movement speed of the camera
	* 
	* @param UnitPerSecond The amount of units per second when moving with the camera.
	*
	*/
	void setSpeed(float UnitPerSecond);


	void setHeight(float h) { Height = h; };


	/*
	* Returns the camera position
	*/
	glm::vec3 getCameraPos() { return cameraPosition; }

	glm::vec3 getVisualPos() { return cameraPosition + cameraZ; };
	glm::vec3 getDirection() { return dir; }

private:

	//Camera settings
	float Height = -69.2157f;
	float EyeLength = 5;


	glm::vec3 cameraPosition = glm::vec3(0.0f, -69.2157f, 0.0f); //7100.0f
	glm::vec3 cameraZ = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::vec3 cameraY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraZ, cameraY);

	//Movement speed
	float deltaFrame = 0.0f; // Time between current frame and last frame
	float prevFrame = 0.0f;
	float movementVelocity = 2.5f * deltaFrame;



	//Mouse input
	glm::vec3 dir;
	float prevX = 400, prevY = 300;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool initMouse = true;
	float Zoom = 20.0f;
	float Fov = 45.0f;


	//Jumping physics
	float mass = 100;
	float Fz;
	bool Jumping = false;
	float StartingHeight;


	//Sound Engine
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	irrklang::ISoundSource* jumpSource = engine->addSoundSourceFromFile("yippee.mp3");
	irrklang::ISoundSource* TeleportSource = engine->addSoundSourceFromFile("teleport.mp3");

};
