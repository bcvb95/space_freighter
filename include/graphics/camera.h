#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#define FOV 70.0f
#define ZNEAR 0.1f
#define ZFAR 1000.0f


class Camera 
{
public:
    Camera(const glm::vec3& pos, float width, float height, int type)
    {
        m_camType=type;
        if (type==1)
            m_perspective = glm::perspective(FOV, width/height, ZNEAR, ZFAR);
        else
            m_ortho = glm::ortho(0.0f, width , height, 0.0f, ZNEAR, ZFAR);

        m_pos = pos;
        m_forward = glm::vec3(0,0,-1);
        m_up = glm::vec3(0,1,0);
        m_zoom = 1;
        SetZoom();
    }

    void SetZoom()
    {
        float min = -pow(10, m_zoom);
        float max = pow(10, m_zoom);
        m_ortho = glm::ortho(min,max, min, max, ZNEAR, ZFAR);
    }

    void Zoom(float zoomVal) {m_zoom += zoomVal; this->SetZoom();}

    inline glm::mat4 GetViewProjectionMatrix() const 
    {
        if (m_camType == 0)
            return m_ortho * glm::lookAt(m_pos, m_pos+m_forward , m_up);
        else
            return m_perspective * glm::lookAt(m_pos, m_pos+m_forward, m_up);
    }

    glm::vec3* GetPos() {return &m_pos;}

protected:
private:
    int m_camType;
    float m_zoom;

    glm::mat4 m_perspective;
    glm::mat4 m_ortho;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};


#endif