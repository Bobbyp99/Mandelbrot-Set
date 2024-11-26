#include "ComplexPlane.h"

//**********************************//

// --- Public Member Functions  --- //

//**********************************//


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = { pixelWidth, pixelHeight };
    m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
    m_plane_center = { 0,0 };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
    m_zoomCount = 0;
    m_State = State::CALCULATING;
    m_vArray.setPrimitiveType(sf::Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = { x_size, y_size };
    m_State = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = { x_size, y_size };
    m_State = CALCULATING;
}

void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_State = CALCULATING;
}

void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(sf::Text& text)
{
    std::ostringstream strm;
    strm << "Mandelbrot Set\n"
        << "Center: (" << m_plane_center.x << ',' << m_plane_center.y << ")\n"
        << "Cursor: (" << m_mouseLocation.x << ',' <<  m_mouseLocation.y << ")\n"
        << "Left-click to Zoom in\n"
        << "Right-click to Zoom out\n";
    text.setString(strm.str());

    m_State = DISPLAYING;
}

void ComplexPlane::updateRender(int currentPart, int maxParts)
{
    if (m_State == CALCULATING)
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

        //m_State = DISPLAYING;
    }
}


//**********************************//

// --- Private Member Functions --- //

//**********************************//


int ComplexPlane::countIterations(sf::Vector2f coord)
{
    std::complex<float> c (coord.x,coord.y);
    std::complex<float> z = c;
    int i = 0;

    while (abs(z) < 2.0 && i < MAX_ITER)
    {
        z = z * z + c;
        i++;
    }

    return i;
}

void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
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

sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
    // equations that translate the location on the pixelplane to the complex plane
    float x_coord = m_plane_size.x * ((mousePixel.x / static_cast<float>(m_pixel_size.x)) - 0.5);
    float y_coord = m_plane_size.y * (0.5 - (mousePixel.y / static_cast<float>(m_pixel_size.y)));

    // offset depending on the current center of the displaying screen
    x_coord += m_plane_center.x;
    y_coord += m_plane_center.y;

    return sf::Vector2f(x_coord,y_coord);
}


//**********************************//

// --- Multithreading Function  --- //

//**********************************//


void multithreadRender(ComplexPlane* cPlane, int currentPart, int maxParts)
{
    cPlane->updateRender(currentPart, maxParts);
}
