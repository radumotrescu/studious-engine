# Synopsis

studious-engine is a small framework designed to make it easy for game makers to create a game in a small time frame.

# Motivation

This framework was created because most game engines are hard to get started with and they come in large file sizes, but also because we wanted to learn modern C++, and what better way to write hardcore C++ than within a game engine?

# Installation

Install these first:

    nodeJS: https://nodejs.org/en/download/

    CMake: https://cmake.org/download/

    ez-gen: https://github.com/hamez0r/ez-gen


In terminal, go to ez-gen folder, and execute: 
    
    npm install -g

Clone this repo:

    https://github.com/radumotrescu/studious-engine

In terminal, go to studious-engine, and enter any of the folders starting with "ez-", then execute: 

    ez-gen
    
This will generate a Visual Studio solution for you, where you can start making your game.


# Walkthrough

**Making your own game**

Our framework delivers a quick way to write your own 2D game. To get started you have to include the specific header.
```
#include "Game.h"
``` 
The Game class is an abstract class. By extending it, you are allowed to come with your own implementations and visions for the coming game.

```
virtual auto update() ->void = 0;
virtual auto start() ->void = 0;
virtual auto init() ->void;
virtual auto run() ->void;
virtual auto onTick() ->void;
```

The init method, sets the widow size to 600 width x 800 height and sets-up the renderer of the game.
The run method, assures the loop circuit of the game at an assessed time. This time is given by the onTick method. 
The default tick is set to 120 fpms. On every tick, the update method is called.
The start method must be implemented as well, and it is a point of stability and personalization in the further development of the new game. It is also an entry point for every other foreign behaviors. 

**Accessing your graphics context**

 You can access the window height and window width by calling:

    SE::Game::m_window->getHeight();
    SE::Game::m_window->getWidth();

And you can access the renderer by using:

    SE::Game::m_renderer

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
    float priority=2; // this will set the desired priority of the rectangle, because you might want some objects to be in front of others
    auto rectangle=std::make_shared<SE::Rectangle>(rectanglePosition,rectangleSize,rectangleColor,texture, priority);
    auto rectangle=std::make_shared<SE::Rectangle>(rectanglePosition,rectangleSize,rectangleColor, priority);
    auto rectangle=std::make_shared<SE::Rectangle>(rectanglePosition,rectangleSize,texture, priority);

Having the rectangle instantiated, we need to add it to the render draw cycle:

    SE::Game::m_renderer->addRectangleToDrawCall(rectangle);

You will now see your rectangle drawn on screen.

Advanced rectangle methods:

By default, the rectangles are affected by the light on the screen. If you want to disable this feature, for example, to make a rectangle part of a HUD and you dont want it to be affected by light, you will call the "setAffectedByLighting" method.To turn this back on, just call the method with the "true" argument.

    rectangle->setAffectedByLighting(false);
    rectangle->setAffectedByLighting(true);

Also by default, textures on rectangle dont loop around themselves. If you want the textures to loop in a certain direction, you will use the "setScrollingSpeedMethod". This will enable you to do background images that scroll endlessly. Remember, for this to look good, you will need a really good texture image.

    rectangle->setScrollingSpeed(SE::vec2(-0.5,4));  // this will scroll the texture to the right and upwards.


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

**Changing the characteristics of a collision**

The isCollided method accessible through: 

```
#include "CollisionChecker.h"
```

Its default behavior is to count in a collision all the edges of the sprite, in our case: all four edges of the rectangle. 
If it is desired to change that fact, it is possible through extending the CollisionChecker class and overriding the isCollided method.

Note that the default CollisionManager makes use of the default collision also.

**Adding sounds**

For adding sounds, you need to include the following header:

	#include<SoundManager.h>

SoundManager allows you to play, loop, pause and stop sounds.
First of all, you need to initialize a system and the channels you need to use. Don't worry, for that you only need to call init() method:

	SE::SoundManager::init();

Next, you can create sounds and add them to the SoundManager:

	auto sound = std::make_shared<Sound>("soundName", "path/to/sound");
	SE::SoundManager::add(sound);

For using sound added to the sound manager, you have to call get() method:

	SE::SoundManager::get("soundName")->play();

In the same way, you can use loop(), pause() and stop() methods.

When update() method from your game is called, you have to specifically call:

	SE::SoundManager::update();

After you don't need sounds anymore, you have to free up the memory. The clean() method releases all the sounds and delete all the channels:

	SE::SoundManager::clean();

Remember that after the memory is cleaned up, you need to call init method again.


