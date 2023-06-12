# Integrated Game Streaming Architecture

__This project is currently under development and despite what this file may say, it currently only demonstrates partial functionality of the planned system.__

This project contains the source code for a game streaming architecture, which uses one server application to render and stream the perspective of multiple connected clients to dedicated client applications. 

Compared to existing game streaming services, which detect game applications running on a system to capture and stream any outputs generated, this system has the game streaming logic integrated into the game application. 

Both the server and client application are written in C++ (compatible with C++20), making use of the OpenGL rendering API, as well as socket networking and video encoding algorithms.



## Table of Contents

1. [Table of Contents](#table-of-contents)
2. [Getting Started](#getting-started)                                                  \
    2.1. [Prerequisites](#prerequisites)                                                \
    2.2. [Installation](#installation)                                                  \
    2.3. [Opening In An IDE](#opening-in-an-ide)                                        \
    2.4. [Compilation](#compilation)                                                    \
    2.5. [Usage](#usage)                                                                \
    2.6. [Understanding the Project Structure](#understanding-the-project-structure)
3. [Development Overview](#development-overview)                                        \
    3.1. [Phase One](#phase-one)
4. [External Libraries](#external-libraries)                                            \
    4.1. [Spdlog](#spdlog)                                                              \
    4.2. [GLEW](#glew)
5. [Contributors](#contributors)
6. [License](#license)



## Getting Started

This section contains instructions on how to fetch a copy of the project files and either [open them in your chosen C++ IDE](#opening-in-an-ide) or [compile the source code](#compilation). \
While an IDE can be used to compile the source code, the compilation instructions provided do not require an IDE to be used.

There are prerequisites to using the source code, such as requiring specific technologies, which are listed [here](#prerequisites).

Once the applications have been compiled, instructions to use the two applications produced can be found [here](#usage).

### Prerequisites

1. This project uses the [Premake5](https://premake.github.io/) command line utility to describe the structure of the source code. \
   To follow the provided instructions, you will require __Premake5__ to generate IDE project files or generate makefiles to compile the applications.
2. This project uses C++ and was written using C++20. Although you may find that the source code can be interpreted with other versions of C++, C++20 is recommended. \
   To compile the C++ source code, you will require a __C++ compiler__, such as MSVC or MinGW. 
3. This project is only validated for the Windows 11 operating system.

### Installation

All project files can be found within the public [GitHub repository](https://github.com/JonathonMacleod/Integrated-Game-Streaming-Architecture).

From the GitHub repository, a link can be found to clone the repository using __Git__ (instructions can be found online). \
Alternatively, the contents of the GitHub repository can be downloaded as a ZIP file and decompressed into a folder to be used.

### Opening In An IDE

As this project uses the Premake5 command line utility, project files can be generated for your chosen IDE by following the instructions provided by Premake5 [here](https://premake.github.io/docs/Using-Premake). \
Currently, only the Visual Studio (2005 to 2022), XCode4, and CodeLite IDEs are supported by Premake5. \
The necessary `premake5.lua` file is provided in the same directory as this `README.md` file.

Alternatively, you may open the project files according to the instructions of an IDE of your own choosing.

### Compilation

As this project uses the Premake5 command line utility, GNU makefiles can be generated for the source files by following the instructions provided by Premake5 [here](https://premake.github.io/docs/Using-Premake). \
To use the makefiles generated to compile the applications, you will require the [GNU Make](https://www.gnu.org/software/make/) application and a GNU C++ compiler, such as [GCC](https://gcc.gnu.org/).

Alternatively, you may compile the source files according to the instructions of a compiler of your own choosing.

### Usage

Instructions on how to use the two applications of this project will be provided once they have been developed.

### Understanding the Project Structure

A description of the project structure will be provided as development commences.



## Development Overview

To manage the development of this project, multiple phases have been planned so that features of the system can be implemented incrementally.

As of now, there are four phases planned (but these are subject to change):

- [ ] __Phase 1:__ Creating a basic server application, which should utilise OpenGL to render multiple player perspectives in a 3D game scene. Also adding basic user input detection to manipulate player perspectives.
- [ ] __Phase 2:__ Creating a basic client application, which uses OpenGL to render an image to the user.
- [ ] __Phase 3:__ Extending the server application to extract the rendered perspective of each player, and stream the perspective to the relevant connected client application to be rendered as images. The client application will further be extended to detect user inputs and stream the instructions to the server application to control the perspective of the relevant player.
- [ ] __Phase 4:__ Implementing a video encoding algorithm to reduce the amount of data transmitted between the server and client applications.

Currently the project is in phase one.

### Phase One

So far during phase one, a server application has been created using [spdlog](#spdlog) to manage logging, [GLEW](#glew) to interact with the OpenGL rendering API, and [GLFW](#glfw) to create a window with an OpenGL context.     \
Basic code has also been written to load GLSL shader programs into OpenGL.



## External Libraries

### Spdlog

The logging library spdlog (version 1.11.0) has been integrated into this project.                                                                                                              \
A copy of the source code for the integrated version of the library can be found at the GitHub repository [here](https://github.com/gabime/spdlog/releases/tag/v1.11.0).                        \
This library has been used in accordance with the MIT license it was supplied with, a copy of which can be found [here](./libs/spdlog-v1-11-0/LICENSE).                                         \
Credit for this library is owed to the contributors of the original GitHub repository, and no modifications have been made.

As spdlog uses the [fmt](https://github.com/fmtlib/fmt) library, this project is also produced in compliance with the fmt license, a copy of which can be found [here](./libs/fmt/LICENSE.rst).

### GLEW

The OpenGL extension wrangler (GLEW) library (version 2.1.0) has been used to expose OpenGL functionality.                                                                                                  \
A copy of the source code for the integrated version of the library can be found at the GitHub repository [here](https://github.com/nigels-com/glew/tree/glew-2.1.0).                                       \
This library has been used in accordance with the Modified BSD license, Mesa 3-D license and Khronos License it was supplied with, a copy of which can be found [here](./libs/glew-v2-1-0/LICENSE.txt).     \
Credit for this library is owed to the contributors of the original GitHub repository, and no modifications have been made.

### GLFW

The GLFW library (version 3.3.8) has been used to create application windows and detect user inputs.                                                                    \
A copy of the source code for the integrated version of the library can be found at the GitHub repository [here](https://github.com/glfw/glfw/releases/tag/3.3.8).      \
This library has been used in accordance with the zlib/libpng license, a copy of which can be found [here](./libs/glfw-v3-3-8/LICENSE.md).                              \
Credit for this library is owed to the contributors of the original GitHub repository, and no modifications have been made.



## Contributors

This project is solely developed and managed by [Jonathon Macleod](https://github.com/JonathonMacleod).



## License

This project is not currently available for use under any license.



[//]: # (All hyperlinks provided are valid as of 10/06/2023)