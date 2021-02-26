### Polaris Engine ![Version](https://img.shields.io/badge/version-v0.1.3-green) ![License](https://img.shields.io/badge/License-Apache2.0-yellow)



# What is Polaris Engine?

Polaris Engine is an early-stage 2D/3D Game Engine created from scratch for the sake of learning. It's being build using C++ &amp; OpenGL, 

The game engine contains several modules and submodules, as well as a visual editor.

###### Modules

- **Core**: Basic features, the core pieces of the engine. ![Version](https://img.shields.io/badge/v0.2-green)
- **Math**: It contains all the math features: Vectors, Matrices, etc. *Right now using GLM until this module is started*. ![Version](https://img.shields.io/badge/NotStarted-red)
- **Rendering**: It contains all the rendering features. 3D/2D Renderer, Models, Shaders, etc. ![Version](https://img.shields.io/badge/v0.1.1-green)
- **UI**: It contains features for adding text, menus, etc. Used In-game and in the Editor. ![Version](https://img.shields.io/badge/NotStarted-red)
- **Physics**: It contains features related to physics: Rigidbodies, collisions, etc. ![Version](https://img.shields.io/badge/NotStarted-red)
- **Audio**: It contains audio reproduction features. ![Version](https://img.shields.io/badge/NotStarted-red)
- **Scripting**: It contains scripting features, so we can add scripts to the game objects. ![Version](https://img.shields.io/badge/NotStarted-red)
- **Events**: It contains an event system to structure all the application. ![Version](https://img.shields.io/badge/NotStarted-red)

###### Submodules

- **Debugger**: It contains debugging features: log-to-console/log-to-file messages, assertions, profiling, etc. ![Version](https://img.shields.io/badge/v0.2-green)

- **Input**: It contains input features, like input polling. ![Version](https://img.shields.io/badge/v0.1.1-green)

- **Memory**: It contains smart memory management features. ![Version](https://img.shields.io/badge/NotStarted-red)

  

###### Visual Editor

The Visual Editor hasn't been started yet. It is expected to have a very early version on Version 0.2.

<br>

## How to compile and use Polaris Engine

Right now, Polaris Engine is only compilable and usable on Windows. This repository includes a Visual Studio Solution ready to use. Follow these steps to start compiling Polaris Engine:

1. Clone the repository wherever you want.
2. Double click on `InstallDependencies.bat`. This script will locate the dependencies and properly unzip the `Dependencies.zip` for you.
3. Open the Visual Studio Solution and try to compile and execute Polaris Engine. It should work now. If it's not working, please make an issue in this repo and I will try to help you!

**Important:** Right now, Polaris Engine is only compilable in x64 mode. This will be fixed soon. Sorry.

<br>

## Quick links

- [CHANGELOG](https://github.com/Delunado/PolarisEngine/blob/master/CHANGELOG.md)

- [ROADMAP](https://github.com/Delunado/PolarisEngine/blob/master/ROADMAP.md)
