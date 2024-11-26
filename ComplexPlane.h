#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <complex>
#include <iostream>
#include <thread>

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State { CALCULATING, DISPLAYING }

class ComplexPlane
{
    public:
        ComplexPlane(int pixelWidth, int pixelHeight);
        void draw(RenderTarget& target, RenderStates states) const override;
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2i mousePixel);
        void setMouseLocation(Vector2i mousePixel);
        void loadText(Text& text);

        // added parameters so that the plane can be rendered in parts
        // its state can be prevented from changing to display after running,...
        // ..so the function can be called multiple times (multithreading in mind)
	    void updateRender(int currentPart = 1, int maxParts = 1, bool changeState = true);

    private:
        VertexArray m_vArray;
        State m_state;
        Vector2f m_mouseLocation;
        Vector2i m_pixel_size;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;
        size_t countIterations(Vector2f coord);
        void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
        Vector2f mapPixelsToCoords(Vector2i mousePixels);
}

//Function needed for multithreading
void multithreadRender(ComplexPlane* cPlane, int currentPart = 1, int maxParts = 1);
