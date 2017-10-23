# Synopsis

studious-engine is a small framework designed to make it easy for game makers to create a game in a small time frame.

# Summary
#### 1. Window
#### 2. InputManager
#### 3. Vectors and Matrices
#### 4. Shader
#### 5. Buffer and VertexArray
#### 6. SimpleRenderer
#### 7. Rectangle
#### 8. Shader
#### 9. Texture
#### 10. CollisionChecker and CollisionManager
#### 11. Font
#### 12. Sound and Sound Manager
#### 13. Light
#### 14. Application


### 1. Window

**TODO**


### 2. InputManager

**TODO**


### 3. Vectors and Matrices

**TODO**


### 4. Shader

**TODO**


### 5. Buffer and VertexArray

**TODO**


### 6. SimpleRenderer

**TODO**


### 7. Rectangle

**TODO**


### 8. Shader

**TODO**


### 9. Texture

**TODO**


### 10. CollisionChecker and CollisionManager

**TODO**


### 11. Font

**TODO**


### 12. Sound and Sound Manager

**TODO**


### 13. Light

**TODO**


### 14. Application

**TODO**


# Code examples

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

**Adding a custom behavior on collision with other sprites**

The header needed to access the collision manager is:
```
#include "CollisionManager.h"
```
The collision manager binds the signal isCollided and the onCollision slot of a certain sprite. 
To add a custom behavior on a collision, first we must know that this future behavior must be part of a class. In other words, if we would want to define a new kind of a rectangle, let's say a RedRectangle, it would have a method called onCollisionWithClassicRectangle with a void return type and two parameters of shared_ptr<Rectangle>& type.
```
auto RedRectangle::onCollisionWithClassicRectangle(std::shared_ptr<SE::Rectangle>& thisRectangle, std::shared_ptr<SE::Rectangle>& thatRectangle) ->void;
```

This method is going to be passed to the collision manager like it follows:
```
RedRectangle redRectangle;
SE::CollisionManager::addCollisionalEntities(rectangle, redRectangle, std::bind(&RedRectangle::onCollisionWithClassicRectangle, &redRectangle, std::placeholders::_1, std::placeholders::_2));

```
Note that the manager requires not only the method pointer, but also an instance pointer of the class containing the method. This makes the context identifiable and the behavior customizable for each and every object.

**Recalling the custom behaviors declared on different collisions**	

To call the behaviors declared previously, all you need to do is call the checkCollisions found in CollisionManager:

```
SE::CollisionManager::checkCollisions();
``` 
	
# Motivation

This framwork was created because most game engines are hard to get started with and they come in large file sizes, but also because we wanted to learn modern C++, and what better way to write hardcore C++ than within a game engine?

# Installation

Install these first:

nodeJS: https://nodejs.org/en/download/

CMake: https://cmake.org/download/

ez-gen: https://github.com/hamez0r/ez-gen


In terminal, go to ez-gen folder, and execute: npm install -g

Clone this repo:
https://github.com/radumotrescu/studious-engine

In terminal, go to studious-engine, and enter any of the folders starting with "ez-", then execute: ez-gen. This will generate a Visual Studio solution for you, where you can start making your game.


# API Reference



# Contributors

Let people know how they can dive into the project, include important links to things like issue trackers, irc, twitter accounts if applicable.

# License

A short snippet describing the license (MIT, Apache, etc.)
