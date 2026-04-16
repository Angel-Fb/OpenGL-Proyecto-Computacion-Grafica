#include <GL/glut.h>

float angulo = 0.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 25, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glTranslatef(-9.0, 4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glutWireTorus(0.8, 2.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTorus(0.8, 2.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, 2.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(1.0, 0.8, 0.0);
    GLUquadricObj* cil1 = gluNewQuadric();
    gluQuadricDrawStyle(cil1, GLU_LINE);
    gluCylinder(cil1, 1.5, 1.5, 6.0, 20, 20);
    gluDeleteQuadric(cil1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 2.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.8, 0.4, 1.0);
    GLUquadricObj* cil2 = gluNewQuadric();
    gluQuadricDrawStyle(cil2, GLU_LINE);
    gluCylinder(cil2, 1.5, 1.5, 6.0, 20, 20);
    gluDeleteQuadric(cil2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0, -4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(1.0, 1.0, 0.3);
    glScalef(2.0, 2.0, 2.0);
    glutWireIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0, -4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(0.8, 0.4, 1.0);
    glScalef(2.0, 2.0, 2.0);
    glutWireIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0, -4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glRotatef(25, 1, 0, 0);
    glColor3f(0.0, 0.8, 1.0);
    glutWireSphere(2.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, -4.0, 0.0);
    glRotatef(angulo, 0, 1, 0);
    glRotatef(25, 1, 0, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(2.0, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void animacion() {
    angulo += 0.05f;
    if (angulo > 360.0f) angulo -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutCreateWindow("pregunta-d");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(animacion);

    glutMainLoop();
    return 0;
}
