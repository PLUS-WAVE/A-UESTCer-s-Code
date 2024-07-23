#include "lab2.h"

namespace LAB2_2
{
GLfloat xrot;
GLfloat yrot;
GLfloat xspeed;
GLfloat yspeed;
GLfloat z = -5.0f;
bool light = false;

GLuint filter;
GLuint texture[2];

int LoadGLTextures()
{
	for (int i = 0; i < 2; i++)
	{
		texture[i] = SOIL_load_OGL_texture("Data/glass.bmp",
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_INVERT_Y);
	}

	if (texture[0] == 0)
		return false;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(texture[1] == 0)
		return false;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}
//void glLight()
//{
//	glColorMaterial(GL_FRONT, GL_DIFFUSE);
//	glEnable(GL_COLOR_MATERIAL);
//
//	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	//GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	GLfloat position[] = { 0.0f, 0.0f, 2.0f, 1.0f };
//	//GLfloat gray[] = { 0.9f, 0.0f, 0.0f, 1.0f };
//	//glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
//	// glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
//	glLightfv(GL_LIGHT0, GL_POSITION, position);
//	glEnable(GL_LIGHT0);
//}

void changeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;

	gluPerspective(45.0f, aspectRatio, 1.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return false;
	}

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 0.0f, 0.0f, 2.0f, 1.0f };
	//GLfloat gray[] = { 0.9f, 0.0f, 0.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	return true;
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, z);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[filter]);

	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glutSwapBuffers();
	xrot += xspeed;
	yrot += yspeed;

}

void processSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_PAGE_UP:
			z -= 0.02f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			z += 0.02f;
			break;
		case GLUT_KEY_UP:
			xspeed -= 0.005f;
			break;
		case GLUT_KEY_DOWN:
			xspeed += 0.005f;
			break;
		case GLUT_KEY_LEFT:
			yspeed -= 0.005f;
			break;
		case GLUT_KEY_RIGHT:
			yspeed += 0.005f;
			break;
	}
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 'l':
			light = !light;
			if (!light)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			break;
		case 'f':
			filter += 1;
			if (filter > 1)
				filter = 0;
			printf("filter: %d\n", filter);
			break;
	}
}

int lab2(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Rotate Cube and Texture");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	InitGL();

	glutMainLoop();

	return 1;
}
}

