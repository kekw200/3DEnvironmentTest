# EXTREMELY WIP
Very rough personal project where I try to implement a 3D graphic environment using OpenGL + GLFW (+ eventually probably Dear ImGui) through, partially, trial and error (and partially google, stack overflow, documentation and learnopengl usage), in order to learn the aforementioned along with C++.
Hence the code is anything but clean and tidy, full of all kinds of commented out lines and what else have you, and probably also unoptimal/unidiomatic ways of both C++ and framework/API usage.

# Current state
So far the application is capable of holding crude representations of 3D meshes with some attributes (like location in space) and rendering them from the POV of a currently static camera - there is no movement yet. So really all it does is display a static image of hardcoded objects, which, at this moment, means 2 walls and 2 boxes, see below (wireframe mode):

<p align="center"><img width="602" height="432" alt="3DEnvironmentTest_eGem6i0NbF" src="https://github.com/user-attachments/assets/92dcfd62-c8ef-410e-a0a5-8b521bf7e0da" /></p>

The aim now is to add camera movement and a more streamlined way of loading in models.
