#include "randomobject.h"
#include "common.h"

//  GKV Game Sepeda
// Anggota Kelompok
// Naufal Rizki Saputra			(24060122120011)
// Muflih Muhammad Imaduddin	(24060122140103)
// Fikri Azka Pradya			(24060122140171)
// Ilhma Azrinargana Pulungan	(24060122140130)

void Objek::setX(float x)
{
    bx = x;
}

void Objek::setY(float y)
{
    by = y;
}

void Objek::setZ(float z)
{
    bz = z;
}

void Objek::setSize(float s)
{
    bsize = s;
}

void Objek::setHitValue(int v){
    bhitval = v;
}

float Objek::getX()
{
    return bx;
}

float Objek::getY()
{
    return by;
}

float Objek::getZ()
{
    return bz;
}

float Objek::getSize()
{
    return bsize;
}

int Objek::getHitValue()
{
    return bhitval;
}


Bangunan1::Bangunan1(float x, float y, float z, float s, float cr, float cg, float cb, int jumlahTumpuk){
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);

    for (int i=0;i<jumlahTumpuk;i++){
        glPushMatrix();
        glTranslatef(getX(),getY()+getSize()*i, getZ());
            glPushMatrix();
                glColor3f(cr, cg, cb);
                glutSolidCube(getSize());
            glPopMatrix();
        glPopMatrix();
    }

}

//pohon
Pohon::Pohon(float x, float y, float z, float s){
	setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);
    GLUquadricObj *quadratic;
    GLUquadricObj *quadric;
    quadratic = gluNewQuadric();
    quadric = gluNewQuadric();

    glPushMatrix();
        glTranslatef(getX(),getY(), getZ());
        glScalef(s,s,s);
        //batang
    	GLUquadricObj *pObj;
    	pObj = gluNewQuadric();
    	gluQuadricNormals(pObj, GLU_SMOOTH);
    	glPushMatrix();
    		glColor3ub(139, 69, 19); // Mengubah warna batang menjadi coklat
    		glRotated(270, 1, 0, 0);
    		glTranslatef(0,0,0);
    		gluCylinder(pObj, 1.5, 0.5, 8, 10, 10); // Lebih detail dengan lebih banyak segmen
		glPopMatrix();
        //daun 1
        glPushMatrix();
            glColor3ub(34,139,34); // Mengubah warna daun menjadi hijau gelap
            glScaled(2, 2, 2);
            glRotated(90, 0, 1, 0);
            glTranslatef(0,5,0);
            glutSolidIcosahedron(); // Mengubah dari dodecahedron ke icosahedron
        glPopMatrix();
        //daun 2
        glPushMatrix();
            glColor3ub(34,139,34);
            glScaled(2, 2, 2);
            glRotated(90, 0, 1, 0);
            glTranslatef(-1,4,-1);
            glutSolidIcosahedron();
        glPopMatrix();
        //daun 3
        glPushMatrix();
            glColor3ub(34,139,34);
            glScaled(2, 2, 2);
            glRotated(90, 0, 1, 0);
            glTranslatef(1,4,1);
            glutSolidIcosahedron();
        glPopMatrix();
	glPopMatrix();
	glFlush();
}


Pine::Pine(float x, float y, float z, float s){
	setX(x);
    setY(y);
    setZ(z);
    setSize(s*2);
    setHitValue(0);
    GLUquadricObj *quadratic;
    GLUquadricObj *quadric;
    quadratic = gluNewQuadric();
    quadric = gluNewQuadric();

    glPushMatrix();
        glTranslatef(getX(),getY(), getZ());
        glScalef(s,s,s);
        //batang
    	GLUquadricObj *pObj;
    	pObj = gluNewQuadric();
    	gluQuadricNormals(pObj, GLU_SMOOTH);
    	glPushMatrix();
    		glColor3ub(104, 70, 14);
    		glRotated(270, 1, 0, 0);
    		glTranslatef(0,0,0);
    		gluCylinder(pObj, 1.5, 1, 8, 5, 5);
		glPopMatrix();
        //daun 1
        glPushMatrix();
            glColor3ub(34,139,34);
            glScaled(2, 2, 2);
            glRotated(-90, 1, 0, 0);
            glTranslatef(0,0,2);
            glutSolidCone(3, 6, 10, 10); // Mengubah ukuran daun
        glPopMatrix();
        //daun 2
        glPushMatrix();
            glColor3ub(34,139,34);
            glScaled(2, 2, 2);
            glRotated(-90, 1, 0, 0);
            glTranslatef(0,0,4);
            glutSolidCone(3, 6, 10, 10);
        glPopMatrix();
        //daun 3
        glPushMatrix();
            glColor3ub(34,139,34);
            glScaled(2, 2, 2);
            glRotated(-90, 1, 0, 0);
            glTranslatef(0,0,6);
            glutSolidCone(3, 6, 10, 10); // Menambah lapisan daun
        glPopMatrix();
	glPopMatrix();
	glFlush();
}
rambu::rambu(float x, float y, float z, float rotation) {
    setX(x);
    setY(y);
    setZ(z);
    setSize(0.25);
    setHitValue(0);

    glPushMatrix();
        glTranslatef(getX(), getY(), getZ());
        glRotatef(rotation, 0, 1, 0);
        
        // Batang
        GLUquadricObj *pObj;
        pObj = gluNewQuadric();
        gluQuadricNormals(pObj, GLU_SMOOTH);
        
        glPushMatrix();
            glColor3f(0.3,0.3,0.3);
            glRotated(270, 1, 0, 0);
            gluCylinder(pObj, 0.25, 0.25, 10, 25, 25);
        glPopMatrix();

        // Sphere di atas cylinder
        glPushMatrix();
            glTranslatef(0, 10, 0); // Pindahkan sphere ke atas cylinder
            glColor3f(1.0, 1.0, 0.0);; // Warna sphere (warna kuning kecoklatan)
            glutSolidSphere(2, 2.5, 2.5); // Sphere dengan segmen lebih banyak untuk lebih halus
        glPopMatrix();
    glPopMatrix();
}

Lampu::Lampu(float x, float y, float z, float rotation){
    setX(x);
    setY(y);
    setZ(z);
    setSize(0.25);
    setHitValue(0);

    glPushMatrix();
        glTranslatef(getX(),getY(), getZ());
        glRotatef(rotation, 0, 1, 0);
        //batang
    	GLUquadricObj *pObj;
    	pObj = gluNewQuadric();
    	gluQuadricNormals(pObj, GLU_SMOOTH);
    	glPushMatrix();
    		glColor3f(0.3,0.3,0.3);
    		glRotated(270, 1, 0, 0);
    		gluCylinder(pObj, 0.25, 0.25, 10, 25, 25);
    		glTranslatef(0,0,10);
    		glutSolidCube(1);
    		glTranslatef(0,1,0);
    		glutSolidCube(1);
    		glTranslatef(0,1,0);
    		glutSolidCube(1);
    		glTranslatef(0,0,-0.5);
    		glColor3f(0.65,0.65,0.15);
    		glutSolidSphere(0.6, 20, 20); // Mengubah dari kubus ke bola
		glPopMatrix();
    glPopMatrix();
}


Awan::Awan(float x, float y, float z, float s){
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);

        glPushMatrix();
        glTranslatef(getX(),getY(),getZ());
        glScalef(s,s,s);
			glPushMatrix();
        		glPushMatrix();
        			glColor3ub(153, 223, 255);
        			glRotated(90, 0, 1, 0);
        			glTranslatef(0, 2, 0); //5 ,20 , -10
        			glutSolidSphere(2, 10, 5);
        		glPopMatrix();
        		glPushMatrix();
        			glColor3ub(153, 223, 255);
        			glRotated(90, 0, 1, 0);
        			glTranslatef(1, 1.5, -1.7);
        			glutSolidSphere(1.8, 10, 5);
        		glPopMatrix();
				glPushMatrix();
        			glColor3ub(153, 223, 255);
        			glRotated(90, 0, 1, 0);
        			glTranslatef(1, 1.5, 1.7);
        			glutSolidSphere(1.8, 10, 5);
        		glPopMatrix();
				glPushMatrix();
        			glColor3ub(153, 223, 255);
        			glRotated(90, 0, 1, 0);
        			glTranslatef(-1, 1.5, -1.7);
        			glutSolidSphere(2, 10, 5);
        		glPopMatrix();
				glPushMatrix();
        			glColor3ub(153, 223, 255);
        			glRotated(90, 0, 1, 0);
        			glTranslatef(-1, 1.5, 1.7);
        			glutSolidSphere(2, 10, 5);
        		glPopMatrix();
        	glPopMatrix();
        glPopMatrix();
}
