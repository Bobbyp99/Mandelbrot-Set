// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <SFML/Window/VideoMode.hpp>

int main()
{
  VideoMode vm(VideoMode::getDesktopMode().width / 2,  VideoMode::getDesktopMode().height / 2);

  RenderWindow window(vm, "Mandelbrot Set", Style::Default);
}
