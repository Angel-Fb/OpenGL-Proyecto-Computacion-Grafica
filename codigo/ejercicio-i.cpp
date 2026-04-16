#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int anchoVentana = 640;
int altoVentana = 480;

struct Linea {
    float x1, y1;
    float x2, y2;
};

const int MAX_LINEAS = 1000;
Linea lineas[MAX_LINEAS];
int numLineas = 0;

bool tienePuntoInicial = false;
float xInicio = 0.0f, yInicio = 0.0f;
float xActual = 0.0f, yActual = 0.0f;

int xMouse = 0, yMouse = 0;

void mostrarCadenaAqui(int x, int y, const char* cadena) {
    glRasterPos2i(x, y);
    for (int i = 0; cadena[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cadena[i]);
    }
}

void dibujarCirculo(float radio, float x, float y) {
    const int SEG = 20;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= SEG; ++i) {
        float ang = 2.0f * 3.1415926f * i / SEG;
        float dx = radio * cosf(ang);
        float dy = radio * sinf(ang);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void dibujar() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numLineas; ++i) {
        glVertex2f(lineas[i].x1, lineas[i].y1);
        glVertex2f(lineas[i].x2, lineas[i].y2);
    }
    glEnd();

    for (int i = 0; i < numLineas; ++i) {
        dibujarCirculo(3.0f, lineas[i].x1, lineas[i].y1);
        dibujarCirculo(3.0f, lineas[i].x2, lineas[i].y2);
    }

    if (tienePuntoInicial) {
        glBegin(GL_LINES);
        glVertex2f(xInicio, yInicio);
        glVertex2f(xActual, yActual);
        glEnd();

        dibujarCirculo(3.0f, xInicio, yInicio);
        dibujarCirculo(3.0f, xActual, yActual);
    }

    char buffer[64];
    glColor3f(0.0f, 1.0f, 0.0f);

    sprintf_s(buffer, sizeof(buffer), "X: %d", xMouse);
    mostrarCadenaAqui(10, 20, buffer);

    sprintf_s(buffer, sizeof(buffer), "Y: %d", yMouse);
    mostrarCadenaAqui(150, 20, buffer);

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'c':
    case 'C':
        numLineas = 0;
        tienePuntoInicial = false;
        glutPostRedisplay();
        break;
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    anchoVentana = w;
    altoVentana = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouseSeMueve(int x, int y) {
    xMouse = x;
    yMouse = y;
    xActual = (float)x;
    yActual = (float)y;
    glutPostRedisplay();
}

void mouseEsPulsado(int button, int estado, int x, int y) {
    xMouse = x;
    yMouse = y;

    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        if (!tienePuntoInicial) {
            tienePuntoInicial = true;
            xInicio = (float)x;
            yInicio = (float)y;
            xActual = xInicio;
            yActual = yInicio;
        }
        else {
            if (numLineas < MAX_LINEAS) {
                lineas[numLineas].x1 = xInicio;
                lineas[numLineas].y1 = yInicio;
                lineas[numLineas].x2 = (float)x;
                lineas[numLineas].y2 = (float)y;
                numLineas++;
            }
            tienePuntoInicial = false;
        }
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(anchoVentana, altoVentana);
    glutCreateWindow("pregunta-i");

    init();

    glutDisplayFunc(dibujar);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseEsPulsado);
    glutMotionFunc(mouseSeMueve);
    glutPassiveMotionFunc(mouseSeMueve);

    glutMainLoop();
    return 0;
}
