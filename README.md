# miniRT - A Simple Raytracer

A lightweight but powerful raytracer written in C that renders 3D scenes with realistic lighting, shadows, and reflections. Built with a custom math library and the MLX42 graphics framework.

## Overview

miniRT is a raytracer that demonstrates fundamental computer graphics concepts including:
- **Ray-object intersection detection** for spheres, planes, cylinders, and triangles
- **Phong lighting model** with ambient, diffuse, and specular components
- **Shadow casting** with point lights
- **Real-time rendering** to a graphical window
- **Scene parsing** from custom `.rt` configuration files

## Features

### Supported Objects
- **Spheres** - Perfect for basic raytracing examples
- **Planes** - Infinite flat surfaces for backgrounds and grounds
- **Cylinders** - With caps, for more complex scenes
- **Triangles** - For custom geometric shapes

### Lighting System
- **Ambient lighting** - Global illumination baseline
- **Point lights** - Multiple light sources with intensity control
- **Phong shading** - Combines ambient, diffuse, and specular components
- **Shadow casting** - Realistic shadows from point light sources

### Additional Features
- **Checkerboard patterns** - Optional texture mapping on surfaces
- **Anti-aliasing ready** - Architecture supports supersampling
- **Interactive window** - Real-time rendering with MLX42
- **Robust parsing** - Comprehensive error checking and validation

## Project Structure

```
miniRT/
├── header/                 # Header files
│   ├── miniRT.h           # Main data structures and definitions
│   └── parser.h           # Parser-related structures
├── src/                   # Source code
│   ├── main.c             # Entry point
│   ├── colour/            # Color calculation and shading
│   ├── objects/           # Object intersection functions
│   ├── parser/            # Scene file parsing and validation
│   ├── ray/               # Ray generation and tracing
│   ├── utils/             # Vector math operations
│   └── window/            # Window rendering and display
├── libraries/
│   ├── libft/             # Custom C library (string, memory, list utilities)
│   └── mlx42/             # MLX42 graphics library
├── scenes/                # Example scene files (.rt format)
├── files/                 # Additional test scenes
└── Makefile               # Build configuration
```

## Scene File Format (.rt)

Scene files use a simple line-based format. Each line defines an element with space-separated values.

### Scene Elements

**Ambient Lighting** - Global illumination
```
A  <ratio> <R,G,B>
A  0.3     255,255,255
```
- `ratio`: Intensity from 0.0 to 1.0
- `R,G,B`: Color values (0-255)

**Camera**
```
C  <x,y,z> <dx,dy,dz> <FOV>
C  0,0,-1  0,0,-1     90
```
- Position coordinates `(x,y,z)`
- Normalized direction vector `(dx,dy,dz)`
- Field of view `FOV` in degrees (0-180)

**Light Source**
```
L  <x,y,z> <brightness> <R,G,B>
L  15,20,3 0.1          255,102,102
```
- Position `(x,y,z)`
- Brightness intensity (0.0-1.0)
- Color `(R,G,B)`

**Sphere**
```
sp <x,y,z> <diameter> <R,G,B>
sp 0,3,-9  6          255,153,0
```
- Center position `(x,y,z)`
- Diameter (not radius)
- Color `(R,G,B)`

**Plane**
```
pl <x,y,z> <nx,ny,nz> <R,G,B>
pl 0,0,0   0,1,0      128,128,128
```
- Point on plane `(x,y,z)`
- Normalized normal vector `(nx,ny,nz)`
- Color `(R,G,B)`

**Cylinder**
```
cy <x,y,z> <dx,dy,dz> <diameter> <height> <R,G,B>
cy -4,-2,-8 1,0,1      4          5        0,0,255
```
- Center position `(x,y,z)`
- Normalized axis vector `(dx,dy,dz)`
- Diameter (not radius)
- Height
- Color `(R,G,B)`

**Triangle**
```
tr <x1,y1,z1> <x2,y2,z2> <x3,y3,z3> <R,G,B>
tr 0,0,0       1,0,0      0,1,0      255,0,0
```
- Three vertex positions
- Color `(R,G,B)`

### Notes on Format
- Empty lines and comment lines (starting with `#`) are ignored
- At least one camera, light source, and object are required
- All vectors must be normalized in the input file
- Colors use standard RGB values (0-255)

## Building

### Prerequisites
- GCC or Clang C compiler
- Make
- GLFW 3 library (for MLX42)

### Compilation
```bash
make              # Build the project
make clean        # Remove object files
make fclean       # Remove all generated files
make re           # Clean and rebuild
```

The executable `miniRT` will be created in the project root.

## Usage

Run the raytracer with a scene file:
```bash
./miniRT scenes/scene_1.rt
```

The renderer will:
1. Parse the scene file
2. Calculate all pixels using raytracing
3. Display the rendered image in a window
4. Keep the window open until you close it

### Window Controls
- **Close window** - Click the close button or press ESC (if implemented)

## Technical Details

### Rendering Pipeline

1. **Input Parsing** (`parser/`)
   - Validates scene file format and values
   - Allocates memory for objects and lights
   - Handles error reporting with detailed messages

2. **Ray Generation** (`ray/`)
   - Creates primary rays from camera through each pixel
   - Implements camera coordinate system with FOV

3. **Intersection Detection** (`objects/`)
   - Ray-sphere intersection
   - Ray-plane intersection
   - Ray-cylinder intersection (including caps)
   - Ray-triangle intersection
   - Finds closest intersection along ray

4. **Color Calculation** (`colour/`)
   - Implements Phong shading model
   - Computes ambient, diffuse, and specular components
   - Handles shadow rays to determine occlusion
   - Optional checkerboard texture

5. **Rendering** (`window/`)
   - Converts colors to pixel values
   - Renders to MLX42 window
   - Maintains image buffer

### Data Structures

**Key types** (see `miniRT.h`):
- `t_vec3` - 3D vectors for positions and directions
- `t_colour` - RGB color values
- `t_ray` - Ray with origin, direction, and distance
- `t_camera` - Camera with position, direction, FOV
- `t_sphere`, `t_plane`, `t_cylinder`, `t_triangle` - Object definitions

### Coordinate System
- **X-axis**: Left-right (positive = right)
- **Y-axis**: Up-down (positive = up)
- **Z-axis**: Forward-backward (positive = away from viewer)

## Example Scenes

Several example scenes are included:

- `scenes/scene_1.rt` - Basic scene with spheres, cylinders, and multiple lights
- `scenes/scene_2.rt` - Additional sample configuration
- `scenes/sphere/sphere_circle_white.rt` - Simple sphere with white circle
- `scenes/sphere/sphere_shadow.rt` - Demonstrates shadow casting
- `scenes/plane/plane_white.rt` - Plane rendering examples
- `scenes/cylinder/cylinder_crosses.rt` - Multiple intersecting cylinders
- `scenes/triangle/triangle_mult_light.rt` - Triangle with multiple lights

## Performance Optimizations

The project includes several optimizations:
- **Compiler flags**: `-O3 -flto` for optimization and link-time optimization
- **Early ray termination**: Stops checking after finding closest object
- **Efficient vector math**: Optimized operators in `utils/`

## Error Handling

The parser provides comprehensive error detection:
- File access validation
- Format validation for each element type
- Numeric range checking (e.g., FOV 0-180, ratios 0.0-1.0)
- Normalized vector verification
- Descriptive error messages to aid debugging

## Dependencies

- **libft** - Custom C library with utility functions
- **MLX42** - Modern graphics library for window rendering

Both are included in the `libraries/` directory.

## Development Notes

### Code Organization
- Modular design with clear separation of concerns
- Each geometric object type has dedicated intersection code
- Color calculation separated from ray tracing logic
- Parser kept independent from rendering

### Future Enhancements
- Reflections and refractions
- Soft shadows with area lights
- Texture mapping
- Normal mapping
- Anti-aliasing implementation
- Parallel rendering

