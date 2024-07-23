#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define	MAX_PARTICLES	200        	// Number of particles to create
#define PI              3.14159f
#define RHO             50
#define LIFE            3.0f
#define TIME            0.01f

float windowHeight, windowWidth;

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
	float	z;						// Z position

	float	v_x;					// X velocity
	float	v_y;					// Y velocity
	float	v_z;					// Z velocity

	float	a_x;					// X acceleration
	float	a_y;					// Y acceleration
	float	a_z;					// Z acceleration
}
particle;							// Particles structure

particle particles[MAX_PARTICLES];	// Particle array (Room for particle info)



//当窗口改变大小时由GLUT函数库调用
void ChangeSize(int w, int h)
{
	float aspectRatio;

	//防止被0所除
	if (h == 0) h = 1;

	//把视口设置为窗口的大小
	glViewport(0, 0, w, h);

	//重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//建立剪裁区域（左、右、底、顶、近、远）
	aspectRatio = (float)w / (float)h;

	if (w <= h){
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else{
		windowWidth = 100.0 * aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int InitPaticleSystem(void)										
{
	float theta, phi, rho;
	
	for (int i = 0; i < MAX_PARTICLES;i++)				         // Initials all particles
	{
		particles[i].init_life = LIFE + rand() % 10 / 10.0;		    // Give All The Particles Full Life
		particles[i].life = particles[i].init_life;
		particles[i].speed_aging = TIME;

		particles[i].r = 1.0f;	                                // Set color for particle
		particles[i].g = 0.0f;	
		particles[i].b = 0.0f;	

		particles[i].x = 0.0f;								   // Set position for particle
		particles[i].y = 50.0f;							
		particles[i].z = 0.0f;

		theta = (rand() % 90 + 45) * PI / 180;
		phi = 90 * PI / 180;
		rho = rand() % RHO;
		particles[i].v_x = float(sinf(phi) * cosf(theta) * rho);  // Set X Axis Speed And Direction for particle
		particles[i].v_y = float(sinf(phi) * sin(theta) * rho);	  // Set Y Axis Speed And Direction for particle
		particles[i].v_z = float(cosf(phi) * rho);                // Set Z Axis Speed And Direction for particle
		
		particles[i].a_x = 0.0f;							// Set X Axis acceleration
		particles[i].a_y = -30.0f;							// Set Y Axis acceleration
		particles[i].a_z = 0.0f;							// Set Z Axis acceleration
	}

	return true;						
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		  // Clear screen and depth buffer
	
	for (int i = 0;i < MAX_PARTICLES; i++)					         // All particles
	{
		float x = particles[i].x;						        // Position of particle
		float y = particles[i].y;						   
		float z = particles[i].z;					

		// Draw particle using RGB values, alpha value based on it's life
		glColor4f(particles[i].r,particles[i].g,particles[i].b,particles[i].life);
		glPointSize(4.0f);
		glBegin(GL_POINTS);
			glVertex3f(x, y, z);
		glEnd();
	}

	glutSwapBuffers();
}

void Update(){
	for (int i = 0;i < MAX_PARTICLES; i++)					// All The Particles
	{
		particles[i].x += particles[i].v_x * TIME;         // update position of particle
		particles[i].y += particles[i].v_y * TIME;
		particles[i].z += particles[i].v_z * TIME;

		particles[i].v_x += particles[i].a_x * TIME;			// update velocity
		particles[i].v_y += particles[i].a_y * TIME;			
		particles[i].v_z += particles[i].a_z * TIME;			

		particles[i].life -= particles[i].speed_aging;		// reduce particles life

		float theta, phi, rho;
		if (particles[i].life < 0.0f)					// if particle has reached end of life
		{
			particles[i].init_life = LIFE + rand()%10/10.0;		// Give it new life
			particles[i].life = particles[i].init_life;

			particles[i].x = 0.0f;						// Initialize position
			particles[i].y = 50.0f;						
			particles[i].z = 0.0f;						

			theta = (rand() % 360) * PI/180;
			phi = 90 * PI / 180;
			rho = rand() % RHO;
			particles[i].v_x = float(sinf(phi) * cosf(theta) * rho);	// Initialize velocity
			particles[i].v_y = float(sinf(phi) * sin(theta) * rho);	
			particles[i].v_z = float(cosf(phi) * rho);
		}
	}
}

void TimerFunction(int value){
	Update();
	glutPostRedisplay();
	glutTimerFunc(10,TimerFunction,1);
}

// Setup the rendering state
void SetupRC(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("Particle system");

	// register callbacks
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);

	// Setup the rendering state
	SetupRC();
	InitPaticleSystem();	

	// enter GLUT event processing loop
	glutMainLoop();

	return 0;
}