## Synopsis

studious-engine is a small framework designed to make it easy for game makers to create a game in a small time frame.

## Code Example

**TODO**

Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

**Creating your graphics context**

The header need to have access to the window and render functionality is in Game.h.

    #include <Game.h>

Initialising the Game:

    SE::Game::init();

This will create your OpenGL window context and your game renderer. You can access the window height and window width by calling:

    SE::Game::m_window->getHeight();
    SE::Game::m_window->getWidth();

**Using the Rectangle and Texture classes**

Now, lets add something to our screen. What about a rectangle with a texture on it? First, lets include the Rectangle and Texture classes:

    #include <Rectangle.h>
    #include <Texture.h>

To make a new texture, you will need to call its constructor like so, remembering that only PNG files will work.

    SE::Texture texture("path/to/image.png");

As in most game engines, the (0,0) coordinate is in the top left of the screen. Keeping that in mind, lets add a new rectangle to our screen:

    auto rectanglePosition=SE::vec2(xCoordinate, yCoordinate); 
    auto rectangleSize=SE::vec2(width,height);
    auto rectangleColor=SE::vec3(R,G,B); // the RGB values need to be given as values from 0.0 to 1.0, 0.0 being no color, and 1.0 being full color
    float priority=2 // this will set the desired priority of the rectangle, because you might want some objects to be in front of others
    auto rectangle=std::make_shared<SE::Rectangle>(rectanglePosition,rectangleSize,rectangleColor,texture, priority);

Having the rectangle instantiated, we need to add it to the render draw cycle:

    SE::Game::m_renderer->addRectangleToDrawCall(rectangle);

You will now see your rectangle drawn on screen.

**Enabling and using the light**

To enable the light and configuring its parameters you will need to call these methods:

    SE::Game::m_renderer->setLightStatus(true);

    auto lightPosition=SE::vec2(xCoordinate, yCoordinate);
    SE::Game::m_renderer->setLightPosition(lightPosition);

    float lightRadius=100.0f;
    SE::Game::m_renderer->setLightRadius(lightRadius);

    float lightIntensity=2.0f;
    SE::Game::m_renderer->setLightIntensity(lightIntensity);

You can always call these methods in your game loop, being possible to make your light move and pulse.


## Motivation

This framwork was created because most game engines are hard to get started with and they come in large file sizes, but also because we wanted to learn modern C++, and what better way to write hardcore C++ than within a game engine?

## Installation

Install these first:

nodeJS: https://nodejs.org/en/download/

CMake: https://cmake.org/download/

ez-gen: https://github.com/hamez0r/ez-gen


In terminal, go to ez-gen folder, and execute: npm install -g

Clone this repo:
https://github.com/radumotrescu/studious-engine

In terminal, go to studious-engine, and enter any of the folders starting with "ez-", then execute: ez-gen. This will generate a Visual Studio solution for you, where you can start making your game.


## API Reference



## Contributors

Let people know how they can dive into the project, include important links to things like issue trackers, irc, twitter accounts if applicable.

## License

A short snippet describing the license (MIT, Apache, etc.)
