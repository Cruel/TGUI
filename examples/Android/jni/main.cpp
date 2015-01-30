#include <TGUI/TGUI.hpp>

void setBackground(tgui::Gui& gui, sf::View view)
{
    gui.get("Landscape")->setSize(view.getSize().x, view.getSize().y);
    gui.get("Portrait")->setSize(view.getSize().x, view.getSize().y);

    if (view.getSize().x > view.getSize().y)
    {
        gui.get("Landscape")->show();
        gui.get("Portrait")->hide();
    }
    else
    {
        gui.get("Landscape")->hide();
        gui.get("Portrait")->show();
    }
}

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");
    tgui::Gui gui(window);

    gui.setGlobalFont("fonts/DejaVuSans.ttf");

    auto picLandscape = tgui::Picture::create("Background-Landscape.png");
    gui.add(picLandscape, "Landscape");

    auto picPortrait = tgui::Picture::create("Background-Portrait.png");
    gui.add(picPortrait, "Portrait");

    auto button = tgui::Button::create("widgets/Black.conf");

    button->setText("Quit");
    button->setPosition(50, 50);
    button->setSize(200, 50);
    button->connect("clicked", [&](){ window.close(); });
    gui.add(button);

    setBackground(gui, window.getDefaultView());

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::View view = window.getView();
                view.setSize(event.size.width, event.size.height);
                view.setCenter(event.size.width/2, event.size.height/2);
                window.setView(view);

                setBackground(gui, window.getDefaultView());
            }
            
            gui.handleEvent(event);
        }

        window.clear(sf::Color::Blue);
        gui.draw();
        window.display();
    }
}
