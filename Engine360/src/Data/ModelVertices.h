#pragma once

//All Data Below are ordered : Position, Normals, UV-Coordinates

const int CUBE_VERTICES_COUNT = 36;
#define CUBE_DATA(length , width, height) { \
-0.5f * length, -0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, \
 0.5f * length, -0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, \
 0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, \
 0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, \
-0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, \
-0.5f * length, -0.5f * width, -0.5f * height,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, \
																				  \
-0.5f * length, -0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, \
 0.5f * length, -0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, \
 0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, \
 0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, \
-0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, \
-0.5f * length, -0.5f * width,  0.5f * height,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, \
																				  \
-0.5f * length,  0.5f * width,  0.5f * height, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, \
-0.5f * length,  0.5f * width, -0.5f * height, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, \
-0.5f * length, -0.5f * width, -0.5f * height, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, \
-0.5f * length, -0.5f * width, -0.5f * height, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, \
-0.5f * length, -0.5f * width,  0.5f * height, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, \
-0.5f * length,  0.5f * width,  0.5f * height, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, \
																				  \
 0.5f * length,  0.5f * width,  0.5f * height,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, \
 0.5f * length,  0.5f * width, -0.5f * height,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, \
 0.5f * length, -0.5f * width, -0.5f * height,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, \
 0.5f * length, -0.5f * width, -0.5f * height,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, \
 0.5f * length, -0.5f * width,  0.5f * height,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, \
 0.5f * length,  0.5f * width,  0.5f * height,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, \
																				  \
-0.5f * length, -0.5f * width, -0.5f * height,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, \
 0.5f * length, -0.5f * width, -0.5f * height,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, \
 0.5f * length, -0.5f * width,  0.5f * height,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, \
 0.5f * length, -0.5f * width,  0.5f * height,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, \
-0.5f * length, -0.5f * width,  0.5f * height,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, \
-0.5f * length, -0.5f * width, -0.5f * height,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, \
																				  \
-0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, \
 0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, \
 0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, \
 0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, \
-0.5f * length,  0.5f * width,  0.5f * height,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, \
-0.5f * length,  0.5f * width, -0.5f * height,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f  \
};

const int PLANE_VERTICES_COUNT = 6;
#define PLANE_DATA(length , width, height) { \
-0.5f * length, -0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, \
 0.5f * length, -0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, \
 0.5f * length,  0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, \
\
 0.5f * length,  0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, \
-0.5f * length,  0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, \
-0.5f * length, -0.5f * width, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, \
};
