#include <GL/glut.h>

int winW = 900, winH = 700;
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;

void dibujarMalla() {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);

    const float min = -10.0f;
    const float max = 10.0f;
    const float paso = 1.0f;

    for (float z = min; z <= max; z += paso) {
        glVertex3f(min, 0.0f, z);
        glVertex3f(max, 0.0f, z);
    }

    for (float x = min; x <= max; x += paso) {
        glVertex3f(x, 0.0f, min);
        glVertex3f(x, 0.0f, max);
    }

    glEnd();
}

void dibujarVarilla(float posX) {
    GLUquadric* q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);

    glPushMatrix();
    glTranslatef(posX, 0.0f, 0.0f);

    glPushMatrix();
    glColor3f(0.0f, 0.7f, 1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(q, 0.6, 0.6, 8.0, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.4f, 0.8f);
    glTranslatef(0.0f, 8.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(1.2, 2.0, 25, 25);
    glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}

void dibujarDiscos(float posX) {
    glPushMatrix();
    glTranslatef(posX, 0.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.4f);
    glutSolidTorus(0.4, 2.4, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.9f);
    glutSolidTorus(0.4, 2.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.4f);
    glutSolidTorus(0.4, 1.6, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.9f);
    glutSolidTorus(0.4, 1.2, 30, 30);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspecto = (float)winW / (float)winH;
    gluPerspective(45.0, aspecto, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 10.0, 30.0,
        0.0, 4.0, 0.0,
        0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    dibujarMalla();

    float x1 = -6.0f;
    float x2 = 0.0f;
    float x3 = 6.0f;

    dibujarVarilla(x1);
    dibujarVarilla(x2);
    dibujarVarilla(x3);

    dibujarDiscos(x1);

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
    case GLUT_KEY_LEFT:      rotY -= 5.0f; break;
    case GLUT_KEY_RIGHT:     rotY += 5.0f; break;
    case GLUT_KEY_UP:        rotX -= 5.0f; break;
    case GLUT_KEY_DOWN:      rotX += 5.0f; break;
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
    glutCreateWindow("pregunta-h");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
