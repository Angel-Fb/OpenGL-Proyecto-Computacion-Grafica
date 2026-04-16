#include <GL/glut.h>
#include <iostream>

int figura = 0;
float rotX = 0, rotY = 0;
float R = 1, G = 1, B = 1;
bool isSolid = true;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    glColor3f(R, G, B);

    if (isSolid) {
        switch (figura) {
        case 1: glutSolidTeapot(1.0); break;
        case 2: glutSolidSphere(1.0, 40, 40); break;
        case 3: glutSolidTorus(0.3, 0.8, 30, 30); break;
        case 4: glutSolidCone(1.0, 1.5, 30, 30); break;
        }
    } else {
        glDisable(GL_LIGHTING);
        switch (figura) {
        case 1: glutWireTeapot(1.0); break;
        case 2: glutWireSphere(1.0, 40, 40); break;
        case 3: glutWireTorus(0.3, 0.8, 30, 30); break;
        case 4: glutWireCone(1.0, 1.5, 30, 30); break;
        }
        glEnable(GL_LIGHTING);
    }

    glutSwapBuffers();
}

void special(int k, int x, int y) {
    if (k == GLUT_KEY_LEFT)  rotY -= 5;
    if (k == GLUT_KEY_RIGHT) rotY += 5;
    if (k == GLUT_KEY_UP)    rotX -= 5;
    if (k == GLUT_KEY_DOWN)  rotX += 5;

    glutPostRedisplay();
}

void menuColor(int value) {
    switch (value) {
    case 11: R = 1; G = 0; B = 0; break;
    case 12: R = 1; G = 1; B = 1; break;
    case 13: R = 1; G = 1; B = 0; break;
    case 14: R = 0; G = 1; B = 0; break;
    case 15: R = 0; G = 0; B = 1; break;
    }
    glutPostRedisplay();
}

void menuFigura(int value) {
    figura = value;
    glutPostRedisplay();
}

void menuModo(int value) {
    if (value == 1)
        isSolid = true;
    else
        isSolid = false;

    glutPostRedisplay();
}

void menuPrincipal(int value) {
    if (value == 1) figura = 0;
    if (value == 0) exit(0);

    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuseLight[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat lightPosition[] = { 5.0, 5.0, 10.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Menu Interactivo con Iluminacion");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);

    int menuColores = glutCreateMenu(menuColor);
    glutAddMenuEntry("Rojo", 11);
    glutAddMenuEntry("Blanco", 12);
    glutAddMenuEntry("Amarillo", 13);
    glutAddMenuEntry("Verde", 14);
    glutAddMenuEntry("Azul", 15);

    int menuModoDibujo = glutCreateMenu(menuModo);
    glutAddMenuEntry("Solido", 1);
    glutAddMenuEntry("Alambre (Wireframe)", 2);

    int menuFiguras = glutCreateMenu(menuFigura);
    glutAddMenuEntry("Tetera", 1);
    glutAddMenuEntry("Esfera", 2);
    glutAddMenuEntry("Toroide", 3);
    glutAddMenuEntry("Cono", 4);

    glutCreateMenu(menuPrincipal);
    glutAddMenuEntry("Limpiar", 1);
    glutAddSubMenu("Figura", menuFiguras);
    glutAddSubMenu("Color", menuColores);
    glutAddSubMenu("Modo de Dibujo", menuModoDibujo);
    glutAddMenuEntry("Salir", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
