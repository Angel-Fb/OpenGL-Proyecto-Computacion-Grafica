#include <GL/glut.h>
#include <cmath>

GLuint texturaPiso, texturaMadera;

void generarTexturaBaldosas()
{
    const int ancho = 128;
    const int alto = 128;
    unsigned char textura[ancho][alto][3];

    for (int i = 0; i < ancho; i++) {
        for (int j = 0; j < alto; j++) {

            int cuadro = ((i / 16) + (j / 16)) % 2;
            unsigned char color = cuadro ? 240 : 80;

            if (i % 16 == 0 || j % 16 == 0) {
                color = 50;
            }

            textura[i][j][0] = color;
            textura[i][j][1] = color;
            textura[i][j][2] = color;
        }
    }

    glGenTextures(1, &texturaPiso);
    glBindTexture(GL_TEXTURE_2D, texturaPiso);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void generarTexturaMadera()
{
    const int ancho = 128;
    const int alto = 128;
    unsigned char textura[ancho][alto][3];

    for (int i = 0; i < ancho; i++) {
        for (int j = 0; j < alto; j++) {

            float veta = sin(i * 0.15f + sin(j * 0.05f) * 2.0f) * 0.3f + 0.7f;

            unsigned char r = (unsigned char)(139 * veta);
            unsigned char g = (unsigned char)(90 * veta);
            unsigned char b = (unsigned char)(43 * veta);

            textura[i][j][0] = r;
            textura[i][j][1] = g;
            textura[i][j][2] = b;
        }
    }

    glGenTextures(1, &texturaMadera);
    glBindTexture(GL_TEXTURE_2D, texturaMadera);
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

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    generarTexturaBaldosas();
    generarTexturaMadera();

    GLfloat luz_pos[] = { 0.0f, 3.0f, 0.0f, 1.0f };
    GLfloat luz_ambiental[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat luz_difusa[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, luz_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiental);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);

    glEnable(GL_COLOR_MATERIAL);
}

void dibujarMesa()
{
    glBindTexture(GL_TEXTURE_2D, texturaMadera);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0, 0.6f, 0);

    glBegin(GL_QUADS);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-0.8f, 0.1f, -0.5f);
    glTexCoord2f(2, 0); glVertex3f(0.8f, 0.1f, -0.5f);
    glTexCoord2f(2, 1); glVertex3f(0.8f, 0.1f, 0.5f);
    glTexCoord2f(0, 1); glVertex3f(-0.8f, 0.1f, 0.5f);

    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-0.8f, 0, 0.5f);
    glTexCoord2f(2, 0); glVertex3f(0.8f, 0, 0.5f);
    glTexCoord2f(2, 0.2f); glVertex3f(0.8f, 0.1f, 0.5f);
    glTexCoord2f(0, 0.2f); glVertex3f(-0.8f, 0.1f, 0.5f);

    glEnd();

    glPopMatrix();

    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * 0.6f, 0.3f, j * 0.35f);
            glScalef(0.1f, 0.6f, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(4.0, 2.5, 4.0,
        0.0, 0.8, 0.0,
        0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, texturaPiso);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-3.0f, 0.0f, -3.0f);
    glTexCoord2f(3, 0); glVertex3f(3.0f, 0.0f, -3.0f);
    glTexCoord2f(3, 3); glVertex3f(3.0f, 0.0f, 3.0f);
    glTexCoord2f(0, 3); glVertex3f(-3.0f, 0.0f, 3.0f);

    glEnd();

    dibujarMesa();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    float proporcion = (float)w / (float)h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, proporcion, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("pregunta-k");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
