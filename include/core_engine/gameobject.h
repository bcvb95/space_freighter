#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <transform.h>
#include <sprite.h>
#include <camera.h>
#include <math.h>

class GameObject
{
public:
    GameObject(const std::string& go_name) : m_name(go_name) 
    {
        m_transform = new Transform();

        // rotate all gameobjects 180
        m_transform->GetRot()->y += M_PI;
    };

    virtual ~GameObject()
    {
        delete m_transform;
    }

    std::string GetName() {return m_name;}
    Transform* GetTransform() {return m_transform;}

protected:
    Transform* m_transform;
    std::string m_name;
};

class DrawableGameObject : public GameObject
{
    public:
        DrawableGameObject(const std::string& go_name, Texture* _texture, BasicShader* _shader) :  GameObject(go_name)
        {
            m_sprite = new Sprite(_texture, _shader);
        };
        
        ~DrawableGameObject() 
        {
            delete m_sprite;
        }
        
        void DrawSprite() 
        {
            m_sprite->Draw(m_transform);
        };

        Sprite* GetSprite() {return m_sprite;};

    protected:
        Sprite* m_sprite;
};

#endif