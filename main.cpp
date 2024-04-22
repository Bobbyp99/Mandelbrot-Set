#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Window/VideoMode.hpp>

using namespace std;

int main()
{
  VideoMode vm(VideoMode::getDesktopMode().width / 2,  VideoMode::getDesktopMode().height / 2);

  RenderWindow window(vm, "Mandelbrot Set", Style::Default);
}
