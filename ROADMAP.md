# Polaris Engine: ROADMAP

Here you can see the different features that will be added to each version.

<br>

## Version 0.1 - 18/2/2021

This is the first version of Polaris Engine. It includes the basics of the Game Engine: 3D Rendering, Basic Input and initial configuration. 

- Basic Game Engine structure and configuration.

- Basic 3D Renderer: you can load 3D models, textures (color and normal mapping), shaders and lights.  
- Camera Controller: you can move around using the mouse and keyboard.
- Input Module started: Input polling added. You can get if a key or mouse button is pressed or not, and get the actual mouse position.

<br>


## Version 0.2 - Around mid-end March.

This version includes:

- **Core**:

  - A proper Window class.

  - Some existing classes refactoring.

    

- **Rendering**:

  - Skybox.

  - Shadow Mapping.

  - A better images loader, supporting more formats besides PNG.

  - Some rendering performance optimizations.

  - Some rendering bug-fixing.

    

- **UI**:

  - Integrating Dear IMGUI for creating User Interfaces.

  - The first visual tool: Managing models load/remove from the application.

    

- **Debugger**

  - Log-To-Console system.

  - Assertions with log info.

    

- **General**

  - Better internal and external documentation.
  - General optimizations and refactoring.

<br>


## Version 0.3 - Around mid-end April / start May.

This version includes:

- **Core**:

  - Refactoring of the modules to make them more accessible and easy-to-use.

    

- **Rendering**:

  - Basic 2D Renderer.

  - Sprites.

  - A better way to manage Uniforms.

    

- **UI**:

  - The second visual tool. Models properties modification: Transform properties, Rendering properties, etc.

    

- **Debugger**

  - Log-To-File system.

  - Add basic profiling

  - Assertions with log-to-file

    

- **Input**

  - Add Input Down, Pressed and Up.

  - Some refactoring.

    

- **General**
  - A better way to manage dependencies, if possible.
  - Better internal and external documentation.
  - General optimizations and refactoring.

<br>


## Version 0.4

When this point is reached, there will be an analysis of the actual state of the Engine. Then, the next versions roadmap will be created in consequence.
