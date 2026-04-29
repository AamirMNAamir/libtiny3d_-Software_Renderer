#  libtiny3d – CO1020 Final C Project (Group 64)

## Project Overview

*libtiny3d* is a lightweight 3D software rendering engine implemented entirely in C for our CO1020 Computer Systems Programming course. The project covers:

-  *Task 1:* 2D Canvas & Line Drawing  
-  *Task 2:* 3D Math Library (vectors, matrices, projections)  
-  *Task 3:* 3D Wireframe Rendering Pipeline  
-  *Task 4:* Lighting Model & Bezier Animation

This repository demonstrates fundamental graphics techniques without using external graphics APIs like OpenGL.

---

## Task Breakdown

### Task 1: Canvas & Line Drawing

- Files: canvas.c, canvas.h
- Implements:
  - Grayscale float-precision canvas
  - Bilinear filtering for smooth pixel intensity distribution
  - Line drawing with floating-point start and end points, configurable thickness
- Demo:
  - demo/main.c draws radial clock lines to test accuracy

---

###  Task 2: 3D Math Library

- Files: math3d.c, math3d.h
- Provides:
  - Vector operations (dot, cross, normalize, SLERP)
  - Matrix operations (identity, translation, scaling, rotations)
  - Perspective projection with frustum matrix
- Test:
  - tests/test_math.c verifies implementation correctness

---

###  Task 3: 3D Rendering Pipeline

- Files: renderer.c, renderer.h, main.c
- Features:
  - Transforms vertices through world, view, and projection matrices
  - Clips meshes to circular viewport
  - Renders wireframe meshes like a cube or soccer ball

---

###  Task 4: Lighting Model & Bezier Animation

- Files: lighting.c, lighting.h, animation.c, animation.h
- Implements:
  - Lambert diffuse lighting model for realistic edge brightness
  - Cubic Bezier curve animation for smooth mesh motion

---

## Build Instructions

###  Prerequisites

- *GCC (C compiler)*
- *Make* (optional, for automated build)
- Linux or WSL recommended

###  Build Steps

1. *Clone repository*

```bash
git clone <repo-link>
cd libtiny3d
