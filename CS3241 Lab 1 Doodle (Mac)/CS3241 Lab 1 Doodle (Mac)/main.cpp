// Name: Tang Xiao Di Wendy REALLLL
// Extra functions I used: glLineStipple AND glLineWidth(4) and others too!
// CS3241 Assignment 1: Doodle#include <cmath>

#include <iostream>
#define GL_SILENCE_DEPRECATION

#ifdef _WIN32
#include <Windows.h>
#include "GL/glut.h"
#define M_PI 3.141592654
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <cstdlib>
#include <ctime>
#endif

using namespace std;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

void loopN(int n, float angleOffset, void (*drawFn)()) {
    for (int i = 0; i < n; ++i) {
        glPushMatrix();
        float angle = i * 360.0f / n + angleOffset;
        glRotatef(angle, 0, 0, 1);
        drawFn();
        glPopMatrix();
    }
}

void drawDot() {
    glBegin(GL_POINTS);
    glVertex2d(0, 0);
    glEnd();
}

void drawDotInMiniOrbit() {
    glPushMatrix();
    glTranslatef(0, 0.1, 0);
    drawDot();
    glPopMatrix();
}

void drawDotCircle() {
    loopN(6, 0, drawDotInMiniOrbit);
}

void drawDotCircleInOrbit() {
    glPushMatrix();
    glTranslatef(0, 3.6, 0);
    drawDotCircle();
    glPopMatrix();
}

void drawDotLoopLoop() {
    loopN(4, 45, drawDotCircleInOrbit);
}

void drawSingleDotOrbit() {
    glPushMatrix();
    glTranslatef(0, 3.6, 0);
    drawDot();
    glPopMatrix();
}

void drawSingleDotLoop() {
    loopN(16, 0, drawSingleDotOrbit);
}

void drawCircle(float x, float y, float radius, int degree = 360) {
    glBegin(GL_POLYGON);
    float offset = (180-degree)/2 * M_PI / 180;
    for (int i = 0; i < degree; ++i) {
        float angle = i * M_PI / 180.0;
        glVertex2f(x + cos(angle+offset) * radius, y + sin(angle+offset) * radius);
    }
    glEnd();
}

void drawArc(float x, float y, float radius, float degree) {
    glBegin(GL_LINE_STRIP);
    float offset = (180-degree)/2 * M_PI / 180;
    for (int i = 0; i < degree; i++) {
        float angle = i * M_PI / 180.0;
        glVertex2f(x + cos(angle+offset) * radius, y + sin(angle+offset) * radius);
    }
    glEnd();
}

void drawArcPattern(float x, float y, float radius, float degree) {
    float offset = (180-degree)/2 * M_PI / 180;
    float angle = degree * M_PI / 180;
    drawCircle(x,y,radius,degree);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x,y);
    glVertex2f(x + cos(angle+offset) * radius, y + sin(angle+offset) * radius);
    glVertex2f(x + cos(offset) * radius, y + sin(offset) * radius);
    glEnd();
    for (int i = 1; i < 4; i++) {
        drawArc(x, y, radius + i * 0.3, degree);
    }
}

void drawWagaraLine() {
    glPushMatrix();
    for (int i = 0; i < 8; i++) {
        drawArcPattern(0-i*2, 0, 1, 100);
    }
    for (int i = 1; i < 8; i++) {
        drawArcPattern(0+i*2, 0, 1, 100);
    }
    glPopMatrix();
}

void drawWagaraLines() {
    float scaling = 5;
    glPushMatrix();
    glTranslatef(0, -5, 0);
    for (int i = 0; i < 7; i=i+2) {
        glColor4f(1-(i)*0.02, 0.65+(i)*0.02, 0.9-(i)*0.01, 0.05+(i*i)*0.02);
        drawWagaraLine();
        glTranslatef(1, -1, 0);
        glScalef(1.1,1.1,1);
        scaling = scaling * 1.1;
        glLineWidth(scaling);
        glColor4f(1-(i+1)*0.02, 0.65+(i+1)*0.02, 0.9-(i+1)*0.01, 0.05+(i+1)*(i+1)*0.02);
        drawWagaraLine();
        glTranslatef(-1, -1, 0);
        glScalef(1.1,1.1,1);
        scaling = scaling * 1.1;
        glLineWidth(scaling);
    }
    glPopMatrix();
}

void drawGlow(int n = 8) {
    glPushMatrix();
    for (int i = 0; i < n; i++) {
        glScalef(1.2, 1.2, 1.1);
        drawCircle(0, 0, 1);
    }
    glPopMatrix();
}

void drawParabola(float a = 1.0f, float b = 0.0f, float c = 0.0f, float xMin = -5.0f, float xMax = 5.0f, float step = 0.1f) {
    glBegin(GL_LINE_STRIP);
    for (float x = xMin; x <= xMax; x += step) {
        float y = a * x * x + b * x + c;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawParabolaInOrbit() {
    glPushMatrix();
    glTranslatef(3.3, 0, 0);
    glRotatef(90,0,0,1);
    drawParabola(1, 0, 0, -1, 1, 0.02);
    glPopMatrix();
}

void drawInnerParabolaInOrbit() {
    glPushMatrix();
    glTranslatef(2.5, 0, 0);
    glRotatef(90,0,0,1);
    glScalef(0.7,0.6,1);
    glColor3f(1, 0.7, 0.6);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    drawParabola(1, 0, 0, -1, 1, 0.02);
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
}

void drawPetals(int n = 8) {
    glColor3f(1,0.87, 0.78);
    loopN(n, 0, drawParabolaInOrbit);
    loopN(n, 0, drawInnerParabolaInOrbit);
}

void drawExternalPetals() {
    glColor4f(1,0.87, 1, 0.5);
    loopN(4, 0, drawParabolaInOrbit);
}

void drawSpiral() {
    int num = 50;
    float angle = 0;
    float radius = 0.0;
    
    glPushMatrix();
    glScalef(2,2,2);
    for (int i = 1; i < num; i++) {
        glPushMatrix();
        angle = i * 30;
        glRotatef(angle, 0, 0, 1);
        glTranslatef(radius, 0, 0);
        glScalef(1.0 - i*0.02, 1.0 - i*0.02, 1.0);

        glColor3f(1.0 - i * 0.03, 0.2 + i * 0.02, 0.5 + i * 0.01);
        glBegin(GL_LINE_STRIP);
            glVertex2d(0, 0);
            glVertex2d(0, 1);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void drawRandomDots(int count, float xmin, float xmax, float ymin, float ymax) {
    for (int i = 0; i < count; i++) {
        float x = xmin + static_cast<float>(rand()) / RAND_MAX * (xmax - xmin);
        float y = ymin + static_cast<float>(rand()) / RAND_MAX * (ymax - ymin);

        float r = static_cast<float>(rand()) / RAND_MAX ;
        float g = static_cast<float>(rand()) / RAND_MAX;
        float b = static_cast<float>(rand()) / RAND_MAX;
        float a = static_cast<float>(rand()) / RAND_MAX * 0.1;

        glColor4f(1 - r * 0.2, 0.65 + g * 0.1, 0.9 - b * 0.2, a);
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(0.015, 0.01, 1);
        drawGlow();
        glPopMatrix();
    }
    glEnd();
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
    
    glScalef(k, k, 1);
    glTranslatef(tx, ty, 0);
    glRotatef(alpha, 0, 0, 1);
    
    drawRandomDots(88,-13,13, -3,13);
    glColor3f(0.08, 0.09, 0.13);
    drawCircle(0, 0, 4.4);
    glColor4f(1, 0.65, 0.9, 0.1);
    drawGlow();
    
    glPushMatrix();
    glScalef(1.1,1.1,1);
    glColor4f(1, 0.8, 0.8, 0.5);
    glPointSize(0.75);
    drawDotLoopLoop();
    glPointSize(1.5);
    glColor4f(1, 0.77, 0.88, 0.66);
    drawSingleDotLoop();
    glLineWidth(2);
    drawExternalPetals();
    glPopMatrix();
    
    glLineWidth(4);
    drawPetals();
    drawSpiral();
    glLineWidth(5);
    drawWagaraLines();

	glPopMatrix();
	glFlush();
}



//not impt
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.08, 0.09, 0.13, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(static_cast<unsigned>(time(0)));
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
            
        case 27:
            exit(0);

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
