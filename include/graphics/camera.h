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
    Camera(const glm::vec3& pos, float width, float height, int type);

    void UpdateWithZoom();

    glm::vec3* GetPos() {return &m_pos;}
    float* GetZoom() {return &m_zoom;}

    void SetZoom(float zoomVal) {m_zoom = zoomVal;}

    inline glm::mat4 GetViewProjectionMatrix() const 
    {
        if (m_camType == 0)
            return m_ortho * glm::lookAt(m_pos, m_pos+m_forward , m_up);
        else
            return m_perspective * glm::lookAt(m_pos, m_pos+m_forward, m_up);
    }


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