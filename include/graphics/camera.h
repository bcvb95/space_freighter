#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#define FOV 70.0f
#define ZNEAR_ORTHO -1.0f
#define ZNEAR_PERSP 0.1f
#define ZFAR 1000.0f

class Camera 
{
public:
    Camera(const glm::vec3& pos, float width, float height, int type)
    {
        m_camType=type;
        m_aspect = width / height;
        m_width = width;
        m_height = height;

        if (type==1)
            m_perspective = glm::perspective(FOV, m_aspect, ZNEAR_PERSP, ZFAR);
        else
            this->SetZoom(1); // sets the orthographic matrix with the zoom value
            this->UpdateWithZoom();

        m_pos = pos;
        m_forward = glm::vec3(0,0,-1);
        m_up = glm::vec3(0,1,0);
    }

    void UpdateWithZoom()
    {
        float min = -pow(10, m_zoom);
        float max = pow(10, m_zoom);
        if (m_width >= m_height){
            m_ortho = glm::ortho(min*m_aspect,max*m_aspect, min, max, ZNEAR_ORTHO, ZFAR);
        }else {
            m_ortho = glm::ortho(min,max, min/m_aspect, max/m_aspect, ZNEAR_ORTHO, ZFAR);
        }
        
    }

    void SetZoom(float zoomVal) {m_zoom = zoomVal;}
    float* GetZoom() {return &m_zoom;}

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
    float m_aspect;
    float m_width;
    float m_height;

    glm::mat4 m_perspective;
    glm::mat4 m_ortho;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};


#endif