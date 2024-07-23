#include "lab5.h"

namespace LAB5
{

GLuint texture[1];

const int RESOLUTION = 70;
static float surface[6 * RESOLUTION * (RESOLUTION + 1)];
static float normal[6 * RESOLUTION * (RESOLUTION + 1)];

static int	wire_frame = 0;
static int	normals = 0;

static float	rotate_x = 30;
static float	rotate_y = 15;
static float	translate_z = 4;

static int	left_click = GLUT_UP;
static int	right_click = GLUT_UP;

static int	xold = 0;
static int	yold = 0;

float light_position[] = { 1.0, 1.0, 0.5, 0.0 };
float light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };


// 全局变量
int g_waveCount = 10;
Vector2 g_direction = {1, 0};

float g_wavelengthMin = 0.1f;
float g_wavelengthMax = 0.8f;
float g_steepnessMin = 0.1f;
float g_steepnessMax = 0.25f;


// 向量归一化函数
Vector2 normalize(Vector2 v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    return {v.x / length, v.y / length};
}

// 向量点乘函数
float dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

// 向量叉乘函数
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

void GerstnerWave_float(/* Inputs */  Vector3 positionIn, int waveCount, Vector2 direction, float speed,
	/* Inputs */  float wavelengthMin, float wavelengthMax,
	/* Inputs */  float steepnessMin, float steepnessMax,
	/* Outputs */ Vector3& positionOut, Vector3& normalOut)
{
	float x = 0, y = 0, z = 0;
	float bx = 0, by = 0, bz = 0;
	float tx = 0, ty = 0, tz = 0;
	positionOut = positionIn;

	unsigned int randX = 12345, randY = 67890;

	for (int i = 0; i < waveCount; i++)
	{
		float step = (float)i / (float)waveCount;

		randX = (randX * 1103515245) + 12345;
		randY = (randY * 1103515245) + 12345;

		Vector2 d = Vector2(sin((float)randX / 801571.f), cos((float)randY / 10223.f));
		d = normalize(d);

		step = pow(step, 0.75f);
		float wavelength = wavelengthMin + step * (wavelengthMax - wavelengthMin);
		float steepness = steepnessMin + step * (steepnessMax - steepnessMin);

		float k = 2 * M_PI / wavelength;
		float w = sqrt(9.8 * k);
		float a = steepness / k;

        Vector2 wavevector;
        wavevector.x = k * d.x;
        wavevector.y = k * d.y;

		float value = dot(Vector2(positionIn.x, positionIn.z), wavevector) - w * speed * 0.1f;

		x += d.x * a * cos(value);
		z += d.y * a * cos(value);
		y += a * sin(value);

		bx += d.x * d.x * k * a * -sin(value);
		by += d.x * k * a * cos(value);
		bz += d.x * d.y * k * a * -sin(value);

		tx += d.x * d.y * k * a * -sin(value);
		ty += d.y * k * a * cos(value);
		tz += d.y * d.y * k * a * -sin(value);
	}

	positionOut.x = positionIn.x + x;
	positionOut.z = positionIn.z + z;
	positionOut.y = y;

	Vector3 bitangent = Vector3(1 - std::min(1.f, bx), by, bz);
	Vector3 tangent = Vector3(tx, ty, 1 - std::min(1.f, tz));
	normalOut = cross(tangent, bitangent);
}


int LoadGLTextures()
{
	texture[0] = SOIL_load_OGL_texture("Data/reflection.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);

	if (texture[0] == 0)
	{
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	return 1;
}

void renderScene(void)
{
    const float t = glutGet(GLUT_ELAPSED_TIME) / 800.;
	const float delta = 2. / RESOLUTION;
    const unsigned int length = 2 * (RESOLUTION + 1);
    const float xn = (RESOLUTION + 1) * delta + 1;
    unsigned int i;
    unsigned int j;
    float x;
    float y;
    unsigned int indice;
    unsigned int preindice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0, 0, -translate_z);
    glRotatef(rotate_y, 1, 0, 0);
    glRotatef(rotate_x, 0, 1, 0);

    /* Vertices */
    for (j = 0; j < RESOLUTION; j++)
    {
        y = (j + 1) * delta - 1;
        for (i = 0; i <= RESOLUTION; i++)
        {
            indice = 6 * (i + j * (RESOLUTION + 1));

            x = i * delta - 1;
            Vector3 positionIn = Vector3(x, 0, y);
            Vector3 positionOut, normalOut;
            GerstnerWave_float(positionIn, g_waveCount, g_direction, t, g_wavelengthMin, g_wavelengthMax, g_steepnessMin, g_steepnessMax, positionOut, normalOut);
			surface[indice + 3] = positionOut.x;
            surface[indice + 4] = positionOut.y;
            surface[indice + 5] = positionOut.z;
            if (j != 0)
            {
                /* Values were computed during the previous loop */
                preindice = 6 * (i + (j - 1) * (RESOLUTION + 1));
                surface[indice] = surface[preindice + 3];
                surface[indice + 1] = surface[preindice + 4];
                surface[indice + 2] = surface[preindice + 5];
            }
            else
            {
                positionIn = Vector3(x, 0, -1);
                GerstnerWave_float(positionIn, g_waveCount, g_direction, t, g_wavelengthMin, g_wavelengthMax, g_steepnessMin, g_steepnessMax, positionOut, normalOut);
                surface[indice] = positionOut.x;
                surface[indice + 1] = positionOut.y;
                surface[indice + 2] = positionOut.z;
            }
            /* Normals */
            normal[indice] = normalOut.x;
            normal[indice + 1] = normalOut.y;
            normal[indice + 2] = normalOut.z;

            positionIn = Vector3(surface[indice + 3], 0, surface[indice + 5]);
            GerstnerWave_float(positionIn, g_waveCount, g_direction, t, g_wavelengthMin, g_wavelengthMax, g_steepnessMin, g_steepnessMax, positionOut, normalOut);
            normal[indice + 3] = normalOut.x;
            normal[indice + 4] = normalOut.y;
            normal[indice + 5] = normalOut.z;
        }
    }


    /* The ground */
    glDisable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor4f(1.0f, 0.9f, 0.7f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();

    glTranslatef(0, 0.2, 0);

    /* Render wireframe? */
    if (wire_frame != 0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    /* The water */
    glEnable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.8f, 1.0f, 0.8f);
    glBegin(GL_TRIANGLES);
    for (j = 0; j < RESOLUTION-1; j++)
    {
        for (i = 0; i < RESOLUTION-1; i++)
        {
            // Calculate indices for the two triangles forming a quad
            indice = 6 * (i + j * (RESOLUTION + 1));
            unsigned int next_i = (i + 1) % (RESOLUTION + 1);
            unsigned int next_j = (j + 1) % (RESOLUTION + 1);
            unsigned int indice_next_i = 6 * (next_i + j * (RESOLUTION + 1));
            unsigned int indice_next_j = 6 * (i + next_j * (RESOLUTION + 1));
            unsigned int indice_next_ij = 6 * (next_i + next_j * (RESOLUTION + 1));

            // First triangle
            // Vertices
            glTexCoord2f(i / (float)RESOLUTION, j / (float)RESOLUTION);
            glNormal3fv(&(normal[indice]));
            glVertex3fv(&(surface[indice]));

            glTexCoord2f((i + 1) / (float)RESOLUTION, j / (float)RESOLUTION);
            glNormal3fv(&(normal[indice_next_i]));
            glVertex3fv(&(surface[indice_next_i]));

            glTexCoord2f(i / (float)RESOLUTION, (j + 1) / (float)RESOLUTION);
            glNormal3fv(&(normal[indice_next_j]));
            glVertex3fv(&(surface[indice_next_j]));

            // Second triangle
            // Vertices
            glTexCoord2f((i + 1) / (float)RESOLUTION, j / (float)RESOLUTION);
            glNormal3fv(&(normal[indice_next_i]));
            glVertex3fv(&(surface[indice_next_i]));

            glTexCoord2f((i + 1) / (float)RESOLUTION, (j + 1) / (float)RESOLUTION);
            glNormal3fv(&(normal[indice_next_ij]));
            glVertex3fv(&(surface[indice_next_ij]));

            glTexCoord2f(i / (float)RESOLUTION, (j + 1) / (float)RESOLUTION);
            glNormal3fv(&(normal[indice_next_j]));
            glVertex3fv(&(surface[indice_next_j]));
        }
    }
    glEnd();

    /* Draw normals? */
    if (normals != 0)
    {
        glDisable(GL_TEXTURE_2D);
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        for (j = 0; j < RESOLUTION; j++)
            for (i = 0; i <= RESOLUTION; i++)
            {
                indice = 6 * (i + j * (RESOLUTION + 1));
                glVertex3fv(&(surface[indice]));
                glVertex3f(surface[indice] + normal[indice] / 50,
                    surface[indice + 1] + normal[indice + 1] / 50,
                    surface[indice + 2] + normal[indice + 2] / 50);
            }
        glEnd();
    }

    /* End */
    glutSwapBuffers();
    glutPostRedisplay();
}



void InitGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	LoadGLTextures();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		wire_frame = !wire_frame;
		break;
	case 'n':
		normals = !normals;
		break;
	case 'q':
	case 27:
		exit(0);
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		left_click = state;
	}
	if (GLUT_RIGHT_BUTTON == button)
	{
		right_click = state;
	}
	xold = x;
	yold = y;
}

void MotionFunc(int x, int y)
{
	if (GLUT_DOWN == left_click)
	{
		rotate_y = rotate_y + (y - yold) / 5.0;
		rotate_x = rotate_x + (x - xold) / 5.0;
		if (rotate_y > 90)
			rotate_y = 90;
		if (rotate_y < -90)
			rotate_y = -90;
		glutPostRedisplay();
	}
	if (GLUT_DOWN == right_click)
	{
		rotate_x = rotate_x + (x - xold) / 5.;
		translate_z = translate_z + (yold - y) / 50.;
		if (translate_z < 0.5)
			translate_z = 0.5;
		if (translate_z > 10)
			translate_z = 10;
		glutPostRedisplay();
	}
	xold = x;
	yold = y;
}


int lab5(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Lab5");

    InitGL();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MotionFunc);

	glutMainLoop();
	
	return 0;
}
}