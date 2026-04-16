#include <GL/glut.h>

int winW = 900, winH = 700;
float rotX = 20.0f;
float rotY = 30.0f;
float rotZ = 0.0f;

void dibujarLienzoCuadrados() {
    glColor3f(0.0f, 0.0f, 1.0f);
    for (float s = 1.0f; s <= 10.0f; s += 1.0f) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(-s, 0.0f, -s);
        glVertex3f(s, 0.0f, -s);
        glVertex3f(s, 0.0f, s);
        glVertex3f(-s, 0.0f, s);
        glEnd();
    }
}

void dibujarArbol() {
    GLUquadric* q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);

    glPushMatrix();
    glColor3f(0.30f, 0.15f, 0.05f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(q, 0.7, 0.7, 3.0, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(3.0, 1.8, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.85f, 0.0f);
    glTranslatef(0.0f, 4.6f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.4, 1.8, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.6f, 0.0f);
    glTranslatef(0.0f, 6.2f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(1.6, 2.0, 30, 30);
    glPopMatrix();

    gluDeleteQuadric(q);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspecto = (float)winW / (float)winH;
    gluPerspective(45.0, aspecto, 1.0, 80.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(16.0, 14.0, 20.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    dibujarLienzoCuadrados();
    dibujarArbol();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    winW = w;
    winH = h;
    glViewport(0, 0, w, h);
}

void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  rotY -= 5.0f; break;
    case GLUT_KEY_RIGHT: rotY += 5.0f; break;
    case GLUT_KEY_UP:    rotX -= 5.0f; break;
    case GLUT_KEY_DOWN:  rotX += 5.0f; break;
    case GLUT_KEY_PAGE_UP:   rotZ += 5.0f; break;
    case GLUT_KEY_PAGE_DOWN: rotZ -= 5.0f; break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("pregunta-f");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
