#include <GL/glut.h>
#include <cmath>

GLuint texturaID;

void generarTexturaCesped()
{
    const int ancho = 64;
    const int alto = 64;
    unsigned char textura[ancho][alto][3];

    for (int i = 0; i < ancho; i++) {
        for (int j = 0; j < alto; j++) {
            float ruido = (sin(i * 0.3) * cos(j * 0.5)) * 0.5 + 0.5;
            unsigned char verde = (unsigned char)(100 + 100 * ruido);
            unsigned char oscuro = (unsigned char)(verde - 40);

            textura[i][j][0] = 20;
            textura[i][j][1] = verde;
            textura[i][j][2] = oscuro;
        }
    }

    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.4, 0.7, 1.0, 1.0);

    generarTexturaCesped();

    GLfloat luz_pos[] = { 2.0, 5.0, 3.0, 0.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
    glEnable(GL_COLOR_MATERIAL);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0, 2.0, 3.0, 0, 0, 0, 0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, texturaID);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-2.0, 0.0, -2.0);
    glTexCoord2f(4, 0); glVertex3f(2.0, 0.0, -2.0);
    glTexCoord2f(4, 4); glVertex3f(2.0, 0.0, 2.0);
    glTexCoord2f(0, 4); glVertex3f(-2.0, 0.0, 2.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    float proporcion = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(64.0, proporcion, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("pregunta-j");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
