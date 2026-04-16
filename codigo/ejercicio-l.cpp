#include <GL/glut.h>
#include <cmath>

float angulo = 0.0f;
bool zbufferActivo = true;

void init() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    GLfloat luz_ambiente[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat luz_difusa[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat luz_pos[] = { 5.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
}

void dibujarTexto(float x, float y, const char* texto) {
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);

    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto);
        texto++;
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(3.5, 2.5, 4.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glRotatef(angulo, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glColor3f(1.0f, 0.2f, 0.2f);
    glTranslatef(0.0f, 0.0f, 0.8f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.8f, -0.5f, 0.0f);
    glVertex3f(0.8f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 1.0f, 0.2f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.7f, 0.7f, 0.0f);
    glVertex3f(0.7f, 0.7f, 0.0f);
    glVertex3f(0.7f, -0.7f, 0.0f);
    glVertex3f(-0.7f, -0.7f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.2f, 1.0f);
    glTranslatef(0.0f, 0.0f, -0.8f);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex3f(cos(rad) * 0.6f, sin(rad) * 0.6f, 0.0f);
    }
    glEnd();
    glPopMatrix();

    if (zbufferActivo) {
        dibujarTexto(10, 570, "Z-BUFFER: ACTIVADO (Presiona ESPACIO para desactivar)");
        dibujarTexto(10, 540, "Las figuras se superponen CORRECTAMENTE");
    }
    else {
        dibujarTexto(10, 570, "Z-BUFFER: DESACTIVADO (Presiona ESPACIO para activar)");
        dibujarTexto(10, 540, "ERROR: Orden incorrecto");
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char key, int x, int y) {
    if (key == ' ') {
        zbufferActivo = !zbufferActivo;

        if (zbufferActivo)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        glutPostRedisplay();
    }

    if (key == 27) exit(0);
}

void timer(int value) {
    angulo += 1.0f;

    if (angulo > 360.0f)
        angulo -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("pregunta-l");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
