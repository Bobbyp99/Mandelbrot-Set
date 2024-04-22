#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
  VideoMode vm(VideoMode::getDesktopMode().width / 2,  VideoMode::getDesktopMode().length / 2);

  RenderWindow window(vm, "Mandelbrot Set", Style::Default);
}
