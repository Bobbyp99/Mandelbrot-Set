// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <SFML/Window/VideoMode.hpp>

using namespace std;

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
  //text.setString(" ");
  
}
