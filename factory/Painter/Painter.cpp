// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/CCanvas.h"
#include "../libpainter/CDesigner.h"
#include "../libpainter/CPainter.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/CModernCanvas.h"

int main()
{
	std::cout << "Enter <info> to get valid input" << std::endl;
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	/*sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Canvas", sf::Style::Default, settings);

	CModernCanvas canvas(window);
	CPainter painter;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		painter.DrawPicture(pictureDraft, canvas);

		window.display();
	}*/

	return 0;
}
