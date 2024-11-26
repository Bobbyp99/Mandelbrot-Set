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
    if(m_State == CALCULATING)
    {
        for(int i = 0; i < pixel.Height; ++i)
        {
            for(int j = 0; i < pixel.Width; ++j)  
            {
                m_vArray[j + i * pixelWidth].position = { (float)j,(float)i };
                Vector2f pixelCoord = mapPixelsToCoords(Vector2i(j, i));
                countIterations(pixelCoord);
                Uint8 r, g, b;
                iterationsToRGB(r, g, b);
                m_vArray[j + i * pixelWidth].color = { r,g,b };
            }
        }
        m_State = State::DISPLAYING;
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
    Vector2f pixelCoord = mapPixelToCoords(mousePixel);
    m_plane_center = pixelCoord;
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    Vector2f pixelCoord = mapPixelToCoords(mousePixel);
    m_mouseLocation = pixelCoord;
}

void ComplexPlane::loadText(Text& text)
{
    stringstring ss;
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<float> z(0, 0);
    complex<float> c(coord.x, coord.y);
    size_t iterations = 0;
    while(abs(z) < 2.0 && iterations < MAX_ITERjhh)
    {
        z = z * z + c;
        ++iterations;
    }
    return iterations;    
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITERS)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    //else if
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    float real = ((mousePixel.x) / static_cast<float>(m_pixel_size.x)) /  (m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0));
    float imaginary = ((mousePixel.y) / static_cast<float>(m_pixel_size.y)) / (m_plane_size.y + (m_plan_center.y - m_plane_size.y / 2.0));
    return Vector2f{real, imaginary);
}




