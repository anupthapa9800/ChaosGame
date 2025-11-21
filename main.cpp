// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib> // Required for std::rand() and std::srand()
#include <ctime>   // Required for std::time()

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

// --- Function to update the instruction text based on the current state ---
void updateInstructions(Text& text, const vector<Vector2f>& vertices, const vector<Vector2f>& points)
{
    stringstream ss;
    if (vertices.size() < 3)
    {
        ss << "Click on the screen to set Vertex " << vertices.size() + 1 << "/3.";
        ss << "\n(Current Vertices: " << vertices.size() << ")";
    }
    else if (points.empty())
    {
        ss << "Vertices set! Click on a FOURTH point to start the Chaos Game.";
    }
    else
    {
        ss << "Chaos Game running! Generating Sierpinski Triangle...";
        ss << "\nTotal points: " << points.size();
        ss << "\nPress ESC to quit.";
    }
    text.setString(ss.str());
}


int main()
{
    // Partner's name: [INSERT YOUR PARTNER'S NAME HERE]

    // --- Initialize random seed for the Chaos Game ---
    srand(time(0));

    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    // --- Font and Text Setup (Requirement) ---
    Font font;
    // NOTE: You MUST have a font file (e.g., arial.ttf) in the executable's directory.
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error: Failed to load font file. Ensure 'arial.ttf' is in the directory." << endl;
        // Proceeding without text, but this is required for full credit.
    }

    Text instruction_text;
    instruction_text.setFont(font);
    instruction_text.setCharacterSize(24);
    instruction_text.setFillColor(Color::White);
    instruction_text.setPosition(10, 10);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Set the initial instructions
    updateInstructions(instruction_text, vertices, points);

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
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Vector2f click_coord = Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (vertices.size() < 3)
                    {
                        // Store the coordinates for the first 3 mouse clicks as the vertices
                        vertices.push_back(click_coord);
                        updateInstructions(instruction_text, vertices, points);
                    }
                    else if (points.size() == 0)
                    {
                        // Assign the user's fourth mouse click coordinate to the starting coordinate
                        points.push_back(click_coord);
                        updateInstructions(instruction_text, vertices, points);
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
        Update (Chaos Game Logic)
        ****************************************
        */
        if (points.size() > 0 && vertices.size() == 3)
        {
            // --- Generate multiple points each frame (e.g., 100) ---
            const int points_per_frame = 100;

            for (int j = 0; j < points_per_frame; ++j)
            {
                // 1. Select a random vertex (0, 1, or 2)
                int rand_index = rand() % 3;
                Vector2f random_vertex = vertices[rand_index];

                // 2. Get the last point generated (the current point)
                Vector2f current_point = points.back();

                // 3. Calculate the midpoint (r = 0.5 for the Sierpinski Triangle)
                Vector2f new_point;
                new_point.x = (current_point.x + random_vertex.x) / 2.0f;
                new_point.y = (current_point.y + random_vertex.y) / 2.0f;

                // 4. Push back the newly generated coordinate.
                points.push_back(new_point);
            }
            // Update the instructions to show the growing count of points
            updateInstructions(instruction_text, vertices, points);
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // 1. Draw the vertices (Blue)
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            // Center the rectangle on the click coordinate
            rect.setPosition(vertices[i].x - 5, vertices[i].y - 5);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // 2. Draw generated points (Red) (Requirement)
        for (const auto& point : points)
        {
            // Use a 2x2 RectangleShape for visibility (1x1 is also common for high detail)
            RectangleShape point_shape(Vector2f(2, 2));
            point_shape.setPosition(point.x - 1, point.y - 1); // Center the point
            point_shape.setFillColor(Color::Red);
            window.draw(point_shape);
        }

        // 3. Draw the instructions text
        window.draw(instruction_text);

        window.display();
    }
    return 0;
}