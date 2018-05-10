#ifndef GUI_OBJECTS_H
#define GUI_OBJECTS_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <iostream>

#include <gui_constants.h>
#include <display.h>
#include <texture.h>
#include <shader.h>

namespace GUI {


    struct RectTransform
    {
        glm::vec2 top_left;
        glm::vec2 top_right;
        glm::vec2 bottom_left;
        glm::vec2 bottom_right;

        glm::vec2 vert_tl;
        glm::vec2 vert_tr;
        glm::vec2 vert_bl;
        glm::vec2 vert_br;

        RectTransform(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, glm::vec2 pos, glm::vec2 size) 
            : top_left(tl), top_right(tr), bottom_left(bl), bottom_right(br) 
            {
                vert_tl = pos + (size * top_left);
                vert_tr = pos + (size * top_right);
                vert_bl = pos + (size * bottom_left);
                vert_br = pos + (size * bottom_right);
            }
    };

    struct TextureStruct 
    {
        GLuint vertexArrayObject;
        GLuint vertexArrayBuffer;
        Texture* texture;
        GUI_Shader* shader;

        TextureStruct (GUI_Shader* gui_shader, Texture* tex) : shader(gui_shader), texture(tex) 
        {
            // Configure VAO/VBO for texture quads
            glGenVertexArrays(1, &vertexArrayObject);
            glGenBuffers(1, &vertexArrayBuffer);

            glBindVertexArray(vertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };

    class Panel
    {
    public:
        Panel(unsigned int id); 
        ~Panel();

        void SetRectTransform(RectTransform* rect) {this->m_rect = rect;}

        int GetID() {return m_id;} 
        Panel* GetParent() {return m_parent;}
        void SetParent(Panel* parent) {this->m_parent = parent;}

        int GetChildCount() {return m_childCount;}
        void AddChildPanel(Panel* child_panel);
        void RemoveChildPanel(Panel* child_panel);

        void InitTexture(GUI_Shader* shader, Texture* texture);
        void DrawPanel(Camera* cam);


    private:
        RectTransform* m_rect;

        unsigned int m_id;
        Panel* m_parent;

        int m_childCount = 0; 
        Panel* m_childrenPanels[MAX_CHILD_PANELS];

        TextureStruct* m_texStruct = NULL;
    };


    class Canvas
    {
    public:
        Canvas(Display* window);
        ~Canvas();

        Panel* NewPanel(Panel* parent = NULL);
        void DeletePanel(Panel* panel);

    private:
        // rect defining the size of the canvas
        int m_width, m_height;
        unsigned int m_unique_panelID = 1;

        int m_numPanels = 0;
        Panel* m_rootPanelList[MAX_PANELS_IN_CANVAS]; 
    };

    void RemoveFromPanelList(Panel* panel, Panel** panel_list, int* count);
}


#endif