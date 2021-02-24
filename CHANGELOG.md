# Polaris Engine: CHANGELOG

Here you can see the different added features and fixed bugs in each version.

<br>

## - Version 0.2 - ???? -

--



#### Features added/upgraded

- Core:
  - Window Abstraction class, which encapsulates GLFW methods. Not fully disengaged  yet, because of events.
  
  - Now Time class is static, so you can access Time data from everywhere in the application.
  
    
  
- Debugger:

  - Added a static Log class, which allow us to send info to the console from everywhere, with a timestamp.
  - Added a static Debug class, which allow us to use assertions with associated messages sent to the console.  



#### Bugs fixed

- 



#### Other improvements

- Application life cycle is now separated from Window life cycle.

- <iostream> include is removed from every class (kind of, still remains a bug to fix).

  




## - Version 0.1 - 18/2/2021 -

This is the first public version of Polaris Engine. It contains a basic 3D renderer, where you can move around with the mouse and keyboard, and load/remove some assets.



#### Features added

- Basic Game Engine structure and configuration.

- Basic 3D Renderer: you can load 3D models, textures (color and normal mapping), shaders and lights.  
- Camera Controller: you can move around using the mouse and keyboard.
- Input Module started: Input polling added. You can get if a key or mouse button is pressed or not, and get the actual mouse position.
