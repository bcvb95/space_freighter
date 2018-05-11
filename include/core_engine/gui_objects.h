#ifndef GUI_OBJECTS_H
#define GUI_OBJECTS_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <iostream>

#include <gui_constants.h>
#include <gui_exceptions.h>
#include <display.h>
#include <texture.h>
#include <shader.h>
<<<<<<< HEAD
#include <text_renderer.h>

=======
#include <functional>
>>>>>>> cf6155ec38b544df72b88ed05b217bdecbe37ddf

namespace GUI {

    //////////////////////////////////////////////////////////////////
    // RectTransform
    //////////////////////////////////////////////////////////////////
    struct RectTransform
    {
        glm::vec2 m_top_left;
        glm::vec2 m_top_right;
        glm::vec2 m_bottom_left;
        glm::vec2 m_bottom_right;

        glm::vec2 m_rel_tl;
        glm::vec2 m_rel_tr;
        glm::vec2 m_rel_bl;
        glm::vec2 m_rel_br;

        glm::vec2 wh_size; // width, height

        RectTransform(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, glm::vec2 parent_pos, glm::vec2 parent_size) 
        : m_rel_tl(tl), m_rel_tr(tr), m_rel_bl(bl), m_rel_br(br) {
            m_top_left = parent_pos + (parent_size * m_rel_tl);
            m_top_right = parent_pos + (parent_size * m_rel_tr);
            m_bottom_left = parent_pos + (parent_size * m_rel_bl);
            m_bottom_right = parent_pos + (parent_size * m_rel_br);

            wh_size = glm::vec2(m_top_right.x - m_top_left.x, m_bottom_right.y - m_top_right.y);
        }
        RectTransform(glm::vec2 rel_tl, glm::vec2 size, glm::vec2 parent_pos, glm::vec2 parent_size) 
        : wh_size(size) {
            m_top_left = parent_pos + (parent_size * rel_tl);
            m_top_right = m_top_left + glm::vec2(wh_size.x, 0);
            m_bottom_left = m_top_left + glm::vec2(0, wh_size.y);
            m_bottom_right = m_top_left + glm::vec2(wh_size.x, wh_size.y);

            m_rel_tl = (m_top_left-parent_pos) / parent_size;
            m_rel_tr = (m_top_right-parent_pos) / parent_size;
            m_rel_bl = (m_bottom_left-parent_pos) / parent_size;
            m_rel_br = (m_bottom_right-parent_pos) / parent_size;
        }
        void print_verts() {
            std::cout << "Top left: " << m_top_left.x << ", " << m_top_left.y << std::endl;
            std::cout << "Top right: " << m_top_right.x << ", " << m_top_right.y << std::endl;
            std::cout << "Bottom left: " << m_bottom_left.x << ", " << m_bottom_left.y << std::endl;
            std::cout << "Bottom right: " << m_bottom_right.x << ", " << m_bottom_right.y << std::endl;
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
    // GUI Object Type Enum
    //////////////////////////////////////////////////////////////////
    enum GUIObjectType {
        PANEL=0, BUTTON=1, LABEL=2, NONE=3
    };

    //////////////////////////////////////////////////////////////////
    // Generic GUI Object
    //////////////////////////////////////////////////////////////////
    class GUIObject 
    {
        public:
            GUIObject(unsigned int id);
            ~GUIObject();

            virtual GUIObjectType GetObjectType() { return NONE; }

            RectTransform* GetRectTransform() { return m_rect; }
            void SetRectTransform(RectTransform* rect) {this->m_rect = rect;}
            bool MouseInBounds(glm::vec2 mousepos, bool clicked);

            void InitTexture(GUI_Shader* shader, Texture* texture);
            virtual GUIObject* GetParent() {return m_parent;}
            virtual GUIObject* SetParent(GUIObject* parent) {this->m_parent = parent;}

            unsigned int GetID() { return m_id; }
            bool IsDisabled () { return m_disabled; }
            void Disable() { m_disabled = true; }
            void Enable() { m_disabled = false; }
        protected:
            unsigned int m_id;
            bool m_disabled = false;
            GUIObject* m_parent = NULL;
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

            virtual GUIObjectType GetObjectType() { return PANEL; }

            virtual Panel* GetParent() { return static_cast<Panel*>(m_parent); }
            virtual Panel* SetParent(Panel* parent) { m_parent = parent; }

            int GetChildCount() {return m_childCount;}
            GUIObject** GetChildren() {return m_children;}
            void AddChild(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, GUIObject* child_object);
<<<<<<< HEAD
            void AddChild(GUIObject* child_object);
=======
            void AddChild(glm::vec2 rel_pos, glm::vec2 wh_size, GUIObject* child_object);
>>>>>>> cf6155ec38b544df72b88ed05b217bdecbe37ddf
            void RemoveChild(GUIObject* child_object);
            void SwapChildrenOrder(int idx1, int idx2);

            virtual void Draw(Camera* cam);
        protected:
            int m_childCount = 0; 
            GUIObject* m_children[MAX_CHILD_PANELS];
    };

    //////////////////////////////////////////////////////////////////
    // Button
    //////////////////////////////////////////////////////////////////
    class Button : public ClickableGUIObject
    {
        public:
            Button(unsigned int id);
            ~Button();

            virtual GUIObjectType GetObjectType() { return BUTTON; }
            
            //void SetOnClick(void (*f)(void*), void* param = NULL) { m_onClick = f; m_param = param; }
            void SetOnClick(std::function<void(void*)> f, void* param = NULL) { m_onClick = f; m_param = param; } 

            void Click() { 
                //m_onClick(m_param);
                if (m_onClick == NULL) {
                    throw NoFunctionOnButtonException(m_id);
                }
                m_onClick(m_param);  
            }
            virtual Panel* GetParent() { return static_cast<Panel*>(m_parent); }

            virtual void Draw(Camera* cam);

        private:
            Panel* m_parent;

            //void (*m_onClick) (void*);
            std::function<void(void*)> m_onClick = NULL;
            void* m_param;
    };

    class Label : public GUIObject
    {
    public:
        Label(unsigned int id, TextRenderer* text_render);
        ~Label();
        virtual GUIObjectType GetObjectType() { return LABEL; }

        void ConfigText(std::string text, FONTSIZE fs, glm::vec2 pos);
        virtual void Draw(Camera* cam);

        virtual Panel* GetParent() {return static_cast<Panel*>(m_parent);}
        virtual void SetParent(Panel* panel) {this->m_parent = panel;}


    private:
        TextRenderer* m_textRender;

        char m_text[255];
        FONTSIZE m_fontSize;
        glm::vec2 m_textSize;

        Panel* m_parent;
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
        Panel* NewPanel(glm::vec2 rel_pos, glm::vec2 wh_size, Panel* parent = NULL);
        void DeletePanel(Panel* panel);
        Button* NewButton(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* parent);
        Button* NewButton(glm::vec2 rel_pos, glm::vec2 wh_size, Panel* parent);
        void DeleteButton(Button* button);
        Label* NewLabel(glm::vec2 pos, Panel* parent, TextRenderer* text_render,std::string text, FONTSIZE font_size);        
        void DeleteLabel(Label* label);

        void MouseInBounds(glm::vec2 mousepos, bool clicked);
    private:
        // rect defining the size of the canvas
        int m_width, m_height;
        unsigned int m_unique_panelID = 1;
        unsigned int m_unique_buttonID = 1;
        unsigned int m_unique_labelID = 1;

        int m_numPanels = 0;
        Panel* m_rootPanelList[MAX_PANELS_IN_CANVAS]; 
    };

    void RemoveFromObjectList(GUIObject* object, GUIObject** object_list, int* count);
}


#endif