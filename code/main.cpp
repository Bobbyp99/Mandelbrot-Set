// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <SFML/Window/VideoMode.hpp>

using namespace std;
using namespace sf;

int main()
{
	VideoMode vm(VideoMode::getDesktopMode().width / 2,  VideoMode::getDesktopMode().height / 2);
	
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);
	
	//complex<double> z(0, 0);
	
	//Handling Font and Text
	Text text;
	Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		throw("Font failed to load");
	}
	text.setFont(font);
	text.setCharacterSize(20);
	text.SetColor(Color::Yellow);
	text.setOutlineThickness(1);
	text.setStyle(sf::Text::Regular);
	text.setString(" ");

	  // Begin the main loop
	while (window.isOpen())
	{
	    //Handle input
	    sf::Event event;
	
	    // Poll Windows queue events
	    while (window.pollEvent(event))
	    {
		// Handle event to close the window
		if (event.type == sf::Event::Closed)
		    window.close();
		// Handle event if mouse button is pressed
		if (event.type == sf::Event::MouseButtonPressed)
		{
		    // Left click (zoom out and set center to where the mouse clicked)
		    if (event.mouseButton.button == sf::Mouse::Left)
		    {
			cPlane.setCenter({event.mouseButton.x, event.mouseButton.y});
			cPlane.zoomIn();
			
		    }
		    // Right click (zoom out and set center to where the mouse clicked)
		    else if (event.mouseButton.button == sf::Mouse::Right)
		    {
			cPlane.setCenter({ event.mouseButton.x, event.mouseButton.y });
			cPlane.zoomOut();
			
		    }
		}
		// Handle event if mouse as moved, update mouse location
		if (event.type == sf::Event::MouseMoved)
		{
		    cPlane.setMouseLocation({ event.mouseMove.x,event.mouseMove.y });
		}
		// Check if Esc is pressed to close the window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
		    window.close();
		}
	    }
	
	
	    // Update (multithreading for updateRender)
	    std::thread th1(multithreadRender, &cPlane, 1, 4);
	    std::thread th2(multithreadRender, &cPlane, 2, 4);
	    std::thread th3(multithreadRender, &cPlane, 3, 4);
	    std::thread th4(multithreadRender, &cPlane, 4, 4);
	    th1.join();
	    th2.join();
	    th3.join();
	    th4.join();
	    
	    cPlane.loadText(text);
	
	    // Draw
	    window.clear();
	    window.draw(cPlane);
	    window.draw(text);
	    window.display();
	}
	
	return 0;
}
