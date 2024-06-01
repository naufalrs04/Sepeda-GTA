//  GKV Game Sepeda
// Anggota Kelompok
// Naufal Rizki Saputra			(24060122120011)
// Muflih Muhammad Imaduddin	(24060122140103)
// Fikri Azka Pradya			(24060122140171)
// Ilhma Azrinargana Pulungan	(24060122140130)

#include "sepeda.h"
#include <GL/glut.h>
#include <math.h>

#define   PI            3.14159
#define WIN_WIDTH      600
#define WIN_HEIGHT      600
#define CYCLE_LENGTH   3.3f
#define ROD_RADIUS      0.05f
#define NUM_SPOKES      20
#define SPOKE_ANGLE      18
#define RADIUS_WHEEL   1.0f
#define TUBE_WIDTH      0.08f
#define RIGHT_ROD      1.6f
#define RIGHT_ANGLE      48.0f
#define MIDDLE_ROD      1.7f
#define MIDDLE_ANGLE   106.0f
#define BACK_CONNECTOR   0.5f
#define LEFT_ANGLE      50.0f
#define WHEEL_OFFSET   0.11f
#define WHEEL_LEN      1.1f
#define TOP_LEN         1.5f
#define CRANK_ROD      0.7f
#define CRANK_RODS      1.12f
#define CRANK_ANGLE      8.0f
#define HANDLE_ROD      1.2f
#define FRONT_INCLINE   70.0f
#define HANDLE_LIMIT   70.0f
#define INC_STEERING   2.0f
#define INC_SPEED      0.05f
float cpDepanX, cpDepanZ, cpBelakangX, cpBelakangZ;
GLfloat pedalAngle, speed, steering;
GLfloat xpos,zpos,direction;

// Gambar rantai
void drawChain()
{
   GLfloat depth;
   static int mode = 0;
	GLfloat scale = 1.2f;
   glPushMatrix(); 

   glScalef(scale, scale, scale);

   glColor3f(0.0f, 1.0f, 0.0f);
   glEnable(GL_LINE_STIPPLE);
   mode = (mode + 1) % 2;

   if (mode == 0 && speed > 0)
      glLineStipple(1, 0x1c47);
   else if (mode == 1 && speed > 0)
      glLineStipple(1, 0x00FF);

   glBegin(GL_LINES);
   for (depth = 0.06f; depth <= 0.12f; depth += 0.01f)
   {
      glVertex3f(-1.6f, 0.15f, ROD_RADIUS);
      glVertex3f(0.0f, 0.3f, depth);

      glVertex3f(-1.6f, -0.15f, ROD_RADIUS);
      glVertex3f(0.0f, -0.3f, depth);
   }
   glEnd();

   glDisable(GL_LINE_STIPPLE);

   glPopMatrix();
}


// Gambar pedal
void drawPedals()
{
	GLfloat scale = 1.5f;
   glColor3f(0.0f,0.0f,1.0f);
   glPushMatrix();
            glScalef(scale, scale, scale);

      glTranslatef(0.0f,0.0f,0.105f);
      glRotatef(-pedalAngle,0.0f,0.0f,1.0f);
      glTranslatef(0.25f,0.0f,0.0f);

      glPushMatrix();
         glScalef(0.5f,0.1f,0.1f);
         glutSolidCube(1.0f);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.25f,0.0f,0.15f);
         glRotatef(pedalAngle,0.0f,0.0f,1.0f);
         glScalef(0.2f,0.02f,0.3f);
         glutSolidCube(1.0f);
      glPopMatrix();

   glPopMatrix();

   glPushMatrix();
      glScalef(scale, scale, scale);

      glTranslatef(0.0f,0.0f,-0.105f);
      glRotatef(180.0f-pedalAngle,0.0f,0.0f,1.0f);
      glTranslatef(0.25f,0.0f,0.0f);

      glPushMatrix();
         glScalef(0.5f,0.1f,0.1f);
         glutSolidCube(1.0f);
      glPopMatrix();

      glPushMatrix();
         glTranslatef(0.25f,0.0f,-0.15f);
         glRotatef(pedalAngle-180.0f,0.0f,0.0f,1.0f);
         glScalef(0.2f,0.02f,0.3f);
         glutSolidCube(1.0f);
      glPopMatrix();

   glPopMatrix();
   glColor3f(1.0f,0.0f,0.0f);
}

// Gambar tempat duduk
void drawSeat()
{

   glBegin(GL_POLYGON);
      glVertex3f(-0.1f, 1.0f, -0.5f);
      glVertex3f(   1.0f, 1.0f, -0.3f);
      glVertex3f( 1.0f, 1.0f,  0.3f);
      glVertex3f(-0.1f, 1.0f,  0.5f);
      glVertex3f(-0.5f, 1.0f,  1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-0.5f, 1.0f, -1.0f);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(-0.1f, -1.0f, -0.5f);
      glVertex3f(   1.0f, -1.0f, -0.3f);
      glVertex3f( 1.0f, -1.0f,  0.3f);
      glVertex3f(-0.1f, -1.0f,  0.5f);
      glVertex3f(-0.5f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-0.5f, -1.0f, -1.0f);
   glEnd();

   glBegin(GL_QUADS);
      glVertex3f(1.0f,1.0f,-0.3f);
      glVertex3f(1.0f,1.0f,0.3f);
      glVertex3f(1.0f,-1.0f,0.3f);
      glVertex3f(1.0f,-1.0f,-0.3f);

      glVertex3f(1.0f,1.0f,0.3f);
      glVertex3f(-0.1f,1.0f,0.5f);
      glVertex3f(-0.1f,-1.0f,0.5f);
      glVertex3f(1.0f,-1.0f,0.3f);

      glVertex3f(1.0f,1.0f,-0.3f);
      glVertex3f(-0.1f,1.0f,-0.5f);
      glVertex3f(-0.1f,-1.0f,-0.5f);
      glVertex3f(1.0f,-1.0f,-0.3f);

      glVertex3f(-0.1f,1.0f,0.5f);
      glVertex3f(-0.5f,1.0f,1.0f);
      glVertex3f(-0.5f,-1.0f,1.0f);
      glVertex3f(-0.1f,-1.0f,0.5f);

      glVertex3f(-0.1f,1.0f,-0.5f);
      glVertex3f(-0.5f,1.0f,-1.0f);
      glVertex3f(-0.5f,-1.0f,-1.0f);
      glVertex3f(-0.1f,-1.0f,-0.5f);

      glVertex3f(-0.5f,1.0f,1.0f);
      glVertex3f(-1.0f,1.0f,1.0f);
      glVertex3f(-1.0f,-1.0f,1.0f);
      glVertex3f(-0.5f,-1.0f,1.0f);

      glVertex3f(-0.5f,1.0f,-1.0f);
      glVertex3f(-1.0f,1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-0.5f,-1.0f,-1.0f);

      glVertex3f(-1.0f,1.0f,1.0f);
      glVertex3f(-1.0f,1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,1.0f);

   glEnd();


}

void ZCylinder(GLfloat radius,GLfloat length)
{
   GLUquadricObj *cylinder;
   cylinder=gluNewQuadric();
   glPushMatrix();
      glTranslatef(0.0f,0.0f,0.0f);
      gluCylinder(cylinder,radius,radius,length,15,5);
   glPopMatrix();
}

void XCylinder(GLfloat radius,GLfloat length)
{
   glPushMatrix();
      glRotatef(90.0f,0.0f,1.0f,0.0f);
      ZCylinder(radius,length);
   glPopMatrix();
}


void collisionBox(float putaran, float tx, float ty, float tz) {
    putaran = putaran - 90;
    cpDepanX = tx + -10.0*sin(putaran*M_PI/180);
    cpDepanZ = tz + -10.0*cos(putaran*M_PI/180);

    cpBelakangX = tx + 5.0*sin(putaran*M_PI/180);
    cpBelakangZ = tz + 5.0*cos(putaran*M_PI/180);

}

// Gambar gir 
void gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
          GLint teeth, GLfloat tooth_depth)
{
    GLint i;
    GLfloat r0, r1, r2;
    GLfloat angle, da;
    GLfloat u, v, len;
    const double pi = 3.14159264;
    GLfloat scale = 1.2f;

    r0 = inner_radius;
    r1 = outer_radius - tooth_depth / 2.0;
    r2 = outer_radius + tooth_depth / 2.0;

    da = 2.0 * pi / teeth / 4.0;

    glPushMatrix(); 

    glScalef(scale, scale, scale);

    glShadeModel(GL_FLAT);

    glNormal3f(0.0, 0.0, 1.0);

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * pi / teeth;
        glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
        glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    }
    glEnd();

    glBegin(GL_QUADS);
    da = 2.0 * pi / teeth / 4.0;
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * pi / teeth;

        glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    }
    glEnd();

    glNormal3f(0.0, 0.0, -1.0);

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * pi / teeth;
        glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    }
    glEnd();

    glBegin(GL_QUADS);
    da = 2.0 * pi / teeth / 4.0;
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * pi / teeth;

        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
        glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * pi / teeth;

        glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
        glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
        u = r2 * cos(angle + da) - r1 * cos(angle);
        v = r2 * sin(angle + da) - r1 * sin(angle);
        len = sqrt(u * u + v * v);
        u /= len;
        v /= len;
        glNormal3f(v, -u, 0.0);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
        glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
        glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
        u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
        v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
        glNormal3f(v, -u, 0.0);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
        glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
    }

    glVertex3f(r1 * cos(0.0), r1 * sin(0.0), width * 0.5);
    glVertex3f(r1 * cos(0.0), r1 * sin(0.0), -width * 0.5);

    glEnd();

    glShadeModel(GL_SMOOTH);

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * pi / teeth;
        glNormal3f(-cos(angle), -sin(angle), 0.0);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
        glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    }
    glEnd();

    glPopMatrix(); 
}


// Gambar roda
void drawTyre()
{
   int i;
   glColor3f(1.0f,1.0f,1.0f);
   glutSolidTorus(0.06f,0.92f,4,30);
 
   glColor3f(1.0f,1.0f,0.5f);
   glPushMatrix();
      glTranslatef(0.0f,0.0f,-0.06f);
      ZCylinder(0.02f,0.12f);
   glPopMatrix();
   glutSolidTorus(0.02f,0.02f,3,20);

   glColor3f(1.0f,1.0f,1.0f);
   for(i=0;i<NUM_SPOKES;++i)
   {
      glPushMatrix();
         glRotatef(i*SPOKE_ANGLE,0.0f,0.0f,1.0f);
         glBegin(GL_LINES);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.86f,0.0f);
         glEnd();
      glPopMatrix();
   }

   glColor3f(0.0f,0.0f,0.0f);
   glutSolidTorus(TUBE_WIDTH,RADIUS_WHEEL,10,30);
   glColor3f(1.0f,0.0f,0.0f);
}

// Gambar sepeda
void Sepeda(float putaran, float x, float y, float z){
	GLfloat scale = 1.6f;
    collisionBox(putaran, x, y, z);
    glTranslatef(x, y, z);
    glPushMatrix();
    
    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(scale, scale, scale);
    glRotated(putaran, 0.0f, 1.0f, 0.0f);
	drawPedals();
	drawChain();
    glColor3f(1.0f,0.0f,0.0f);

   glPushMatrix();

      glPushMatrix();

         glColor3f(0.0f,1.0f,0.0f);


         glPushMatrix();
            glTranslatef(0.0f,0.0f,0.06f);
            glRotatef(-2*pedalAngle,0.0f,0.0f,1.0f);
            gear(0.08f,0.3f,0.03f,30,0.03f);
         glPopMatrix();

         glColor3f(1.0f,0.0f,0.0f);
         glTranslatef(0.0f,0.0f,-0.2f);
         ZCylinder(0.08f,0.32f);
      glPopMatrix();

      glRotatef(RIGHT_ANGLE,0.0f,0.0f,1.0f);
      XCylinder(ROD_RADIUS,RIGHT_ROD);


      glRotatef(MIDDLE_ANGLE-RIGHT_ANGLE,0.0f,0.0f,1.0f);
      XCylinder(ROD_RADIUS,MIDDLE_ROD);

      glColor3f(1.0f,1.0f,0.0f);
      glTranslatef(MIDDLE_ROD,0.0f,0.0f);
      glRotatef(-MIDDLE_ANGLE,0.0f,0.0f,1.0f);
      glScalef(0.3f,ROD_RADIUS,0.25f);
      drawSeat();

      glColor3f(1.0f,0.0f,0.0f);
   glPopMatrix();

   glPushMatrix();
      glRotatef(-180.0f,0.0f,1.0f,0.0f);
      XCylinder(ROD_RADIUS,BACK_CONNECTOR);

      glPushMatrix();
         glTranslatef(0.5f,0.0f,WHEEL_OFFSET);
         XCylinder(ROD_RADIUS,RADIUS_WHEEL+TUBE_WIDTH);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0.5f,0.0f,-WHEEL_OFFSET);
         XCylinder(ROD_RADIUS,RADIUS_WHEEL+TUBE_WIDTH);
      glPopMatrix();
   glPopMatrix();


   glPushMatrix();
      glTranslatef(-(BACK_CONNECTOR+RADIUS_WHEEL+TUBE_WIDTH),0.0f,0.0f);

      glPushMatrix();
         glRotatef(-2*pedalAngle,0.0f,0.0f,1.0f);
         drawTyre();
         glColor3f(0.0f,1.0f,0.0f);
         glPushMatrix();
         	glScalef(scale, scale, scale);
            gear(0.03f,0.15f,0.03f,20,0.03f);
         glPopMatrix();
         glColor3f(1.0f,0.0f,0.0f);
      glPopMatrix();
      glRotatef(LEFT_ANGLE,0.0f,0.0f,1.0f);


      glPushMatrix();
         glTranslatef(0.0f,0.0f,-WHEEL_OFFSET);
         XCylinder(ROD_RADIUS,WHEEL_LEN);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(0.0f,0.0f,WHEEL_OFFSET);
         XCylinder(ROD_RADIUS,WHEEL_LEN);
      glPopMatrix();


      glTranslatef(WHEEL_LEN,0.0f,0.0f);
      XCylinder(ROD_RADIUS,CRANK_ROD);


      glTranslatef(CRANK_ROD,0.0f,0.0f);
      glRotatef(-LEFT_ANGLE,0.0f,0.0f,1.0f);
      XCylinder(ROD_RADIUS,TOP_LEN);


      glTranslatef(TOP_LEN,0.0f,0.0f);
      glRotatef(-FRONT_INCLINE,0.0f,0.0f,1.0f);

 
      glPushMatrix();
         glTranslatef(-0.1f,0.0f,0.0f);
         XCylinder(ROD_RADIUS,0.45f);
      glPopMatrix();

      glPushMatrix();
         glRotatef(-steering,1.0f,0.0f,0.0f);

         glTranslatef(-0.3f,0.0f,0.0f);


         glPushMatrix();
            glRotatef(FRONT_INCLINE,0.0f,0.0f,1.0f);

            glPushMatrix();
               glTranslatef(0.0f,0.0f,-HANDLE_ROD/2);
               ZCylinder(ROD_RADIUS,HANDLE_ROD);
            glPopMatrix();

            glPushMatrix();
               glColor3f(1.0f,1.0f,0.0f);
               glTranslatef(0.0f,0.0f,-HANDLE_ROD/2);
               ZCylinder(0.07f,HANDLE_ROD/4);
               glTranslatef(0.0f,0.0f,HANDLE_ROD*3/4);
               ZCylinder(0.07f,HANDLE_ROD/4);
               glColor3f(1.0f,0.0f,0.0f);
            glPopMatrix();
         glPopMatrix();


         glPushMatrix();

            XCylinder(ROD_RADIUS,CRANK_ROD);


            glTranslatef(CRANK_ROD,0.0f,0.0f);
            glRotatef(CRANK_ANGLE,0.0f,0.0f,1.0f);


            glPushMatrix();
               glTranslatef(0.0f,0.0f,WHEEL_OFFSET);
               XCylinder(ROD_RADIUS,CRANK_RODS);
            glPopMatrix();
            glPushMatrix();
            
               glTranslatef(0.0f,0.0f,-WHEEL_OFFSET);
               XCylinder(ROD_RADIUS,CRANK_RODS);
            glPopMatrix();

          
            glTranslatef(CRANK_RODS,0.0f,0.0f);
            glRotatef(-2*pedalAngle,0.0f,0.0f,1.0f);
            drawTyre();
         glPopMatrix();
      glPopMatrix();   
   glPopMatrix();
glPopMatrix();
}

