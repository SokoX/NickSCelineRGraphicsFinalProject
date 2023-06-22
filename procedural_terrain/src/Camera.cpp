#include "Camera.hpp"

#include "glm/gtx/transform.hpp"

#include <iostream>

void Camera::MouseLook(int mouseX, int mouseY){
    // Record our new position as a vector
    glm::vec2 newMousePosition(mouseX, mouseY);
    // Detect how much the mouse has moved since
    // the last time
    glm::vec2 mouseDelta = 0.005f*(newMousePosition-m_oldMousePosition);
    glm::vec3 m_leftVector = glm::cross(m_upVector, m_viewDirection);

    m_viewDirection = glm::mat3(glm::rotate(-mouseDelta.x, m_upVector)) * glm::mat3(glm::rotate(mouseDelta.y, m_leftVector)) * m_viewDirection;
    
    // Update our old position after we have made changes 
    m_oldMousePosition = newMousePosition;
}

// OPTIONAL TODO: 
//               The camera could really be improved by
//               updating the eye position along the m_viewDirection.
//               Think about how you can do this for a better camera!

void Camera::MoveForward(float speed)
{
    m_eyePosition.z += m_viewDirection.z * speed;
    m_eyePosition.x += m_viewDirection.x * speed;
}

void Camera::MoveBackward(float speed)
{
    m_eyePosition.z -= m_viewDirection.z * speed;
    m_eyePosition.x -= m_viewDirection.x * speed;
}

void Camera::MoveLeft(float speed)
{
    glm::vec3 m_leftVector = glm::cross(m_upVector, m_viewDirection);
    m_eyePosition.x += m_leftVector.x * speed;
    m_eyePosition.z += m_leftVector.z * speed;
}

void Camera::MoveRight(float speed)
{
    glm::vec3 m_rightVector = glm::cross(m_viewDirection, m_upVector);
    m_eyePosition.x += m_rightVector.x * speed;
    m_eyePosition.z += m_rightVector.z * speed;
}

void Camera::MoveUp(float speed)
{
    m_eyePosition.y += m_upVector.y * speed;
}

void Camera::MoveDown(float speed)
{
    m_eyePosition.y -= m_upVector.y * speed;
}

// Set the position for the camera
void Camera::SetCameraEyePosition(float x, float y, float z){
    m_eyePosition.x = x;
    m_eyePosition.y = y;
    m_eyePosition.z = z;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}


Camera::Camera(){
    std::cout << "(Constructor) Created a Camera!\n";
	// Position us at the origin.
    m_eyePosition = glm::vec3(0.0f,0.0f, 0.0f);
	// Looking down along the z-axis initially.
	// Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
	// For now--our upVector always points up along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}
