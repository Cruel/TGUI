/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2013 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Widgets.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Widget::Widget() :
    m_Enabled        (true),
    m_Visible        (true),
    m_Loaded         (false),
    m_WidgetPhase    (0),
    m_Parent         (nullptr),
    m_Opacity        (255),
    m_MouseHover     (false),
    m_MouseDown      (false),
    m_Focused        (false),
    m_AllowFocus     (false),
    m_AnimatedWidget (false),
    m_DraggableWidget(false),
    m_ContainerWidget(false),
    m_Callback       ()
    {
        m_Callback.widget = this;
        m_Callback.widgetType = Type_Unknown;
        m_Callback.id = 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Widget::Widget(const Widget& copy) :
    sf::Drawable     (copy),
    Transformable    (copy),
    CallbackManager  (copy),
    m_Enabled        (copy.m_Enabled),
    m_Visible        (copy.m_Visible),
    m_Loaded         (copy.m_Loaded),
    m_WidgetPhase    (copy.m_WidgetPhase),
    m_Parent         (copy.m_Parent),
    m_Opacity        (copy.m_Opacity),
    m_MouseHover     (false),
    m_MouseDown      (false),
    m_Focused        (false),
    m_AllowFocus     (copy.m_AllowFocus),
    m_AnimatedWidget (copy.m_AnimatedWidget),
    m_DraggableWidget(copy.m_DraggableWidget),
    m_ContainerWidget(copy.m_ContainerWidget),
    m_Callback       (copy.m_Callback)
    {
        m_Callback.widget = this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Widget::~Widget()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Widget& Widget::operator= (const Widget& right)
    {
        // Make sure it is not the same widget
        if (this != &right)
        {
            this->sf::Drawable::operator=(right);
            this->Transformable::operator=(right);
            this->CallbackManager::operator=(right);

            m_Enabled             = right.m_Enabled;
            m_Visible             = right.m_Visible;
            m_Loaded              = right.m_Loaded;
            m_WidgetPhase         = right.m_WidgetPhase;
            m_Parent              = right.m_Parent;
            m_Opacity             = right.m_Opacity;
            m_MouseHover          = false;
            m_MouseDown           = false;
            m_Focused             = false;
            m_AllowFocus          = right.m_AllowFocus;
            m_AnimatedWidget      = right.m_AnimatedWidget;
            m_DraggableWidget     = right.m_DraggableWidget;
            m_ContainerWidget     = right.m_ContainerWidget;
            m_Callback            = Callback();
            m_Callback.widget     = this;
            m_Callback.widgetType = right.m_Callback.widgetType;
            m_Callback.id         = right.m_Callback.id;
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::show()
    {
        m_Visible = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::hide()
    {
        m_Visible = false;

        // If the widget is focused then it must be unfocused
        m_Parent->unfocusWidget(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Widget::isVisible() const
    {
        return m_Visible;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::enable()
    {
        m_Enabled = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::disable()
    {
        m_Enabled = false;

        // Change the mouse button state.
        m_MouseHover = false;
        m_MouseDown = false;

        // If the widget is focused then it must be unfocused
        m_Parent->unfocusWidget(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Widget::isEnabled() const
    {
        return m_Enabled;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Widget::isDisabled() const
    {
        return !m_Enabled;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Widget::isLoaded() const
    {
        return m_Loaded;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::extractPhases(std::string phases)
    {
        bool nextPhaseFound = true;
        std::string::size_type commaPos;

        while (nextPhaseFound)
        {
            // Search for the next comma
            commaPos = phases.find(',', 0);

            // Check if there was a comma
            if (commaPos != std::string::npos)
            {
                // Get the next phase
                std::string SinglePhase = phases.substr(0, commaPos);

                // Store the phase
                if (SinglePhase.compare("hover") == 0)
                    m_WidgetPhase |= WidgetPhase_Hover;
                else if (SinglePhase.compare("focus") == 0)
                    m_WidgetPhase |= WidgetPhase_Focused;
                else if (SinglePhase.compare("down") == 0)
                    m_WidgetPhase |= WidgetPhase_MouseDown;
                else if (SinglePhase.compare("selected") == 0)
                    m_WidgetPhase |= WidgetPhase_Selected;

                // Remove this phase from the string
                phases.erase(0, commaPos+1);
            }
            else // There was no comma
            {
                nextPhaseFound = false;

                // Store the phase
                if (phases.compare("hover") == 0)
                    m_WidgetPhase |= WidgetPhase_Hover;
                else if (phases.compare("focus") == 0)
                    m_WidgetPhase |= WidgetPhase_Focused;
                else if (phases.compare("down") == 0)
                    m_WidgetPhase |= WidgetPhase_MouseDown;
                else if (phases.compare("selected") == 0)
                    m_WidgetPhase |= WidgetPhase_Selected;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::focus()
    {
        m_Parent->focusWidget(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::unfocus()
    {
        if (m_Focused)
            m_Parent->unfocusAllWidgets();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::focusNextWidget()
    {
        m_Parent->unfocusWidget(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Widget::isFocused() const
    {
        return m_Focused;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WidgetTypes Widget::getWidgetType() const
    {
        return m_Callback.widgetType;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Container* Widget::getParent() const
    {
        return m_Parent;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::setTransparency(unsigned char transparency)
    {
        m_Opacity = transparency;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned char Widget::getTransparency() const
    {
        return m_Opacity;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::moveToFront()
    {
        m_Parent->moveWidgetToFront(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::moveToBack()
    {
        m_Parent->moveWidgetToBack(this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::setCallbackId(unsigned int callbackId)
    {
        m_Callback.id = callbackId;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Widget::getCallbackId()
    {
        return m_Callback.id;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::update()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::addCallback()
    {
        // Get the list of callback functions
        std::list<CallbackFunction>& functions = m_CallbackFunctions[m_Callback.trigger];

        // Loop through all callback functions
        for (std::list<CallbackFunction>::const_iterator it = functions.begin(); it != functions.end(); ++it)
        {
            // Pass the callback to the correct place
            if (it->simpleFunction != nullptr)
                it->simpleFunction();
            else if (it->extendedFunction != nullptr)
                it->extendedFunction(m_Callback);
            else
                m_Parent->addChildCallback(m_Callback);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseEnteredWidget()
    {
        if (m_CallbackFunctions[MouseEntered].empty() == false)
        {
            m_Callback.trigger = MouseEntered;
            addCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseLeftWidget()
    {
        if (m_CallbackFunctions[MouseLeft].empty() == false)
        {
            m_Callback.trigger = MouseLeft;
            addCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::leftMousePressed(float, float)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::leftMouseReleased(float, float)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseMoved(float, float)
    {
        if (m_MouseHover == false)
            mouseEnteredWidget();

        m_MouseHover = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::keyPressed(sf::Keyboard::Key)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::textEntered(sf::Uint32)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseWheelMoved(int)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::widgetFocused()
    {
        if (m_CallbackFunctions[Focused].empty() == false)
        {
            m_Callback.trigger = Focused;
            addCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::widgetUnfocused()
    {
        if (m_CallbackFunctions[Unfocused].empty() == false)
        {
            m_Callback.trigger = Unfocused;
            addCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseNotOnWidget()
    {
        if (m_MouseHover == true)
            mouseLeftWidget();

        m_MouseHover = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::mouseNoLongerDown()
    {
        m_MouseDown = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::initialize(tgui::Container *const parent)
    {
        m_Parent = parent;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WidgetBorders::WidgetBorders() :
    m_LeftBorder  (0),
    m_TopBorder   (0),
    m_RightBorder (0),
    m_BottomBorder(0)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector4u WidgetBorders::getBorders() const
    {
        return Vector4u(m_LeftBorder, m_TopBorder, m_RightBorder, m_BottomBorder);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////