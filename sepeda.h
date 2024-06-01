#ifndef SEPEDA_H_INCLUDED
#define SEPEDA_H_INCLUDED
#include "gl/glut.h"
void collisionBox(float putaran, float tx, float ty, float tz);
void Sepeda(float putaran, float x, float y, float z);
void gear( GLfloat inner_radius, GLfloat outer_radius, GLfloat width,GLint teeth, GLfloat tooth_depth );
void ZCylinder(GLfloat radius,GLfloat length);
void XCylinder(GLfloat radius,GLfloat length);
void drawChain();
void drawPedals();
void drawTyre();
void drawSeat();
#endif // TRUK_H_INCLUDED
