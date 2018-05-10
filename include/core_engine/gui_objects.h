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

    //////////////////////////////////////////////////////////////////
    // RectTransform
    //////////////////////////////////////////////////////////////////
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

        glm::vec2 wh_size; // width, height

        RectTransform(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, glm::vec2 pos, glm::vec2 size) 
            : top_left(tl), top_right(tr), bottom_left(bl), bottom_right(br) 
            {
                vert_tl = pos + (size * top_left);
                vert_tr = pos + (size * top_right);
                vert_bl = pos + (size * bottom_left);
                vert_br = pos + (size * bottom_right);

                wh_size = glm::vec2(vert_tr.x - vert_tl.x, vert_br.y - vert_tr.y);
            }
        void print_verts() {
            std::cout << "Top left: " << vert_tl.x << ", " << vert_tl.y << std::endl;
            std::cout << "Top right: " << vert_tr.x << ", " << vert_tr.y << std::endl;
            std::cout << "Bottom left: " << vert_bl.x << ", " << vert_bl.y << std::endl;
            std::cout << "Bottom right: " << vert_br.x << ", " << vert_br.y << std::endl;
        }
    };

    //////////////////////////////////////////////////////////////////
    // TextureStruct
    //////////////////////////////////////////////////////////////////
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

    //////////////////////////////////////////////////////////////////
    // Generic GUI Object
    //////////////////////////////////////////////////////////////////
    class GUIObject 
    {
        public:
            GUIObject(unsigned int id);
            ~GUIObject();

            RectTransform* GetRectTransform() { return m_rect; }
            void SetRectTransform(RectTransform* rect) {this->m_rect = rect;}
            bool MouseInBounds(glm::vec2 mousepos);

            void InitTexture(GUI_Shader* shader, Texture* texture);

            unsigned int GetID() { return m_id; }
        protected:
            unsigned int m_id;
            RectTransform* m_rect;
            TextureStruct* m_texStruct = NULL;

            virtual void Draw(Camera* cam);
    };

    //////////////////////////////////////////////////////////////////
    // Clickable GUI Object
    //////////////////////////////////////////////////////////////////
    class ClickableGUIObject : public GUIObject
    {
        public:
            ClickableGUIObject(unsigned int id);
            ~ClickableGUIObject();

        private:
    };

    //////////////////////////////////////////////////////////////////
    // Panel
    //////////////////////////////////////////////////////////////////
    class Panel : public GUIObject
    {
    public:
        Panel(unsigned int id); 
        ~Panel();

        Panel* GetParent() {return m_parent;}
        void SetParent(Panel* parent) {this->m_parent = parent;}

        int GetChildCount() {return m_childCount;}
        Panel** GetChildPanels() {return m_childrenPanels;}
        void AddChildPanel(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* child_panel);
        void RemoveChildPanel(Panel* child_panel);

        virtual void Draw(Camera* cam);
    protected:
        Panel* m_parent;

        int m_childCount = 0; 
        Panel* m_childrenPanels[MAX_CHILD_PANELS];
    };

    //////////////////////////////////////////////////////////////////
    // Button
    //////////////////////////////////////////////////////////////////
    class Button : public ClickableGUIObject
    {
        public:
            Button(unsigned int id);
            ~Button();
            
            void SetOnClick(void (*f)(void)) { m_onClick = f; }
            void Click() { m_onClick(); }

        private:
            Panel* m_parent;

            void (*m_onClick) (void);
    };

    //////////////////////////////////////////////////////////////////
    // Canvas
    //////////////////////////////////////////////////////////////////
    class Canvas
    {
    public:
        Canvas(Display* window);
        ~Canvas();

        Panel* NewPanel(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* parent = NULL);
        void DeletePanel(Panel* panel);
        Button* NewButton(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* parent);
        void DeleteButton(Button* button);
        void MouseClicked(glm::vec2 mousepos);
    private:
        // rect defining the size of the canvas
        int m_width, m_height;
        unsigned int m_unique_panelID = 1;
        unsigned int m_unique_buttonID = 1;

        int m_numPanels = 0;
        Panel* m_rootPanelList[MAX_PANELS_IN_CANVAS]; 

    };

    void RemoveFromPanelList(Panel* panel, Panel** panel_list, int* count);
}


#endif