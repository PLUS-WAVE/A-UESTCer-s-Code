/**************************************************************************

  File: Lesson40.cpp
  
  Based on Jeff Molofee's Basecode Example

  Modified by Erkin Tunca for nehe.gamedev.net

**************************************************************************/
#include "lab4.h"

// 绳子
namespace LAB41
{
/*
  class RopeSimulation is derived from class Simulation (see Physics1.h). It simulates a rope with 
  point-like particles binded with springs. The springs have inner friction and normal length. One tip of 
  the rope is stabilized at a point in space called "Vector3D ropeConnectionPos". This point can be 
  moved externally by a method "void setRopeConnectionVel(Vector3D ropeConnectionVel)". RopeSimulation 
  creates air friction and a planer surface (or ground) with a normal in +y direction. RopeSimulation 
  implements the force applied by this surface. In the code, the surface is refered as "ground".
*/
RopeSimulation* ropeSimulation = new RopeSimulation(
													80,							// 80 Particles (Masses)
													0.05f,						// Each Particle Has A Weight Of 50 Grams
													500.0f,						// springConstant In The Rope
													0.05f,						// Normal Length Of Springs In The Rope
													0.2f,						// Spring Inner Friction Constant
													Vector3D(0, -9.81f, 0));	// Gravitational Acceleration

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	ropeSimulation->getMass(ropeSimulation->numOfMasses - 1)->vel.z = 10.0f;

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);									// Black Background
	glClearDepth (1.0f);													// Depth Buffer Setup
	glShadeModel (GL_SMOOTH);												// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Set Perspective Calculations To Most Accurate

	return true;										// Initialization Went OK
}

void Deinitialize (void)													// Any User DeInitialization Goes Here
{
	ropeSimulation->release();												// Release The ropeSimulation
	delete(ropeSimulation);													// Delete The ropeSimulation
	ropeSimulation = NULL;
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

        // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void Update ()											// Perform Motion Updates Here
{
	 ropeSimulation->operate(0.001);
}

void renderScene(void) {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();														// Reset The Modelview Matrix
	
	// Position Camera 40 Meters Up In Z-Direction.
	// Set The Up Vector In Y-Direction So That +X Directs To Right And +Y Directs To Up On The Window.
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);						

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// Clear Screen And Depth Buffer

	//update 
    Update();

	// Start Drawing The Rope.
	glColor3ub(255, 255, 0);												// Set Color To Yellow
	for (int a = 0; a < ropeSimulation->numOfMasses - 1; ++a)
	{
		Mass* mass1 = ropeSimulation->getMass(a);
		Vector3D* pos1 = &mass1->pos;

		Mass* mass2 = ropeSimulation->getMass(a + 1);
		Vector3D* pos2 = &mass2->pos;

		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3f(pos1->x, pos1->y, pos1->z);
			glVertex3f(pos2->x, pos2->y, pos2->z);
		glEnd();
	}
	// Drawing The Rope Ends Here.
	
	glFlush ();																// Flush The GL Rendering Pipeline

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if(key == 's'){
		Vector3D ropeConnectionVel;	
		ropeConnectionVel.x = 0.0;
		ropeConnectionVel.y = 0.0;
		ropeConnectionVel.z = 0.0;
		ropeSimulation->setRopeConnectionVel(ropeConnectionVel);
	}
	if (key == 27){
		// Application Is Finished
		Deinitialize();											// User Defined DeInitialization

		exit(0);
	}
}

void processSpecialKeys(int key, int x, int y) {

	Vector3D ropeConnectionVel;												// Create A Temporary Vector3D
    switch(key) {
        case GLUT_KEY_RIGHT :													// Is The Right Arrow Being Pressed?
           ropeConnectionVel.x += 1.0f;											// Add Velocity In +X Direction   
		   break;
        case GLUT_KEY_LEFT :                                                    // Is The Left Arrow Being Pressed?
			ropeConnectionVel.x -= 1.0f;										// Add Velocity In -X Direction
			break;
        case GLUT_KEY_UP :
			ropeConnectionVel.y += 1.0f;										// Add Velocity In +Y Direction
			break;
		case GLUT_KEY_DOWN :
			ropeConnectionVel.y -= 1.0f;										// Add Velocity In -Y Direction
			break;
		case GLUT_KEY_PAGE_UP:
			ropeConnectionVel.z += 1.0f;										// Add Velocity In +Z Direction
			break;
		case GLUT_KEY_PAGE_DOWN:
			ropeConnectionVel.z -= 1.0f;										// Add Velocity In -Z Direction
			break;		
    }

	ropeSimulation->setRopeConnectionVel(ropeConnectionVel);				// Set The Obtained ropeConnectionVel In The Simulation
	
}

int lab41(int argc, char **argv) {
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Rope Simulation");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

	if(!InitGL()){
		printf("Initialization Failed.");
		return false;
	}

    // process key
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
}

// 布料
namespace LAB4
{
ClothSimulation* clothSimulation = new ClothSimulation(
	30,						
	30,
	0.05f,					// Each Particle Has A Weight Of 50 Grams
	5000.0f,				// springConstant In The Rope
	0.4f,					// Normal Length Of Springs In The Rope
	7.0f,					// Spring Inner Friction Constant
	Vector3D(0, 0, 0)); // Gravitational Acceleration

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	//ropeSimulation->getMass(ropeSimulation->numOfMasses - 1)->vel.z = 10.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);									// Black Background
	glClearDepth(1.0f);														// Depth Buffer Setup
	glShadeModel(GL_SMOOTH);												// Select Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Set Perspective Calculations To Most Accurate
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//clothSimulation->changeShape();

	return true;
}


void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Update()											// Perform Motion Updates Here
{
	clothSimulation->operate(0.0015);
}

void renderScene(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Update();

	glColor3ub(226, 226, 226);

	for (int i = 0; i < clothSimulation->Xlen - 1; ++i)
	{
		for (int j = 0; j < clothSimulation->Ylen - 1; ++j)
		{
			Mass* mass1 = clothSimulation->getMass(i, j);
			Vector3D* pos1 = &mass1->pos;

			if (i < clothSimulation->Xlen - 2)
			{
				Mass* mass2 = clothSimulation->getMass(i + 1, j);
				Vector3D* pos2 = &mass2->pos;

				Vector3D diff = mass1->pos - mass2->pos;
				float distance = diff.length();
				float tension = abs(distance - 0.4f);

				float colorIntensity = 0.005 / tension;

				glColor3f(220, colorIntensity*0.5, 150);

				glLineWidth(2);
				glBegin(GL_LINES);
				glVertex3f(pos1->x, pos1->y, pos1->z);
				glVertex3f(pos2->x, pos2->y, pos2->z);
				glEnd();
			}

			if (j < clothSimulation->Ylen - 2)
			{
				Mass* mass3 = clothSimulation->getMass(i, j + 1);
				Vector3D* pos3 = &mass3->pos;

				Vector3D diff = mass1->pos - mass3->pos;
				float distance = diff.length();
				float tension = abs(distance - 0.4f);

				float colorIntensity = 0.005 / tension;

				glColor3f(220, colorIntensity*0.5, 150);

				glLineWidth(2);
				glBegin(GL_LINES);
				glVertex3f(pos1->x, pos1->y, pos1->z);
				glVertex3f(pos3->x, pos3->y, pos3->z);
				glEnd();
			}
		}
	}

	glFlush();

	glutSwapBuffers();
}


// 鼠标状态和位置
int mouseState = 0;
int mouseX = 0, mouseY = 0;
int selectedMassX = 0, selectedMassY = 0;


// 鼠标事件处理函数
void mouse(int button, int state, int x, int y)
{
	// 检查是否是左键
	if (button == GLUT_LEFT_BUTTON)
	{
		// 检查按钮状态
		if (state == GLUT_DOWN)
		{
			// 按下鼠标左键，记录状态和位置
			mouseState = 1;
			mouseX = x;
			mouseY = y;

			// 获取当前的模型视图矩阵、投影矩阵和视口
			GLdouble modelView[16], projection[16];
			GLint viewport[4];
			glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glGetIntegerv(GL_VIEWPORT, viewport);

			// 将鼠标的屏幕坐标转换为模拟空间的坐标
			GLdouble posX, posY, posZ;
			gluUnProject(x, viewport[3] - y, 1, modelView, projection, viewport, &posX, &posY, &posZ);

			// 找到最近的质点
			float minDist = FLT_MAX;
			for (int i = 0; i < clothSimulation->Xlen; ++i)
			{
				for (int j = 0; j < clothSimulation->Ylen; ++j)
				{
					Mass* mass = clothSimulation->getMass(i, j);
					float dx = posX - mass->pos.x;
					float dy = posY - mass->pos.y;
					float dz = posZ - mass->pos.z;
					float dist = sqrt(dx * dx + dy * dy + dz * dz);
					if (dist < minDist)
					{
						minDist = dist;
						selectedMassX = i;
						selectedMassY = j;
					}
				}
			}
		}
		else
		{
			// 释放鼠标左键，重置状态
			mouseState = 0;
		}
	}
}


// 鼠标移动事件处理函数
void motion(int x, int y)
{
	// 如果鼠标左键被按下
	if (mouseState == 1)
	{
		// 获取当前的模型视图矩阵、投影矩阵和视口
		GLdouble modelView[16], projection[16];
		GLint viewport[4];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);

		// 将鼠标的屏幕坐标转换为模拟空间的坐标
		GLdouble posX, posY, posZ;
		gluUnProject(x, viewport[3] - y, 0, modelView, projection, viewport, &posX, &posY, &posZ);

		// 更新模拟的位置
		Mass* selectedMass = clothSimulation->getMass(selectedMassX, selectedMassY);
		float dx = posX - selectedMass->pos.x;
		float dy = posY - selectedMass->pos.y;
		float dz = posZ - selectedMass->pos.z;

		//// 限制最大移动距离
		//float maxDist = 2.0f;
		//float dist = sqrt(dx * dx + dy * dy + dz * dz);
		//if (dist > maxDist)
		//{
		//	dx *= maxDist / dist;
		//	dy *= maxDist / dist;
		//	dz *= maxDist / dist;
		//}

		selectedMass->pos.x += dx * 0.2;
		selectedMass->pos.y += dy * 0.2;
		selectedMass->pos.z += dz * 0.2;

		// 更新鼠标位置
		mouseX = x;
		mouseY = y;
	}
}



int lab4(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Rope Simulation");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();

	return 0;
}
}