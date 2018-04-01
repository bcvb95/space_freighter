#include <camera.h>


Camera::Camera(const glm::vec3& pos, float width, float height, int type)
{
    m_camType=type;
    m_aspect = width / height;
    m_width = width;
    m_height = height;

    if (type==1)
        m_perspective = glm::perspective(FOV, m_aspect, ZNEAR_PERSP, ZFAR);
    else
        this->SetZoom(0.1); // sets the orthographic matrix with the zoom value
        this->UpdateWithZoom();

    m_pos = pos;
    m_forward = glm::vec3(0,0,-1);
    m_up = glm::vec3(0,1,0);
}


void Camera::UpdateWithZoom()
{
    float min = -pow(10, m_zoom);
    float max = pow(10, m_zoom);
    if (m_width >= m_height){
        m_ortho = glm::ortho(min*m_aspect,max*m_aspect, min, max, ZNEAR_ORTHO, ZFAR);
    }else {
        m_ortho = glm::ortho(min,max, min/m_aspect, max/m_aspect, ZNEAR_ORTHO, ZFAR);
    }
    
}