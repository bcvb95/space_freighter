#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera 
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_ortho = glm::ortho(0.0f, 800.0f , 500.0f, 0.0f, zNear, zFar);
        m_pos = pos;
        m_forward = glm::vec3(0,0,-1);
        m_up = glm::vec3(0,1,0);
    }

    inline glm::mat4 GetViewProjectionMatrix() const 
    {
        return m_ortho * glm::lookAt(m_pos, m_pos+m_forward , m_up);
    }

    glm::vec3* GetPos() {return &m_pos;}

protected:
private:
    glm::mat4 m_perspective;
    glm::mat4 m_ortho;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};


#endif