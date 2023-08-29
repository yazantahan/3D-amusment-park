#include <glut.h>
#include <math.h>
#include <iostream>

#include <mmsystem.h>

using namespace std;

//include this library to import images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float OBJ_SPEED = 0.1;
float OBJ_ROTATE = 0.5;

float chairObj = 0;
float chairObj1 = 10;
float chairObj2 = 20;
float chairObj3 = 30;
float chairObj4 = 40;

float cchairObj = 0;
float cchairObj1 = 50;
float cchairObj2 = 100;
float cchairObj3 = 150;
float cchairObj4 = 200;

float pchairObj = 0;

double th = 0;
double EX = 0;
double EZ = 0;
double EY = 0;

//defining a global matrix to store the texture objects
int tex[24];

//use the function to load RGB images
GLuint LoadTexture(const char imagename[])
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//GL_ADD, GL_MODULATE, GL_DECAL, GL_BLEND, GL_REPLACE.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imagename, &width, &height, &nrChannels, 0);
	if (data)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//MessageBox(NULL, "Failed to load texture", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
	stbi_image_free(data);


	return textureID;
}

//use this function to load RGBA (.png) images
GLuint LoadTexture1(const char imagename[])
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//GL_ADD, GL_MODULATE, GL_DECAL, GL_BLEND, GL_REPLACE.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imagename, &width, &height, &nrChannels, 0);
	if (data)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//MessageBox(NULL, "Failed to load texture", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
	stbi_image_free(data);


	return textureID;
}

void drawBox(GLfloat size, GLenum type, int tex_id)
{
	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2d(1, 1);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2d(0, 1);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2d(0, 0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2d(1, 0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void glutSolidCubeTex(GLdouble size, int tex_id)
{
	drawBox(size, GL_QUADS, tex_id);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VK_ESCAPE: /* Escape key */
		exit(0);
		break;
	case '3':
		OBJ_SPEED += 0.05;
		break;
	case '1':
		OBJ_SPEED -= 0.05;
		break;
	case '6':
		OBJ_ROTATE += 0.05;
		break;
	case '4':
		OBJ_ROTATE -= 0.05;
		break;
	default:
		break;
	}
}

void Special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		th += 0.05;
		break;
	case GLUT_KEY_LEFT:
		th -= 0.05;
		break;
	case GLUT_KEY_DOWN:
		EX = EX - cos(th);
		EZ = EZ - sin(th);
		break;
	case GLUT_KEY_UP:
		EX = EX + cos(th);
		EZ = EZ + sin(th);
		break;
	case GLUT_KEY_PAGE_UP:
		EY += 1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		EY -= 1;
		break;
	default:
		break;
	}
}

void InitGL(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	//don't forget to enable texturing
	glEnable(GL_TEXTURE_2D);

	//loading the sky box images
	//you can download skybox images from here: http://www.humus.name/index.php?page=Textures 
	tex[0] = LoadTexture("Data/negy.jpg");
	tex[1] = LoadTexture("Data/posy.jpg");
	tex[2] = LoadTexture("Data/posx.jpg");
	tex[3] = LoadTexture("Data/posz.jpg");
	tex[4] = LoadTexture("Data/negx.jpg");
	tex[5] = LoadTexture("Data/negz.jpg");

	//loading other images to use on the objects in the built space
	tex[7] = LoadTexture("Data/CGL_GRASS.jpg");
	tex[8] = LoadTexture("Data/CGL_WOOD2.jpg");
	tex[9] = LoadTexture("Data/CGL_GRASS2.jpg");
	tex[10] = LoadTexture("Data/Wood.bmp");
	tex[11] = LoadTexture("Data/CGL_BOOTH_COUNTER.jpg");
	tex[12] = LoadTexture("Data/CGL_COUNTER.png");
	tex[13] = LoadTexture("Data/CGL_STEEL.jpg");
	tex[14] = LoadTexture("Data/CGL_STEEL1.jpg");
	tex[15] = LoadTexture("Data/Crate.bmp");
	tex[16] = LoadTexture("Data/CGL_ROPE.jpg");

	//Importing Background Sound
	PlaySound(TEXT("sounds/CGL_BACKGROUND_NOISE.wav"), 0, SND_ASYNC | SND_LOOP);
}

//this function is the cube that represents the skybox, it consists of six quads and each quad is set to bind with a texture object
void SkyBoxCube()
{
	float P1[] = { 1, -1,  1 };
	float P2[] = { 1, -1, -1 };
	float P3[] = { -1,-1, -1 };
	float P4[] = { -1,-1,  1 };
	float P5[] = { 1, 1,  1 };
	float P6[] = { 1, 1, -1 };
	float P7[] = { -1, 1, -1 };
	float P8[] = { -1, 1,  1 };
	glColor3f(1, 1, 1);
	//bottom
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3fv(P1);
	glTexCoord2f(0, 0); glVertex3fv(P2);
	glTexCoord2f(0, 1); glVertex3fv(P3);
	glTexCoord2f(1, 1); glVertex3fv(P4);
	glEnd();
	//top
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(P6);
	glTexCoord2f(1, 1); glVertex3fv(P5);
	glTexCoord2f(1, 0); glVertex3fv(P8);
	glTexCoord2f(0, 0); glVertex3fv(P7);
	glEnd();
	//right
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P1);//1
	glTexCoord2f(1, 0); glVertex3fv(P5);//2
	glTexCoord2f(0, 0); glVertex3fv(P6);//6
	glTexCoord2f(0, 1); glVertex3fv(P2);//5
	glEnd();
	//front
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P2);//2
	glTexCoord2f(1, 0); glVertex3fv(P6);//3
	glTexCoord2f(0, 0); glVertex3fv(P7);//7
	glTexCoord2f(0, 1); glVertex3fv(P3);//6
	glEnd();
	//left
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P3);//3
	glTexCoord2f(1, 0); glVertex3fv(P7);//4
	glTexCoord2f(0, 0); glVertex3fv(P8);//8
	glTexCoord2f(0, 1); glVertex3fv(P4);//7
	glEnd();
	//back
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1); glVertex3fv(P4);//4
	glTexCoord2f(1, 0); glVertex3fv(P8);//1
	glTexCoord2f(0, 0); glVertex3fv(P5);//5
	glTexCoord2f(0, 1); glVertex3fv(P1);//8
	glEnd();
}

//this function is used to enable & disable features needed to use the skybox
void SkyBoxFunc()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	SkyBoxCube();
	glEnable(GL_DEPTH_TEST);
	//you decide if you want to stop the texture calculation and turn on lighting after the skybox or not
	glDisable(GL_TEXTURE_2D);
}

void createChair() {
	glNewList(1, GL_COMPILE);
	GLUquadric* g = gluNewQuadric();
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);
	glScalef(0.08, 1.5, 0.08);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 0.0f);
	glColor3d(0.0, 1.0, 0.0);
	glScalef(0.08, 1.5, 0.08);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -1.75, 3.0f);
	glColor3d(0.0, 1.0, 0.0);
	glScalef(0.08, 0.75, 0.08);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0f, -1.75, 3.0f);
	glColor3d(0.0, 1.0, 0.0);
	glScalef(0.08, 0.75, 0.08);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0.25, 1.75);
	glColor3d(0.0, 1.0, 0.0);
	glScalef(1, 0.05, 0.75);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 4, 0);
	glColor3d(0.0, 1.0, 0.0);
	glScalef(1.05, 0.5, 0.1);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0); 
	glDisable(GL_TEXTURE_2D);
	glEndList();


}

void createTable() {
	glNewList(2, GL_COMPILE);
		GLUquadric* g = gluNewQuadric();

		glEnable(GL_TEXTURE_2D);
		g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[10]);
		glPushMatrix();
			glTranslatef(0, 0, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(g, 0.45, 0.45, 7.75, 10, 10);
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			gluDisk(g, 0, 5.3, 25, 25);
			gluCylinder(g, 5.3, 5.3, 0.6, 25, 25);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	glEndList();

}

void createWheelChair() {
	glNewList(6, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3d(1.0, 0.5, 0.0);
	glScalef(0.08, 1, 2.3);
	glTranslatef(0.0, 0.41, 0.0);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 0.5, 0.0);
	glTranslatef(2.55, -2.1, -0.15);
	glScalef(1, 0.15, 2.35);
	glutSolidCubeTex(5, tex[10]);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createWheelBase() {
	glNewList(7, GL_COMPILE);
	GLUquadric* g;
	g = gluNewQuadric();
	gluQuadricTexture(g, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[14]);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 11.25, 0);
	glScalef(1.8, 1.8, 1.8);
	glutSolidTorus(0.3, -6.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 11.25, 10);
	glScalef(1.8, 1.8, 1.8);
	glutSolidTorus(0.3, -6.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 10.75, 0);
	glScalef(0.1, 0.1, 0.2);
	gluCylinder(g, 5.3, 5.3, 50, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11.25, 10.75, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.45);
	gluCylinder(g, 5.3, 5.3, 50, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11.25, 10.75, 10);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.45);
	gluCylinder(g, 5.3, 5.3, 50, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3.3, -4.15);
	glRotatef(-73, 1, 0, 0);
	glScalef(-0.1, 0.1, 0.3);
	gluCylinder(g, 5.3, 5.3, 50, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3.15, 14.35);
	glRotatef(-108, 1, 0, 0);
	glScalef(0.1, 0.1, 0.3);
	gluCylinder(g, 5.3, 5.3, 50, 10, 10);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createLampPost() {
	glNewList(4, GL_COMPILE);
	GLUquadric* g;
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.6, 0.06, 0.6);
	glutSolidCubeTex(5, tex[13]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.45, 0.1, 0.45);
	glutSolidCubeTex(5, tex[13]);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	g = gluNewQuadric();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.3, 0.0, 0.7);
	glScalef(0.1, 0.1, -10.8);
	glColor3f(0.0, 0.0, 0.0);
	gluDisk(g, 0, 5.3, 25, 25);
	gluCylinder(g, 5.3, 5.3, 0.6, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.25, 6, 0.1);
	glScalef(0.2, 0.2, 0.2);
	glutSolidSphere(5, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glEndList();
}

void createCarouselBase() {
	glNewList(3, GL_COMPILE);
	GLUquadric* g;
	g = gluNewQuadric();
	gluQuadricTexture(g, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[10]);

	glPushMatrix();
	glColor3f(0.9, 0.5, 0.1);
	glTranslatef(0, 15.8, 0);
	glScalef(1, 2.75, 1);
	glRotatef(90, 1, 0, 0);
	gluCylinder(g, 0.45, 0.45, 7.75, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.5, 0.1);
	glTranslatef(0, 15.5, 0);
	glScalef(3, 2.05, 3);
	glRotatef(90, 1, 0, 0);
	gluDisk(g, 0, 5.3, 25, 25);
	gluCylinder(g, 5.3, 5.3, 0.6, 25, 25);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createCarouselChair() {
	glNewList(5, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3d(1.0, 0.5, 0.0);
	glScalef(0.05, 1.1, 0.9);
	glTranslatef(0.0, 0.41, 0.0);
	glutSolidCubeTex(5, tex[11]);
	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 0.5, 0.0);
	glTranslatef(2.55, -2.1, -0.15);
	glScalef(1, 0.1, 1);
	glutSolidCubeTex(5, tex[11]);
	glPopMatrix();

	GLUquadric* g;
	g = gluNewQuadric();
	gluQuadricTexture(g, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, tex[16]);
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(0, 3.2, -2.05);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.05, 0.05, 20.75);
	gluCylinder(g, 5, 5, 0.6, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(0, 3.2, 2.05);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.05, 0.05, 20.75);
	gluCylinder(g, 5, 5, 0.6, 25, 25);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createPirateShipBase() {
	glNewList(8, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		GLUquadric* g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[13]);
		glPushMatrix();
			glTranslatef(0, -5.45, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(27, 0, 1, 0);
			glScalef(0.25, 0.25, 24.25);
			glColor3f(1, 0, 0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -5.45, 25.3);
			glRotatef(-90, 1, 0, 0);
			glRotatef(27, 0, 1, 0);
			glScalef(0.25, 0.25, 24.25);
			glColor3f(1, 0, 0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(45, -7.8, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-24, 0, 1, 0);
			glScalef(0.25, 0.25, 25.55);
			glColor3f(1, 0, 0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(45, -7.8, 25.3);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-24, 0, 1, 0);
			glScalef(0.25, 0.25, 25.55);
			glColor3f(1, 0, 0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(23.4, 38.1, -1.2);
			glScalef(1, 0.3, 14.2);
			glColor3f(1, 0, 0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createPirateShip() {
	glNewList(9, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[15]);
		glPushMatrix();
		glScalef(2.6, 2.2, 1.4);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);
		glVertex3f(-5,0,0);
		glTexCoord2d(0, 1);
		glVertex3f(5,0,0);
		glTexCoord2d(0, 0);
		glVertex3f(8,5,0);
		glTexCoord2d(1, 0);
		glVertex3f(-8,5,0);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, tex[15]);
		glPushMatrix();
		glScalef(2.6, 2.2, 1.4);
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);
		glVertex3f(8, 5, 0);

		glTexCoord2d(0, 1);
		glVertex3f(8, 5, 7.2);

		glTexCoord2d(0, 0);
		glVertex3f(5, 0, 7.2);

		glTexCoord2d(1, 0);
		glVertex3f(5, 0, 0);

		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, tex[15]);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 10.0);
		glScalef(2.6, 2.2, 1.4);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);
		glVertex3f(-5, 0, 0);

		glTexCoord2d(0, 1);
		glVertex3f(5, 0, 0);

		glTexCoord2d(0, 0);
		glVertex3f(8, 5, 0);

		glTexCoord2d(1, 0);

		glVertex3f(-8, 5, 0);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, tex[15]);
		glPushMatrix();
		glScalef(2.6, 2.2, 1.4);
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);
		glVertex3f(-8, 5, 0);

		glTexCoord2d(0, 1);
		glVertex3f(-8, 5, 7.2);

		glTexCoord2d(0, 0);
		glVertex3f(-5, 0, 7.2);

		glTexCoord2d(1, 0);
		glVertex3f(-5, 0, 0);

		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, tex[15]);
		glPushMatrix();
		glScalef(2.6, 2.2, 1.4);
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_QUADS);
		glTexCoord2d(1, 1);
		glVertex3f(5, 0, 7.2);

		glTexCoord2d(0, 1);
		glVertex3f(-5, 0, 7.2);

		glTexCoord2d(0, 0);
		glVertex3f(-5, 0, 0);

		glTexCoord2d(1, 0);

		glVertex3f(5, 0, 0);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		GLUquadric* g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, tex[14]);
		glPushMatrix();
			glTranslatef(1.5, 30, 5);
			glRotatef(90, 1, 0, 0);
			glScalef(0.2, 0.2, 14);
			glColor3f(1.0, 0.0, 0.0);
			gluCylinder(g, 5, 5, 2, 25, 25);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_TEXTURE_2D);

	glEndList();
}

void createTree(GLUquadric* g) {

	glNewList(10, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[8]);
			glPushMatrix();
				glTranslatef(0, -5.4, 0);
				glRotatef(-90, 1, 0, 0);
				glScalef(0.3, 0.3, 9.8);
			gluCylinder(g, 5, 5, 2, 20, 20);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[9]);
			glPushMatrix();
				glTranslatef(0, 6, 0);
				glRotatef(-90, 1, 0, 0);
				glScalef(1, 1, 9);
				gluCylinder(g, 5, 0, 2, 20, 20);
				gluDisk(g, 0, 5, 50, 50);
			glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		g = gluNewQuadric();
		gluQuadricTexture(g, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[9]);
			glPushMatrix();
				glTranslatef(0, 10, 0);
				glRotatef(-90, 1, 0, 0);
				glScalef(1, 1, 9);
				gluCylinder(g, 5, 0, 2, 20, 20);
				gluDisk(g, 0, 5, 50, 50);
			glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createCafeCounter() {
	glNewList(11, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(0, -0.2, 0);
			glScalef(4, 2, 3);

			glColor3f(1.0, 0.0, 0.0);
			glutSolidCubeTex(5, tex[11]);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 9.5, 0);
			glScalef(2, 4.5, 2.7);

			glColor3f(0.0, 0.5, 1);
			glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 19.7, 0);
			glScalef(4, 2, 3);

			glColor3f(1.0, 0.0, 0.0);
			glutSolidCubeTex(5, tex[11]);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-8, 20, 0);
			glScalef(1, 1, 0.8);
			glutSolidCubeTex(5, tex[12]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void createTicketBooth() {
	glNewList(12, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glScalef(4, 2, 3);

	glColor3f(1.0, 0.0, 0.0);
	glutSolidCubeTex(5, tex[11]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 9.5, 0);
	glScalef(2, 4.5, 2.7);

	glColor3f(0.0, 0.5, 1);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 19.7, 0);
	glScalef(4, 2, 3);

	glColor3f(1.0, 0.0, 0.0);
	glutSolidCubeTex(5, tex[11]);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
}

void ReSizeGLScene(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	 
	//calling the skybox before the camera for it to move with the camera, therefor the camera can't leave the skybox
	//we also set it to be rotating with same angle of the camera to be able to see all the faces of the cube 
	glPushMatrix();
	glRotatef(th * 180 / 3.14, 0, 1, 0);
	SkyBoxFunc();
	glPopMatrix();

	gluLookAt(EX, EY, EZ, EX + cos(th), EY, EZ + sin(th), 0, 1, 0);

	GLUquadric* g = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);

	//Creating Chair
	createChair();
	
	//Creating Table
	createTable();
	
	//Creating Light Bump
	createLampPost();
	
	//Creating Both chair and Base for Ferris Wheel game
	createWheelChair();
	createWheelBase();
	
	//Creating Both chair and base for Carousel Wheel game
	createCarouselBase();
	createCarouselChair();

	//Creating Both ship and base for Pirate Ship game
	createPirateShipBase();
	createPirateShip();

	//Creating Tree
	createTree(g);

	//Create Cafe's Counter
	createCafeCounter();

	createTicketBooth();

	glBindTexture(GL_TEXTURE_2D, tex[7]);
	glPushMatrix();
	glColor4f(0.8, 0.8, 0.8, 0.5);
	glTranslatef(0, -5, 0);
	glBegin(GL_QUADS); 
	glTexCoord2d(1, 1);
	glVertex3d(400, 0, -400);
	glTexCoord2d(0, 1); 
	glVertex3d(400, 0, 400);
	glTexCoord2d(0, 0); 
	glVertex3d(-400, 0, 400);
	glTexCoord2d(1, 0); 
	glVertex3d(-400, 0, -400);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	

	//Creating a Fully-Ferris Wheel Object
	glPushMatrix();
	glTranslatef(20, -3.25, 30);
	glCallList(7);
	
	glPushMatrix();
	glTranslatef(-1.65, 12.05, 5);
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(10 * cos(chairObj1), 10 * sin(chairObj1), 0);
		glScalef(1, 1, 0.85);
		glCallList(6);
		glPopMatrix();
	
		chairObj1 += 0.005f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(10 * cos(chairObj), 10 * sin(chairObj), 0);
		glScalef(1, 1, 0.85);
		glCallList(6);
		glPopMatrix();
	
		chairObj += 0.005f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(10 * cos(chairObj2), 10 * sin(chairObj2), 0);
		glScalef(1, 1, 0.85);
		glCallList(6);
		glPopMatrix();
	
		chairObj2 += 0.005f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(10 * cos(chairObj3), 10 * sin(chairObj3), 0);
		glScalef(1, 1, 0.85);
		glCallList(6);
		glPopMatrix();
	
		chairObj3 += 0.005f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(10 * cos(chairObj4), 10 * sin(chairObj4), 0);
		glScalef(1, 1, 0.85);
		glCallList(6);
		glPopMatrix();
	
		chairObj4 += 0.005f;
	}
	glPopMatrix();
	
	glPopMatrix();
	
	//Creating a Fully-Carousel Wheel Object
	glPushMatrix();

	glTranslatef(20, 0, -30);
	glCallList(3);
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glRotatef(cchairObj3 * 10, 0, 1, 0);
		glTranslatef(10 * sin(cchairObj), 0, 10 * cos(cchairObj));
		glCallList(5);
		glPopMatrix();
	
		cchairObj += 0.01f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glRotatef(cchairObj * 10, 0, 1, 0);
		glTranslatef(10 * sin(cchairObj1), 0, 10 * cos(cchairObj1));
		glCallList(5);
		glPopMatrix();
	
		cchairObj1 += 0.01f;
	}

	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glRotatef(cchairObj1 * 10, 0, 1, 0);
		glTranslatef(10 * sin(cchairObj2), 0, 10 * cos(cchairObj2));
		glCallList(5);
		glPopMatrix();

		cchairObj2 += 0.01f;
	}
	
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glRotatef(cchairObj2 * 10, 0, 1, 0);
		glTranslatef(10  * sin(cchairObj3), 0, 10 * cos(cchairObj3));
		glCallList(5);
		glPopMatrix();
	
		cchairObj3 += 0.01f;
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 0, 0);
	glCallList(8);
	
	glTranslatef(22.2, 8, 5.8);
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslatef(0, 32, 0);
		glRotatef(90 * sin(pchairObj), 0, 0, 1);
		glTranslatef(0, -32, 0);
		glCallList(9);
		glPopMatrix();

		pchairObj += 0.001f;
	}
	glPopMatrix();
 
	glNewList(13, GL_COMPILE);
		glPushMatrix();
		glCallList(2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -2.5, -8.2);
		glCallList(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, -2.5, 8.2);
		glRotatef(-180, 0, 1, 0);
		glCallList(1);
		glPopMatrix();
	glEndList();

	glPushMatrix();
		glTranslatef(175, -2, -88);
		glScalef(0.4, 0.7, 2.5);
		glCallList(11);
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
		glPushMatrix();
				glTranslatef((i * 15) + 50, 0, j * 20);
				glTranslatef(55, 0.7, -99);
				glRotatef(-55, 0, 1, 0);
				glCallList(13);
		glPopMatrix();
		}
	}
	glPopMatrix();

	//Creating Lamp Posts
	glPushMatrix();
	glTranslatef(0, 0, 100);
	glCallList(10);
	glTranslatef(50, 0, 0);
	glCallList(10);
	glTranslatef(50, 0, 0);
	glCallList(10);
	glTranslatef(50, 0, 0);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-30, 0, 100);
	glCallList(10);
	glTranslatef(0, 0, -50);
	glCallList(10);
	glTranslatef(0, 0, -50);
	glCallList(10);
	glTranslatef(0, 0, -50);
	glCallList(10);
	glTranslatef(0, 0, -50);
	glCallList(10);
	glTranslatef(0, 0, -20);
	glCallList(10);
	glPopMatrix();
	glPushMatrix(); 
	glTranslatef(250, 0, -94);
	glCallList(10);
	for (int i = 0; i < 6; i++) {
		glTranslatef(0, 0, 30);
		glCallList(10);
	}
	glTranslatef(-30, 0, 0);
	glCallList(10);
	glTranslatef(-30, 0, 0);
	glCallList(10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -130);
	glCallList(10);
	for (int i = 0; i < 5; i++) {
		glTranslatef(50, 0, 0);
		glCallList(10);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(177.5, -2.6, -53);
	glScalef(1.7, 2, 1.7);
	glCallList(4);
	glTranslatef(-30, 0, 0);
	glCallList(4);
	glTranslatef(-30, 0, 0);
	glCallList(4);
	glTranslatef(0, 0, -20);
	glCallList(4);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-18, -2.6, 0);
	glScalef(1.7, 2, 1.7);
	glCallList(4);
	glTranslatef(30, 0, 0);
	glCallList(4);
	glTranslatef(30, 0, -15);
	glCallList(4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(55, -2.0, 25);
	glScalef(1.7, 2, 1.7);
	glCallList(4);
	glTranslatef(0, 0, 15);
	glCallList(4);
	glTranslatef(0, 0, 15);
	glCallList(4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.7, 12.15);
	glScalef(0.6, 0.45, 0.7);
	glCallList(12);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); // Use single display buffer.
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Amusement Park");
	InitGL();
	glutReshapeFunc(ReSizeGLScene);
	glutDisplayFunc(DrawGLScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}