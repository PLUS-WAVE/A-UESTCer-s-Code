#include "lab3.h"

namespace LAB3
{
#define	MAX_PARTICLES	500        	// Number of particles to create
#define PI              3.14159f
#define RHO             360
#define LIFE            1.f
#define TIME            0.01f

float windowHeight = 100, windowWidth = 100;

GLuint texture[1];
std::default_random_engine generator;
std::normal_distribution<float> distribution(0.0, 10.0);

int LoadGLTextures()
{
	for (int i = 0; i < 2; i++)
	{
		texture[i] = SOIL_load_OGL_texture("Data/Particle.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y);
	}

	if (texture[0] == 0)
		return false;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}

typedef struct						// Create a Structure for Particle
{
	float	life;					// Particle Life
	float   init_life;
	float	speed_aging;			// Aging speed

	float	r;						// Red value
	float	g;						// Green value
	float	b;						// Blue value

	float	x;						// X position
	float	y;						// Y position
	//float	z;						// Z position

	float	v_x;					// X velocity
	float	v_y;					// Y velocity
	//float	v_z;					// Z velocity

	float	a_x;					// X acceleration
	float	a_y;					// Y acceleration
	//float	a_z;					// Z acceleration

	float	size;					// Size of particle
}
particle;							// Particles structure

particle particles[MAX_PARTICLES];	// Particle array (Room for particle info)



void changeSize(int w, int h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h); // 设置视口大小
	glMatrixMode(GL_PROJECTION); // 设置投影矩阵
	glLoadIdentity(); // 重置投影矩阵
	aspectRatio = (GLfloat)w / (GLfloat)h; // 计算窗口的宽高比
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
	}
	glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW); // 设置模型视图矩阵
	glLoadIdentity(); // 重置模型视图矩阵
}



void RenderScene(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);		  // Clear screen and depth buffer

	for (int i = 0; i < MAX_PARTICLES; i++)					         // All particles
	{
		float x = particles[i].x;						        // Position of particle
		float y = particles[i].y;
		float z = 0;
		float size = particles[i].size;                      // Size of particle

		// Draw particle using RGB values, alpha value based on it's life
		glColor4f(particles[i].r, particles[i].g, particles[i].b, particles[i].life);

		// 矩形
		glBegin(GL_QUADS);
		glVertex3f(x - 2.0f, y - 2.0f, z);
		glVertex3f(x + 2.0f, y - 2.0f, z);
		glVertex3f(x + 2.0f, y + 2.0f, z);
		glVertex3f(x - 2.0f, y + 2.0f, z);
		glEnd();

		glPopMatrix();
	}

	glColor4f(0.0f, 0.0f, 0.0f, 0.1f);
	glRectf(-windowWidth, -windowHeight, windowWidth, windowHeight);

	glutSwapBuffers();
}

int InitPaticleSystem(void)
{

	for (int i = 0; i < MAX_PARTICLES; i++)				         // Initials all particles
	{
		float lifeRange = 10.0f; // Set the life range for more random generation time
		particles[i].init_life = ((rand() % 100) / 100.0f) * lifeRange; // Give All The Particles Random Initial Life
		particles[i].life = particles[i].init_life;
		particles[i].speed_aging = 0.1;

		float distance = abs(particles[i].x);
		float maxDistance = 15.0f;

		std::uniform_real_distribution<float> random_factor(0.0f, 0.1f);

		// Set color for particle
		float lerp_factor = distance / maxDistance;
		particles[i].r = 1.0f;
		particles[i].g = (1.0f - lerp_factor);
		particles[i].b = 0.0f;

		float range = 20.0f; // Increase the range for larger smoke effect
		particles[i].x = ((rand() % 100) / 100.0f) * range - range / 2.0f;
		particles[i].y = -55.0f;

		float speedRange = 4.0f; // Increase the speed range for more random smoke effect
		particles[i].v_x = ((rand() % 100) / 100.0f) * speedRange - speedRange / 2.0f;
		particles[i].v_y = ((rand() % 100) / 100.0f) * speedRange - speedRange / 2.0f;

		float accelerationRange = 2.0f; // Set the acceleration range for more random smoke effect
		particles[i].a_x = ((rand() % 100) / 100.0f) * accelerationRange - accelerationRange / 2.0f; // Set X Axis acceleration
		particles[i].a_y = 50.0f; // Set Y Axis acceleration
	}

	return true;
}

void Update()
{
	for (int i = 0; i < MAX_PARTICLES; i++)					// All The Particles
	{
		particles[i].x += particles[i].v_x * TIME;         // update position of particle
		particles[i].y += particles[i].v_y * TIME;

		particles[i].v_x += particles[i].a_x * TIME;			// update velocity
		particles[i].v_y += particles[i].a_y * TIME;

		particles[i].life -= particles[i].speed_aging;		// reduce particles life

		float theta, phi, rho;
		if (particles[i].life < 0.0f)					// if particle has reached end of life
		{
			particles[i].init_life = LIFE + rand() % 10 / 10.0;		    // Give All The Particles Full Life
			particles[i].life = particles[i].init_life;
			particles[i].speed_aging = TIME;

			particles[i].x = distribution(generator);
			particles[i].y = -55.0f;

			float distance = abs(particles[i].x);
			float maxDistance = 15.0f;

			std::uniform_real_distribution<float> random_factor(0.0f, 0.1f);

			// Set color for particle
			float lerp_factor = distance / maxDistance;
			particles[i].r = 1.0f;
			particles[i].g = (1.0f - lerp_factor); 
			particles[i].b = 0.0f; 
			
			float speedRange = 10.0f;
			particles[i].v_x = ((rand() % 100) / 100.0f) * speedRange - speedRange / 2.0f;
			particles[i].v_y = 2.0f;

			particles[i].a_x = 0.0f;							// Set X Axis acceleration
			particles[i].a_y = 50.0f;							// Set Y Axis acceleration
		}
	}
}

void checkBump()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		float x = particles[i].x;
		float y = particles[i].y;

		// 然后检测碰撞，如果碰到边界就反弹
		if (x  > windowWidth || x < -windowWidth)
		{
			particles[i].v_x = -particles[i].v_x;
			x += particles[i].v_x; // 稍微调整位置，防止卡在边界上
		}
		if (y  > windowHeight || y < -windowHeight)
		{
			particles[i].v_y = -particles[i].v_y;
			y += particles[i].v_y; // 稍微调整位置，防止卡在边界上
			
		}
	}
}



void TimerFunction(int value)
{
	Update();
	checkBump();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 0.1);
}


int InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return false;
	}


	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	return true;
}

int lab3(int argc, char** argv)
{

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Particle system");

	// register callbacks
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutTimerFunc(10, TimerFunction, 1);
	
	// Setup the rendering state
	InitGL();
	InitPaticleSystem();

	// enter GLUT event processing loop
	glutMainLoop();

	return 0;
}
}