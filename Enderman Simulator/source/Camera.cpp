#include <Camera.h>

Camera::Camera()
{
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    Fz = mass * GRAVITATION;

    jumpSource->setDefaultVolume(0.5f);

}

Camera::~Camera()
{
    engine->drop();
}

void Camera::lookingAround(GLFWwindow* window, double x_pos, double y_pos) {
    if (initMouse)
    {
        prevX = x_pos;
        prevY = y_pos;
        initMouse = false;
    }


    float xoffset = x_pos - prevX;
    float yoffset = prevY - y_pos;
    prevX = x_pos;
    prevY = y_pos;
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;


    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraZ = glm::normalize(dir);

}


void Camera::zooming(GLFWwindow* window, double offset_y) {
    Zoom -= (float)offset_y;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
    Fov = Zoom;
}

void Camera::changeCameraPosition(float x, float y, float z)
{
    cameraPosition = glm::vec3(x, y, z);
}

glm::mat4 Camera::getView()
{
    return view;
}

void Camera::setView()
{

    glm::vec3 visual = cameraPosition + cameraZ;

    view = glm::lookAt(cameraPosition, cameraPosition + cameraZ, cameraY);

    //std::cout << "x = " << (cameraPosition.x) << ",  y = " << (cameraPosition.y) << ", z = " << (cameraPosition.z) << std::endl;
    //std::cout << "pitch = " << pitch << ", yaw = " << yaw;
}

float Camera::getFovValue()
{
    return Fov;
}

void Camera::moveCamera(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

        if (!Jumping) {
            setSpeed(10.0f);
            cameraPosition = cameraPosition + movementVelocity * cameraZ;
        }
        else {
            cameraPosition = cameraPosition + cameraZ;

        }

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

        if (!Jumping) {
            setSpeed(10.0f);
            cameraPosition = cameraPosition + movementVelocity * cameraZ;
        }
        else {
            cameraPosition = cameraPosition + cameraZ;

        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

        if (!Jumping) {
            setSpeed(10.0f);
            cameraPosition -= movementVelocity * cameraZ;
        }
        else {
            cameraPosition -= cameraZ;

        }

    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {


        if (!Jumping) {
            setSpeed(10.0f);
            cameraPosition -= glm::normalize(glm::cross(cameraZ, cameraY)) * movementVelocity;
        }
        else {
            cameraPosition -= glm::normalize(glm::cross(cameraZ, cameraY));


        }

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

    
        if (!Jumping) {
            setSpeed(10.0f);
            cameraPosition += glm::normalize(glm::cross(cameraZ, cameraY)) * movementVelocity;
        }
        else {
            cameraPosition += glm::normalize(glm::cross(cameraZ, cameraY));


        }
    
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !Jumping) {

        setSpeed(10.0f);

        float TeleportDistance = 50.0f;

        cameraPosition += cameraZ * TeleportDistance;

        if (!engine->isCurrentlyPlaying(TeleportSource)) {
            engine->play3D(TeleportSource, irrklang::vec3df(0, 0, 0), false, false);

        }

    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        
        Jumping = true;


    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

        Jumping = true;
    }


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        Jumping = true;
        StartingHeight = Height;        
    }





    /// Edges
    if (cameraPosition.z < -1312.0f) {
        cameraPosition.z = -1311.99f;
    }

    if (cameraPosition.z > 1312.0f) {
        cameraPosition.z = 1311.99f;
    }

    if (cameraPosition.x > 878.0f) {
        cameraPosition.x = 877.99f;
    }

    if (cameraPosition.x < -878.0f) {
        cameraPosition.x = -877.99f;
    }

    /// Corners

    if (cameraPosition.z < -1312.0f && cameraPosition.x < -878.0f) {
        cameraPosition.z = -1311.99f;
        cameraPosition.x = -877.99f;
    }

    if (cameraPosition.z > 1312.0f && cameraPosition.x > 878.0f) {
        cameraPosition.z = 1311.99f;
        cameraPosition.x = 877.99f;
    }

    if (cameraPosition.x > 878.0f && cameraPosition.z < -1312.0f) {
        cameraPosition.z = -1311.99f;
        cameraPosition.x = 877.99f;
    }

    if (cameraPosition.x < -878.0f && cameraPosition.z > 1312.0f) {
        cameraPosition.z = 1311.99f;
        cameraPosition.x = -877.99f;
    }
  


    if (Jumping && cameraPosition.y >= Height + EyeLength) {
        cameraPosition.y += EyeLength + movementVelocity * deltaFrame;
        movementVelocity += Fz * deltaFrame;

        if (!engine->isCurrentlyPlaying(jumpSource)) {
            engine->play3D(jumpSource, irrklang::vec3df(0, 0, 0), false, false);

        }
    }
    else {
        Jumping = false;
    }


    if (!Jumping) {
        cameraPosition.y = Height + EyeLength;
    }


}

void Camera::CameraObjectInteraction(GLFWwindow* window, TestCube * c) {


    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        c->setHeld(true);
        c->AdjustPosition(getVisualPos(), dir);
    }

    if (c->isBeingHeld()) {
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            c->setHeld(false);

        }
    }




}





void Camera::setSpeedParameters()
{
    float currentFrame = glfwGetTime();
    deltaFrame = currentFrame - prevFrame;
    prevFrame = currentFrame;

}

void Camera::setSpeed(float UnitPerSecond)
{
    movementVelocity = UnitPerSecond * deltaFrame;
}


