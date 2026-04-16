#include <GL/glut.h>
#include <cmath>

float angulo = 30.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat luz_posicion[] = { 2.0, 4.0, 6.0, 1.0 };
    GLfloat luz_ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat luz_difusa[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat luz_especular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);

    glShadeModel(GL_SMOOTH);
}

void cilindro() {
    GLUquadricObj* puntero = gluNewQuadric();
    gluQuadricDrawStyle(puntero, GLU_LINE);

    glPushMatrix();
    glRotatef(angulo, 0, 1, 0);
    glColor3f(0.839, 0.969, 0.502);
    gluCylinder(puntero, 0.8, 0.8, 3.5, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(puntero);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 12, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glTranslatef(-4.0, 3.0, 0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTeapot(1.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, 3.0, 0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glutWireTeapot(1.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    cilindro();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, -3.0, 0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTeapot(1.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, -3.0, 0);
    glRotatef(angulo, 0, 1, 0);
    glColor3f(0.0, 0.5, 1.0);
    glutSolidTeapot(1.5);
    glPopMatrix();

    glutSwapBuffers();
}

void animacion() {
    angulo += 0.7f;
    if (angulo > 360.0f) angulo = 0.0f;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("EJERCICIO 01");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(animacion);

    glutMainLoop();
    return 0;
}
