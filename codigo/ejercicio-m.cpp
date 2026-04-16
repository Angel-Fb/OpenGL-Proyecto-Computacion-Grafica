#include <GL/glut.h>
#include <stdbool.h>

float angulo = 25.0;
bool rotar = false;

void inicializarLuces() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    GLfloat luzPosicion[] = { 2.0, 5.0, 5.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);
}

void dibujarTexto(const char* texto, float x, float y) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);
}

void dibujarMesa() {
    glColor3f(0.55, 0.27, 0.07);
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(3.0, 0.1, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.45, 0.23, 0.05);

    float patas[4][3] = {
        {-1.3, -1.05, -0.8},
        { 1.3, -1.05, -0.8},
        {-1.3, -1.05,  0.8},
        { 1.3, -1.05,  0.8}
    };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(patas[i][0], patas[i][1], patas[i][2]);
        glScalef(0.1, 1.0, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}

void dibujarTeteras() {
    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.0);
    glColor3f(0.8, 0.1, 0.1);
    glutSolidTeapot(0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0.0, 0.0);
    glColor3f(0.1, 0.1, 0.8);
    glutSolidTeapot(0.4);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        0.0, 1.5, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glRotatef(angulo, 0.0, 1.0, 0.0);

    dibujarTeteras();
    dibujarMesa();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    dibujarTexto("Presione ESPACIO para continuar", 270, 570);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void idle() {
    if (rotar) {
        angulo += 0.2;
        if (angulo > 360) angulo = 0;
        glutPostRedisplay();
    }
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 32) {
        rotar = !rotar;
    }
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
    glutCreateWindow("pregunta-m");

    inicializarLuces();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}
