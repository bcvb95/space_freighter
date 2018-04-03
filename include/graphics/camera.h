#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <display.h>

#define FOV 70.0f
#define ZNEAR_ORTHO -1.0f
#define ZNEAR_PERSP 0.1f
#define ZFAR 1000.0f

class Camera 
{
public:
    Camera(const glm::vec3& pos, float width, float height, int type, Display* window);

    inline glm::mat4 GetViewProjectionMatrix() const 
    {
        if (m_camType == 0)
            return m_ortho * glm::lookAt(m_pos, m_pos+m_forward , m_up);
        else
            return m_perspective * glm::lookAt(m_pos, m_pos+m_forward, m_up);
    }

    void Zoom(bool zoomIn, float delta_time);
    void Move(glm::vec2 dir, float delta_time);

    // Getters
    glm::vec3* GetPos() {return &m_pos;}
    float* GetZoom() {return &m_zoom;}
    
    float GetCamWidth() {return m_camWidth;}
    float GetCamHeight() {return m_camHeight;}

    glm::vec2 GetMouseWorldPos() {return m_mouseWorldPos;}

    // Setters
    void SetZoom(float zoomVal) {m_zoom = zoomVal; this->Zoom(true, 0); }
    void SetMouseWorldPos(glm::vec2 pos) {m_mouseWorldPos = pos;}

protected:
private:
    int m_camType; // 0 for ortographic, 1 for perspective
    float m_maxzoom;
    float m_zoomspeed;
    float m_zoom;
    float m_speed;
    float m_camWidth;
    float m_camHeight;
    
    glm::vec2 m_mouseWorldPos;

    glm::mat4 m_perspective;
    glm::mat4 m_ortho;
    glm::vec3 m_pos;
    glm::vec3 m_forward;
    glm::vec3 m_up;

    Display* m_window;
};


#endif