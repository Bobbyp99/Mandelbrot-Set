#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <complex>
#include <iostream>
#include <thread>
#include <vector>

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0,
			BASE_HEIGHT = 4.0,
			BASE_ZOOM = 0.5;

// State - depcits when the complex plane should be calcuated
//-----------------------------------------------------------------------------------
//  CALCULATING State - since calculating the complex plane display is CPU intensive,
//					| this will only be set as the current state once per user click.
//	DISPLAYING State - this state should always be active whenever calculating is not
//					| needed, therefore avoiding intense CPU usage
//-----------------------------------------------------------------------------------
enum State {CALCULATING, DISPLAYING};

class ComplexPlane : public sf::Drawable
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void zoomIn();
	void zoomOut();

	void setCenter(sf::Vector2i mousePixel);
	void setMouseLocation(sf::Vector2i mousePixel);

	void loadText(sf::Text& text);
	void updateRender(int currentPart = 1, int maxParts = 1);

private:

	int countIterations(sf::Vector2f coord);
	void iterationsToRGB(size_t count,sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);
	sf::Vector2f mapPixelToCoords(sf::Vector2i mousePixel);

	// image data
	sf::VertexArray m_vArray;

	// wheter to calculate the complex plane or display it
	State m_State;

	// how many pixels is the width and height of the window
	sf::Vector2i m_pixel_size;
	
	// where the mouse currently is located on the complex plane
	sf::Vector2f m_mouseLocation;
	
	// current center on the complex plane
	sf::Vector2f m_plane_center;

	// the ranges of the complex plane dependent on the windows resolution
	// Width always is = BASE_WIDTH
	// Height changes depending on = BASE_HEIGHT * m_aspectRatio
	sf::Vector2f m_plane_size;


	int m_zoomCount;
	
	
	float m_aspectRatio;
};

void multithreadRender(ComplexPlane* cPlane, int currentPart = 1, int maxParts = 1);
