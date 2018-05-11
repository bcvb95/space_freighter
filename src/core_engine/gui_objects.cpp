#include <gui_objects.h>

namespace GUI {

    //////////////////////////////////////////////////////////////////
    // Generic GUI Object
    //////////////////////////////////////////////////////////////////
    GUIObject::GUIObject(unsigned int id) {
        m_id = id;
    }
    
    GUIObject::~GUIObject() {}

    void GUIObject::InitTexture(GUI_Shader* shader, Texture* texture)
    {
        m_texStruct = new TextureStruct(shader, texture);
    }

    void GUIObject::Draw(Camera* cam) {
        m_texStruct->shader->Bind();
        m_texStruct->shader->Update(cam);

        glBindVertexArray(m_texStruct->vertexArrayObject);

        GLfloat vertices[6][4] = {
            { m_rect->vert_bl.x , m_rect->vert_bl.y,  0.0, 1.0 },
            { m_rect->vert_tr.x, m_rect->vert_tr.y ,  1.0, 0.0 },
            { m_rect->vert_tl.x, m_rect->vert_tl.y ,  0.0, 0.0 },

            { m_rect->vert_bl.x, m_rect->vert_bl.y,   0.0, 1.0 },
            { m_rect->vert_br.x, m_rect->vert_br.y,   1.0, 1.0 },
            { m_rect->vert_tr.x, m_rect->vert_tr.y,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        m_texStruct->texture->Bind();

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_texStruct->vertexArrayBuffer);
        glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool GUIObject::MouseInBounds(glm::vec2 mousepos, bool clicked) {
        if (m_rect->vert_tl.x < mousepos.x && m_rect->vert_tr.x > mousepos.x &&
            m_rect->vert_tl.y < mousepos.y && m_rect->vert_bl.y > mousepos.y) 
        {
            std::cout << "Clicked object with ID: " << m_id << std::endl;
            GUIObjectType object_type = this->GetObjectType(); 
            if (object_type == PANEL) {
                Panel* panel = static_cast<Panel*>(this);
                GUIObject** children = panel->GetChildren();
                for (int i = 0; i < panel->GetChildCount(); i++) { 
                    children[i]->MouseInBounds(mousepos, clicked);
                }
            } else if (object_type == BUTTON) {
                if (clicked) {
                    Button* button = static_cast<Button*>(this);
                    button->Click();
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////
    // Clickable GUI Object
    //////////////////////////////////////////////////////////////////
    ClickableGUIObject::ClickableGUIObject(unsigned int id) : GUIObject(id) {
    }
    
    ClickableGUIObject::~ClickableGUIObject() {}

    //////////////////////////////////////////////////////////////////
    // Panel
    //////////////////////////////////////////////////////////////////
    Panel::Panel(unsigned int id) : GUIObject(id)
    {
    }

    Panel::~Panel()
    {
        for (int i = 0; i < m_childCount; i++) {
            delete m_children[i];
        }

    }

    void Panel::AddChild(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, GUIObject* new_object) 
    {
        new_object->SetParent(this);
        m_children[m_childCount] = new_object;
        m_childCount++;
        new_object->SetRectTransform(new RectTransform(tl, tr, bl, br, this->m_rect->vert_tl, this->m_rect->wh_size));   
    } 

    void Panel::RemoveChild(GUIObject* child_object)
    {
        RemoveFromObjectList(child_object, m_children, &m_childCount);
    }

    void Panel::Draw(Camera* cam)
    {
        GUIObject::Draw(cam); // Base class draw method
        
        for (int i = 0; i < m_childCount; i++) 
        {
            switch (m_children[i]->GetObjectType()) {
                case PANEL:
                    static_cast<Panel*>(m_children[i])->Draw(cam);
                    break;
                case BUTTON:
                    static_cast<Button*>(m_children[i])->Draw(cam);
                    break;
                default:
                    std::cout << "PANEL: Could not determine child object type." << std::endl;
                    break;
            }
        }
    }

    void RemoveFromObjectList(GUIObject* object, GUIObject** object_list, int* count)
    {
        bool found = false;
        int i;
        for (i = 0; i < *count ; i++) {
            if (object_list[i] == object) {
               found = true;
               break; 
            }
        }

        if (!found) {
            if (object->GetParent() == NULL) {
                std::cout << "CANVAS ERROR: ";  
            } else {
                std::cout << "OBJECT ERROR: ";
            }
            std::cout << "can't find child in children list" << std::endl;
            return;
        }
        for (int j = i; j < (*count)-1; j++) {
            object_list[j] = object_list[j+1];
        }
        *count -= 1;
    }

    //////////////////////////////////////////////////////////////////
    // Button
    //////////////////////////////////////////////////////////////////
    Button::Button(unsigned int id) : ClickableGUIObject(id) {
    }

    Button::~Button() { }  

    void Button::Draw(Camera* cam) {
        GUIObject::Draw(cam);
    }

    //////////////////////////////////////////////////////////////////
    // Canvas 
    //////////////////////////////////////////////////////////////////
    Canvas::Canvas(Display* window) 
    {
        m_width = window->GetWindowWidth();
        m_height = window->GetWindowHeight();
    }

    Canvas::~Canvas() 
    {
        for (int i = 0; i < m_numPanels; i++) {
            delete m_rootPanelList[i];
        }
    }

    Panel* Canvas::NewPanel(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* parent) 
    {   
        Panel* new_panel = new Panel(m_unique_panelID);
        m_unique_panelID++;

        if (parent == NULL) {
            new_panel->SetRectTransform(new RectTransform(tl, tr, bl, br, glm::vec2(0), glm::vec2(m_width, m_height)));
            m_rootPanelList[m_numPanels] = new_panel;
            m_numPanels++;
        }
        else {
           parent->AddChild(tl, tr, bl, br, new_panel); 
        }

        return new_panel;
    }     

    void Canvas::DeletePanel(Panel* panel) 
    {
        if (panel->GetChildCount() > 0) {
            std::cout << "CANVAS ERROR: cannot delete panel with children" << std::endl;
            return;
        }

        Panel* parent_panel = panel->GetParent(); 
        if (parent_panel != NULL) {
            parent_panel->RemoveChild(panel);
        }
        else {
            RemoveFromObjectList(panel, (GUIObject**)m_rootPanelList, &m_numPanels);
        }
        delete panel;
    }

    void Canvas::MouseInBounds(glm::vec2 mousepos, bool clicked) {
        for (int i=0; i < m_numPanels; i++) {
            m_rootPanelList[i]->MouseInBounds(mousepos, clicked);
        }
    }

    Button* Canvas::NewButton(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br, Panel* parent) {
        Button* new_button = new Button(m_unique_buttonID);
        parent->AddChild(tl, tr, bl, br, new_button);
        m_unique_buttonID++;
        return new_button;
    }
 
}
