#include <iostream>
#include <camera.h>


Camera::Camera(const glm::vec3& pos, float width, float height, int type, Display* window)
{
    m_camType=type;
    m_window = window;
     
    m_zoom = 1.0f;
    m_maxzoom = 5.0f;
    m_zoomspeed = 0.05f;

    float windowAspect = m_window->GetWindowAspect();

    if (type==1)
        m_perspective = glm::perspective(FOV, windowAspect, ZNEAR_PERSP, ZFAR);
    else
    {
        // Make zoom.
        float min = -pow(10.0f, m_zoom);
        float max = pow(10.0f, m_zoom);
        this->m_ortho = glm::ortho(min*windowAspect,max*windowAspect, min, max, ZNEAR_ORTHO, ZFAR);
        
        m_camWidth = max*windowAspect - min*windowAspect;
        m_camHeight = max - min;
    }
    m_pos = pos;
    m_forward = glm::vec3(0,0,-1);
    m_up = glm::vec3(0,1,0);
}

void Camera::Zoom(bool zoomIn, float delta_time)
{
    // Ensure zoom limits.
    if (m_zoom <= 1.0f) { m_zoom = 1.0f; } 
    else if(m_zoom >= m_maxzoom){ m_zoom = m_maxzoom; } 

    if (zoomIn) { m_zoom -= m_zoomspeed; } 
    else { m_zoom += m_zoomspeed; }
    // if zooming in move camera towards target zoom point (mousepos in world coords)
    if (zoomIn)
        m_pos += (glm::vec3(m_mouseWorldPos, 1) - m_pos) * 0.1f; 
    
    float winAspect = m_window->GetWindowAspect(); 
    float winWidth = (float)(m_window->GetWindowWidth());
    float winHeight = (float)(m_window->GetWindowHeight());

    // calculate limits for camera based on zoom
    float min = -pow(10.0f, m_zoom);         
    float max = pow(10.f, m_zoom);

    float left, right, bottom, top;
    if (winWidth >= winHeight) 
    {
        left = min*winAspect; 
        right = max*winAspect; 
        bottom = min;
        top = max;
    } else {
        left = min;
        right = max;
        bottom = min/winAspect;
        top = max/winAspect;
    }

    // update camera size
    m_camWidth = right - left;
    m_camHeight = top - bottom;

    // update perspective matrix
    this->m_ortho = glm::ortho(left, right, bottom, top, ZNEAR_ORTHO, ZFAR);

}

void Camera::Move(glm::vec2 dir, float delta_time)
{   
    // set pan speed based on fraction of zooming
    float pan_factor = 2.0f;
    float max_pan = 10000.0f;
    float min_pan = 1.0f;
    float zoom_frac = m_zoom / m_maxzoom;
    m_speed = max_pan * pow(zoom_frac, 4) + min_pan * (1 - zoom_frac);

    // pan camera
    m_pos += glm::vec3(dir,0) * delta_time * m_speed; //pan_factor * m_speed;

}