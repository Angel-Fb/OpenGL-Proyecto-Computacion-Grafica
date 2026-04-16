#include <GL/glut.h>

int modoProyeccion = 1;
int winW = 900, winH = 700;
float rotX = 25.0f, rotY = 30.0f;

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

void dibujarArbol() {
    GLUquadric* q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);

    glPushMatrix();
    glColor3f(0.30f, 0.15f, 0.05f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(q, 0.7, 0.7, 3.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.9f, 0.0f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.4, 3.0, 30, 30);
    glPopMatrix();

    gluDeleteQuadric(q);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspecto = (float)winW / (float)winH;

    if (modoProyeccion == 1) {
        glOrtho(-12.0f * aspecto, 12.0f * aspecto,
            -12.0f, 12.0f,
            1.0f, 50.0f);
    }
    else {
        gluPerspective(45.0, aspecto, 1.0, 50.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(10.0, 10.0, 18.0,
        0.0, 3.0, 0.0,
        0.0, 1.0, 0.0);

    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);

    dibujarMalla();
    dibujarArbol();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    winW = w;
    winH = h;
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        modoProyeccion = 1;
        break;
    case '2':
        modoProyeccion = 2;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  rotY -= 5.0f;
    if (key == GLUT_KEY_RIGHT) rotY += 5.0f;
    if (key == GLUT_KEY_UP)    rotX -= 5.0f;
    if (key == GLUT_KEY_DOWN)  rotX += 5.0f;

    glutPostRedisplay();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("pregunta-e");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    glutMainLoop();
    return 0;
}
