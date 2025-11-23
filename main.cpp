// Member: Anup Jung Thapa and William Li
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	// Seed random once
	srand(static_cast<unsigned>(time(nullptr)));

	Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error loading font\n";
	}

	Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::White);
	instructions.setPosition(10.f, 10.f);
	instructions.setString("Click 3 points to set triangle vertices.");

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					cout << "the left button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						instructions.setString("Fractal running..."); // change instructions
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0 && vertices.size() == 3)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			const int POINTS_PER_FRAME = 100; // more = faster fractal

			for (int i = 0; i < POINTS_PER_FRAME; i++)
			{
				// last generated point
				Vector2f lastPoint = points.back();

				// choose a random vertex
				int idx = rand() % 3;              // 0, 1, or 2
				Vector2f v = vertices[idx];

				// midpoint between lastPoint and chosen vertex
				Vector2f mid(
					(lastPoint.x + v.x) / 2.0f,
					(lastPoint.y + v.y) / 2.0f
				);

				// store new point
				points.push_back(mid);
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		///TODO:  Draw points

		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape dot(Vector2f(2, 2));
			dot.setPosition(points[i]);
			dot.setFillColor(Color::White);
			window.draw(dot);
		}

		// Draw instructions text
		window.draw(instructions);

		window.display();
	}
}