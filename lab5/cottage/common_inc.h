#pragma once

#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#endif

#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glew.h>

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include <numbers>
#include <stdexcept>
#include <string>
#include <array>
