#include <iostream>
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
    {
        this->SetZoom(0.1); // sets the orthographic matrix with the zoom value
        glm::vec3 defdir(0.0f,0.0f,0.0f);
        this->Update(defdir , 0.0f);
    }

    m_speed = 2.0f;
    m_pos = pos;
    m_forward = glm::vec3(0,0,-1);
    m_up = glm::vec3(0,1,0);
}

void Camera::Update(glm::vec3 dir, float delta_time)
{   
    // zoom/scale limits.
    if (m_zoom < 0.0f) {
        m_zoom = 0.0f;
    } else if(m_zoom > 3.0f){
        m_zoom = 3.0f;
    } 

    // set pan speed based on fraction of zooming
    float pan_factor = 4.0f;
    float zoom_frag = m_zoom / 3.0f; 
    m_speed = zoom_frag*pow(pan_factor, 4);

    // pan camera
    if (dir.x || dir.y)
    {
        m_pos += dir * (float)delta_time * m_speed; // move camera
    }

    // Make zoom.
    float min = -pow(10, m_zoom);
    float max = pow(10, m_zoom);
    if (m_width >= m_height){
        m_ortho = glm::ortho(min*m_aspect,max*m_aspect, min, max, ZNEAR_ORTHO, ZFAR);
    }else {
        m_ortho = glm::ortho(min,max, min/m_aspect, max/m_aspect, ZNEAR_ORTHO, ZFAR);
    }
    
}