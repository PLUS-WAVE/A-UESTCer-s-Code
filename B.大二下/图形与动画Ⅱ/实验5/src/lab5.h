#ifndef LAB5_H
#define LAB5_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <SOIL.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <random>
#include <math.h>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector2
{
	float x;
	float y;
};

namespace LAB5
{
	int lab5(int argc, char** argv);
}

#endif // !LAB5_H
