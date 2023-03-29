#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;
float rotate_y = 0.0,
angle_x = 0.0, angle_y = 0.0, angle_z = 0.0,
camera_x = 0.0, /*camera_y = 2.0*/ camera_z = -5.0,
pos_x = 0.0, pos_y = 0.0, pos_z = 0.0, aroundtheworld = 0.0,
myscale = 1.0;
//Ініціалізація
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void MakeCube(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glFlush();
}

void MakePyramid()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	glFlush();
}

void timer(int) //використання таймеру
{
	glTranslatef(1.5, 2.5, 0.0);
	aroundtheworld += 1.0;
	if (aroundtheworld > 360.0) {
		aroundtheworld -= 360.0;
	}
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, 0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//Очистити матрицю
	glLoadIdentity();
	//Видова трансформація (камера)
	gluLookAt(camera_x, 2.0, camera_z, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0);
	
	glTranslatef(pos_x, pos_y, 1.0);
	glScalef(0.5, 0.5, 0.5);
	MakePyramid();
	glPushMatrix();
	glPopMatrix();

	glTranslatef(-3, 0.5, 0.0);
	glScalef(myscale, myscale, myscale);
	MakeCube();
	glPushMatrix();
	glPopMatrix();

	glTranslatef(3.5, 3.5, 0.0);
	glRotatef(aroundtheworld, 0.0, 1.0, 0.0);
	MakeCube();
	glPushMatrix();
	glPopMatrix();
	
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (pos_x > -1.6) {
			pos_x -= 0.15;
		}
	}

	else if (key == GLUT_KEY_UP)
	{
		if (pos_y < 1.75) {
			pos_y += 0.15;
		}
	}
	else if (key == GLUT_KEY_DOWN) {
		if (pos_y > -1.65) {
			pos_y -= 0.15;
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		if (pos_x < 2.0) {
			pos_x += 0.15;
		}
	}
	else if (key == GLUT_KEY_F1) {
		angle_x += 0.05;
		camera_x = sin(angle_x) * 5.0f;
		camera_z = cos(angle_x) * 5.0f;
		if (angle_x > 360.0) {
			angle_x -= 360.0;
		}
	}
	else if (key == GLUT_KEY_F2) {
		angle_x -= 0.05;
		camera_x = sin(angle_x) * 5.0f;
		camera_z = cos(angle_x) * 5.0f;
		if (angle_x < -360.0) {
			angle_x += 360.0;
		}
	}
	else if (key == GLUT_KEY_PAGE_UP) {
		myscale += 0.15;
	}
	else if (key == GLUT_KEY_PAGE_DOWN) {
		myscale -= 0.15;
	}
	glutPostRedisplay();
}
// Зміна розмірів вікна
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Labwork 2");
	glutTimerFunc(0, timer, 0); // запуск таймера анімації
	glutDisplayFunc(display);
	reshape(3, 3);
	init();

	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}