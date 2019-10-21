#include "nave.hpp"
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
#define PI 3.1415926535

Nave::Nave(){}

void Nave::setAtt(float x, float y, int iD, float raio, string fill){
    pos_x = x;
    pos_y = y;
    radius = raio;
    id = iD; 
    cor = fill;
}

void Nave::desenhaNave(float angle, int circle_points){
	glBegin(GL_POLYGON);
	if(cor == "red")
	glColor3f(1, 0, 0);
	if(cor == "green")
    glColor3f(0, 1, 0);
	if(cor =="orange")
	glColor3f(1, 0.5, 0);

	for(int i = 0; i < circle_points; i++) {
    	angle = (2*PI*i)/circle_points;
		glVertex2f(pos_x+radius*cos(angle),pos_y+radius*sin(angle));	
	}	
	glEnd();	
 	
	glutPostRedisplay();
	glFlush();
}
