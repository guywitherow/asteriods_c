#ifndef GLUT_H
#define GLUT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#endif // !GLUT_HEADER