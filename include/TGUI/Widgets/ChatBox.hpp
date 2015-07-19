/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CHAT_BOX_HPP
#define TGUI_CHAT_BOX_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Scrollbar;
    class ChatBoxRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ChatBox : public Widget
    {
    public:

        typedef std::shared_ptr<ChatBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ChatBox> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox(const ChatBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBox& operator= (const ChatBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the chat box
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section            The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ChatBox::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "ChatBox");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another chat box
        ///
        /// @param chatBox  The other chat box
        ///
        /// @return The new chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ChatBox::Ptr copy(ChatBox::ConstPtr chatBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<ChatBoxRenderer> getRenderer() const
        {
            return std::static_pointer_cast<ChatBoxRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout2d& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the chat box.
        ///
        /// This size does not include the borders.
        ///
        /// @param size   The new size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the chat box.
        ///
        /// This is the size including the borders.
        ///
        /// @return Full size of the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color and character size will be used.
        ///
        /// @param text  Text that will be added to the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default text color will be used.
        ///
        /// @param text      Text that will be added to the chat box
        /// @param textSize  Size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// The default character size will be used.
        ///
        /// @param text   Text that will be added to the chat box
        /// @param color  Color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Add a new line of text to the chat box.
        ///
        /// The whole text passed to this function will be considered as one line for the getLine and removeLine functions,
        /// even if it is too long and gets split over multiple lines.
        ///
        /// @param text      Text that will be added to the chat box
        /// @param color     Color of the text
        /// @param textSize  Size of the text
        /// @param font      Font of the text (nullptr to use default font)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addLine(const sf::String& text, const sf::Color& color, unsigned int textSize, std::shared_ptr<sf::Font> font = nullptr);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the contents of the requested line.
        ///
        /// @param lineIndex  The index of the line of which you request the contents.
        ///                   The first line has index 0.
        ///
        /// @return The contents of the requested line.
        ///         An empty string will be returned when the index is too high.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getLine(std::size_t lineIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the requested line.
        ///
        /// @param lineIndex  The index of the line that should be removed.
        ///                   The first line has index 0.
        ///
        /// @return True if the line was removed, false if no such line existed (index too high).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeLine(std::size_t lineIndex);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all lines from the chat box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllLines();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of lines in the chat box.
        ///
        /// @return Number of lines in the chat box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getLineAmount()
        {
            return m_panel->getWidgets().size();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set a maximum amount of lines in the chat box.
        ///
        /// Only the last maxLines lines will be kept. Lines above those will be removed.
        /// Set to 0 to disable the line limit (default).
        ///
        /// @param maxLines  The maximum amount of lines that the chat box can contain.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLineLimit(std::size_t maxLines);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default font of the text.
        ///
        /// @return The currently used default font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<sf::Font> getTextFont()
        {
            return m_panel->getGlobalFont();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default character size of the text.
        ///
        /// @param size  The new default text size.
        ///              The minimum text size is 8.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default character size of the text.
        ///
        /// @return The currently used default text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_textSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default color of the text.
        ///
        /// @param color  The new default text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color)
        {
            m_textColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default color of the text.
        ///
        /// @return The currently used default text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const
        {
            return m_textColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the line spacing of all lines.
        ///
        /// By default, line spacing is chosen based on the font and character size. This also means that when mixing different
        /// text styles in ChatBox, lines can have different line spacings.
        /// By calling this function, all line spacings will be set to the value passed to this function.
        ///
        /// The line spacing should be equal or greater than the text size to avoid overlapping lines.
        ///
        /// @param lineSpacing  New line spacing for all lines
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLineSpacing(unsigned int lineSpacing);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the scrollbar from the chat box (if there is one).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Let the first lines start from the top or from the bottom of the chat box.
        ///
        /// Note that this only makes a difference when the lines don't fill the entire chat box.
        /// This does not change the order of the lines, new lines will always be below older lines.
        ///
        /// @param startFromTop  Let the first lines be placed at the top of the chat box, or remain at the bottom?
        ///
        /// By default the first lines will be placed at the bottom of the chat box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLinesStartFromTop(bool startFromTop);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const parent) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Retrieve the height of one of the lines, including the space below it that separates it from the next line.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getLineSpacing(const Label::Ptr& line);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculate the space used by all the labels.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateFullTextHeight();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the position of the labels.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateDisplayedText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the position and size of the panel and scrollbar.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateRendering();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<ChatBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        unsigned int m_lineSpacing = 0;
        unsigned int m_textSize = 18;
        sf::Color m_textColor = sf::Color::Black;

        std::size_t m_maxLines = 0;

        float m_fullTextHeight = 0;

        bool m_linesStartFromTop = false;

        // The panel containing the labels
        Panel::Ptr m_panel = Panel::create();

        // The scrollbar
        Scrollbar::Ptr m_scroll = Scrollbar::create();

        friend class ChatBoxRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ChatBoxRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param chatBox  The chat box that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChatBoxRenderer(ChatBox* chatBox) : m_chatBox{chatBox} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamically change a property of the renderer, without even knowing the type of the widget.
        ///
        /// This function should only be used when you don't know the type of the widget.
        /// Otherwise you can make a direct function call to make the wanted change.
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property
        /// @param rootPath  Path that should be placed in front of any resource filename
        ///
        /// @throw Exception when the property doesn't exist for this widget.
        /// @throw Exception when the value is invalid for this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value, const std::string& rootPath = getResourcePath());


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the border color that will be used inside the chat box.
        ///
        /// @param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor)
        {
            m_borderColor = borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color that will be used inside the chat box.
        ///
        /// @param backgroundColor  The new background color.
        ///
        /// Note that this color is ignored when you set a background image.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor)
        {
            m_backgroundColor = backgroundColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background image
        ///
        /// When this image is set, the background color property will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color property will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundImage(const std::string& filename,
                                const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the scrollbar of the chat box.
        ///
        /// @param scrollbarThemeFileFilename  Filename of the theme file.
        /// @param section  The section to look for inside the theme file.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbar(const std::string& scrollbarThemeFileFilename = "", const std::string& section = "Scrollbar");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the padding.
        ///
        /// @param padding  Size of the padding
        ///
        /// This padding will be scaled together with the background image.
        /// If there is no background image, or when 9-slice scaling is used, the padding will be exactly what you pass here.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPadding(const Padding& padding) override;
        using WidgetPadding::setPadding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ChatBoxRenderer(const ChatBoxRenderer&) = default;
        ChatBoxRenderer& operator=(const ChatBoxRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        ChatBox* m_chatBox;

        sf::Color m_borderColor = {0, 0, 0};
        sf::Color m_backgroundColor = {245, 245, 245};

        Texture m_backgroundTexture;

        friend class ChatBox;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
