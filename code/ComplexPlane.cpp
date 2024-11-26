#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = pixelHeight / static_cast<float> (pixelWidth);
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

void ComplexPlane::updateRender(int currentPart, int maxParts, bool changeState)
{
    if (m_State == State::CALCULATING)
    {
        // h loop
        int height = m_pixel_size.y;

        int part = height / maxParts;

        int heightUpper = part * currentPart;
        int heightLower = part * (currentPart - 1);

        if (currentPart == maxParts || heightUpper > height )
        {
            heightUpper = height;
        }

        // w loop
        int width = m_pixel_size.x;

        

        for (int h = heightLower; h < heightUpper; h++)
        {
            for (int w = 0; w < width; w++)
            {
                
                m_vArray[h * width + w].position = { (float)w, (float)h };

                sf::Vector2f location(mapPixelToCoords({ w,h }));
                int iterations = countIterations(location);
                sf::Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                m_vArray[h * width + w].color = { r, g, b };

            }
        }

        if (changeState)
        {
            m_State = State::DISPLAYING;
        }
    }
}

void ComplexPlane::zoomIn()
{
    ++m_zoomCount;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {x, y};
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    --m_zoomCount;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
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
    std::ostringstream strm;
    strm << "Mandelbrot Set\n"
    << "Center: (" << m_plane_center.x << ',' << m_plane_center.y << ")\n"
    << "Cursor: (" << m_mouseLocation.x << ',' <<  m_mouseLocation.y << ")\n"
    << "Left-click to Zoom in\n"
    << "Right-click to Zoom out\n";
    text.setString(strm.str());

    //this function should be called after rendering, as the option to remove its state was removed...
    //..so that it can work with being called multiple times through multithreading
    m_State = State::DISPLAYING;   
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<float> z(0, 0);
    complex<float> c(coord.x, coord.y);
    size_t iterations = 0;
    while(abs(z) < 2.0 && iterations < MAX_ITER)
    {
        z = z * z + c;
        ++iterations;
    }
    return iterations;    
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count < 64)
    {
        // needed the value pi for the following equation
        const double pi = 2 * acos(0.0);
    
        //set color on a gradient which plugs the number of iterations into a..
        //..parametric equation representing a 3D helix. Each dimension relates to..
        //..the red, green, and blue colors.
    
        r = static_cast<int>(127 * cos((2 * pi * count) / MAX_ITER - 1)); 
        g = static_cast<int>(127 * sin((2 * pi * count) / MAX_ITER - 1));
        b = static_cast<int>(255 - (255 * (count / (MAX_ITER - 1))));
    }
    else
    {
        //set color to black
        r = g = b = 0;
    }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    float real = (m_plane_size.x * ((mousePixel.x / static_cast<float>(m_pixel_size.x)) - 0.5)) +  m_plane_center.x;
    float imaginary =  (m_plane_size.y * (0.5 - (mousePixel.y / static_cast<float>(m_pixel_size.y)))) +  m_plane_center.x;
    return Vector2f{real, imaginary};
}

//Function needed for multithreading to work
void multithreadRender(ComplexPlane* cPlane, int currentPart, int maxParts)
{
    // passing false as to not change m_State to display,..
    // ..since multiple threads will be calling this funciton
    cPlane->updateRender(currentPart, maxParts, false);
}
