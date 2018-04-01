#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Transform
{
    public:
    Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0,1.0,1.0))
    {
        this->pos = pos;
        this->rot = rot;
        this->scale = scale;
    }
    Transform(const Transform& other) {};

    

    inline glm::vec3* GetPos() {return &pos;}
    inline glm::vec3* GetRot() {return &rot;}
    inline glm::vec3* GetScale() {return &scale;}

    inline void SetPos(const glm::vec3& pos) {this->pos = pos;}
    inline void SetRot(const glm::vec3& rot) {this->rot = rot;}
    inline void SetScale(const glm::vec3& scale) {this->scale = scale;}

    inline glm::mat4 GetTransformMatrix() const 
    {
		glm::mat4 scaleMat = glm::scale(scale);

        glm::mat4 posMat = glm::translate(pos); // translate back to origin
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0)); // do rotation
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;


		return posMat * rotMat * scaleMat; 
    }
    protected:
    private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

};


#endif
