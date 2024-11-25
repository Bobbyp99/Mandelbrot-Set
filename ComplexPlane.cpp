#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = pixelHeight / static_cast<float> pixelWidth;
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_zoomCount = 0;
    m_State = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void complexPlane::updateRender()
{
    if(m_State == State::CALCULATING)
    {
        for(int i = 0; i < pixel.Height; ++i)
        {
            for(int j = 0; i < pixel.Width; ++j)  
            {
                
            }
        }
    }
}

void ComplexPlane::zoomIn()
{
    ++m_zoomCount;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {x, y};
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    --m_zoomCount;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {x, y};
    m_State = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    
}

void ComplexPlane::loadText(Text& text)
{
    //create the upperleft hub
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    
}




