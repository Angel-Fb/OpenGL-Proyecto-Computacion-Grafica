#include <GL/glut.h>

int figura3D = 33;
int modo = 11;

float angulo_rotx = 20;
float angulo_roty = 30;
float angulo_rotz = 0;

void inicializarLuces() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void elegirModo(int opcion) {
    switch (opcion) {
    case 1: modo = 11; break;
    case 2: modo = 22; break;
    }
    glutPostRedisplay();
}

void elegirFigura3D(int opcion) {
    switch (opcion) {
    case 3: figura3D = 33; break;
    case 4: figura3D = 44; break;
    case 5: figura3D = 55; break;
    }
    glutPostRedisplay();
}

void salir(int opcion) {
    switch (opcion) {
    case 0: exit(0);
    }
}

void dibujar() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 1, 20);
    glTranslatef(0, 0, -5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angulo_rotx, 1, 0, 0);
    glRotatef(angulo_roty, 0, 1, 0);
    glRotatef(angulo_rotz, 0, 0, 1);

    if (modo == 11) {
        switch (figura3D) {
        case 33: glutSolidSphere(1.6, 20, 20); break;
        case 44: glutSolidCone(1.5, 1.3, 20, 20); break;
        case 55: glutSolidTorus(0.7, 1.4, 20, 20); break;
        }
    } else {
        switch (figura3D) {
        case 33: glutWireSphere(1.6, 20, 20); break;
        case 44: glutWireCone(1.5, 1.3, 20, 20); break;
        case 55: glutWireTorus(0.7, 1.4, 20, 20); break;
        }
    }

    glPopMatrix();
    glutSwapBuffers();
}

void funcion1(int w, int h) {
    glViewport(0, 0, w, h);
}

void rotacionEnEjeZ(unsigned char key, int x, int y) {
    switch (key) {
    case 'z': angulo_rotz += 2; break;
    case 'Z': angulo_rotz -= 2; break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void rotacionEjesXY(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        angulo_rotx -= 2;
        break;
    case GLUT_KEY_DOWN:
        angulo_rotx += 2;
        break;
    case GLUT_KEY_LEFT:
        angulo_roty -= 2;
        break;
    case GLUT_KEY_RIGHT:
        angulo_roty = 2;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(300, 300);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("MENÚ DE OPCIONES");

    glutDisplayFunc(dibujar);
    glutReshapeFunc(funcion1);
    glutKeyboardFunc(rotacionEnEjeZ);
    glutSpecialFunc(rotacionEjesXY);

    inicializarLuces();

    int x = glutCreateMenu(elegirModo);
    glutAddMenuEntry("Solido", 1);
    glutAddMenuEntry("Malla", 2);

    int y = glutCreateMenu(elegirFigura3D);
    glutAddMenuEntry("Esfera", 3);
    glutAddMenuEntry("Cono", 4);
    glutAddMenuEntry("Toroide", 5);

    glutCreateMenu(salir);
    glutAddSubMenu("Modo", x);
    glutAddSubMenu("Figura3D", y);
    glutAddMenuEntry("Salir", 0);

    glutAttachMenu(GLUT_LEFT_BUTTON);

    glutMainLoop();
    return 0;
}
