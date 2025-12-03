#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <cgvCylinder.h>

#include "cgvScene3D.h"
#include "cgvTriangleMesh.h"


// Constructor methods

/**
 * Default constructor
 */
cgvScene3D::cgvScene3D () {  //Section B: Insert code to create a cylinder
    mesh = new cgvCylinder(1.0f, 1.0f, 40, 2);
    axes = true;
    rotX = rotY = rotZ = 0.0f;

    currentScene = 1; //Para el testing;

    x = 0;
    y = 0;
    z = 0;
    z2 = 0;

    objetoSeleccionado = 1;
    timer = 0.0;

    // Inicializamos selección
    selectionMode = false;
    idToHighlight = -1;

    for (int i = 0; i < 3; i++) {
        transforms[i].tx = 0.0f;
        transforms[i].ty = 0.0f;
        transforms[i].tz = 0.0f;

        transforms[i].rx = 0.0f;
        transforms[i].ry = 0.0f;
        transforms[i].rz = 0.0f;

        transforms[i].s = 1.0f;
    }

    //Practica 3
    lightbulb = new cgvLightSource(
            GL_LIGHT0,
            cgvPoint3D(1, 1, 1),
            cgvColor(0, 0, 0, 1),
            cgvColor(1, 1, 1, 1),
            cgvColor(1, 1, 1, 1),
            1, 0, 0
    );
    lightbulb->turnon();

    spotlight = new cgvLightSource(
            GL_LIGHT1,
            cgvPoint3D(3, 1, 1),
            cgvColor(0, 0, 0, 1),
            cgvColor(1, 1, 1, 1),
            cgvColor(1, 1, 1, 1),
            1, 0, 0,
            cgvPoint3D(0, -1, 0),
            45,
            0
    );
    spotlight->turnon();

    material = new cgvMaterial(
            cgvColor(0.15, 0, 0),
            cgvColor(0.5, 0, 0),
            cgvColor(0.5, 0, 0),
            120
    );
    texture = nullptr;
}

/**
 * Destructor
 */
cgvScene3D::~cgvScene3D ()
{  if ( mesh != nullptr ){delete mesh; mesh = nullptr;}
    //Practica 3
    delete lightbulb;
    delete spotlight;
    delete material;
    delete texture;
}

//Practica 3
/**
 * Method for painting a quadrilateral in the scene
 */
void cgvScene3D::paint_quad() {
    float ini_x = 0.0;
    float ini_z = 0.0;
    float tam_x = 5.0;
    float tam_z = 5.0;

    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(ini_x, 0.0, ini_z);
    glVertex3f(ini_x, 0.0, ini_z + tam_z);
    glVertex3f(ini_x + tam_x, 0.0, ini_z + tam_z);
    glVertex3f(ini_x + tam_x, 0.0, ini_z);
    glEnd();
}

void cgvScene3D::paint_quad(float div_x, float div_z) {
    float ini_x = 0.0;
    float ini_z = 0.0;
    float tam_x = 5.0;
    float tam_z = 5.0;

    float longX = tam_x / div_x;
    float longZ = tam_z / div_z;

    glNormal3f(0, 1, 0);
    for (int i = 0; i < div_x; i++) {
        for (int j = 0; j < div_z; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f((ini_x + i * longX) / tam_x, (ini_z + j * longZ) / tam_z);
            glVertex3f(ini_x + i * longX, 0.0f, ini_z + j * longZ);

            glTexCoord2f((ini_x + i * longX) / tam_x, (ini_z + (j + 1) * longZ) / tam_z);
            glVertex3f(ini_x + i * longX, 0.0f, ini_z + (j + 1) * longZ);

            glTexCoord2f((ini_x + (i + 1) * longX) / tam_x, (ini_z + (j + 1) * longZ) / tam_z);
            glVertex3f(ini_x + (i + 1) * longX, 0.0f, ini_z + (j + 1) * longZ);

            glTexCoord2f((ini_x + (i + 1) * longX) / tam_x, (ini_z + j * longZ) / tam_z);
            glVertex3f(ini_x + (i + 1) * longX, 0.0f, ini_z + j * longZ);
            glEnd();
        }
    }
}

// Public methods

/**
 * Method for painting the coordinate axes by calling OpenGL functions
 */
void cgvScene3D::paint_axes()
{    GLfloat red[] = { 1,0,0,1.0 };
    GLfloat green[] = { 0,1,0,1.0 };
    GLfloat blue[] = { 0,0,1,1.0 };

    glMaterialfv(GL_FRONT, GL_EMISSION, red);
    glBegin(GL_LINES);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, green);
    glBegin(GL_LINES);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);
    glEnd();

    glMaterialfv(GL_FRONT, GL_EMISSION, blue);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void cgvScene3D::paintCube() {
    // buscar marron oscuro muy oscuro
    if (!selectionMode && idToHighlight == 1) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
    }
    else {
        if (!selectionMode) {
            GLfloat color_cube[] = {0.35, 0.16, 0.14};
            glMaterialfv(GL_FRONT, GL_EMISSION, color_cube);
        }
    }
    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glEnd();
}

void cgvScene3D::drawMastil(float lenght) {
    GLUquadricObj* tube;
    if (!selectionMode && idToHighlight == 2) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
    }
    else {
        if (!selectionMode) {
            GLfloat mastilColor[] = {0.3, 0.3, 0.3};
            glMaterialfv(GL_FRONT, GL_EMISSION, mastilColor);
        }
    }

    tube = gluNewQuadric();
    gluQuadricDrawStyle(tube, GLU_FILL);

    glPushMatrix();
    glRotated(270,1,0,0);
    glScalef(1,1,4);
    gluCylinder(tube, 0.25,0.25,lenght,20,20);
    glPopMatrix();

    gluDeleteQuadric(tube);
}


void cgvScene3D::drawEsferaArmilar(float lenght) {
    // Esta no va a ser seleccionable, pero por si acaso:
    if (!selectionMode) {
        GLfloat esferaColor[] = {1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, esferaColor);
    }

    glPushMatrix();
    glTranslatef(0.0, 6, 0.0);
    glutSolidSphere(lenght, 25, 25);
    glPopMatrix();
}

void cgvScene3D::drawFlag(float lenght) {
    if (!selectionMode && idToHighlight == 3) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
    }
    else {
        if (!selectionMode) {
            GLfloat flagColor[] = {1.0, 0.0, 0.0};
            glMaterialfv(GL_FRONT, GL_EMISSION, flagColor);
        }
    }

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glEnd();
}


void cgvScene3D::drawLogo(float lenght) {
    if (!selectionMode && idToHighlight == 4) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
    }
    else {
        if (!selectionMode) {
            GLfloat logoColor[] = {0.3, 0.3, 0.3};
            glMaterialfv(GL_FRONT, GL_EMISSION, logoColor);
        }
    }

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, 0.75f);
    glVertex3f(0.75f, 0.75f, -0.75f);
    glVertex3f(-0.75f, 0.75f, -0.75f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.75f, -0.75f, -0.75f);
    glVertex3f(0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, 0.75f);
    glVertex3f(-0.75f, -0.75f, -0.75f);
    glEnd();
}



/**
 * Method with OpenGL calls to visualise the scene
 */
void cgvScene3D::display( void )
{
    // Siempre mantenemos un push/pop global bien balanceado para no corromper la pila.
    glPushMatrix();

    // Si estamos en "Modo Selección" (click del ratón), apagamos luces para pintar colores planos (IDs).
    // Si no, encendemos luces normales.
    if (selectionMode) {
        glDisable(GL_LIGHTING);
        glDisable(GL_DITHER);
    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_DITHER);

        GLfloat mesh_colour[] = { 0, 0.25, 0 };
        GLfloat light0[4] = { 2.0, 2.5, 3.0, 1 };
        glLightfv ( GL_LIGHT0, GL_POSITION, light0 );
        glEnable(GL_LIGHT0);
        glMaterialfv ( GL_FRONT, GL_EMISSION, mesh_colour );
    }

    // paint the axes
    if (axes) paint_axes();



    // create the model - rotaciones globales (APLICADAS SIEMPRE)
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // Switch por escenas (mantenemos transformaciones y order coherente
    switch (currentScene)
    {
        case 1: // Escena A
            if (mesh != nullptr)
                mesh->display();
            break;

        case 2: // Escena B (bandera + wooper) - modo visualización
        {
            glPushMatrix();
            // escala global de escenario
            glScaled(0.2, 0.2, 0.2);

            // --- WOOPER (a la derecha) ---
            glPushMatrix();
            glTranslatef(3.5f, 0.0f, 0.0f); // separo el wooper
            // en modo selección no pintamos IDs para el wooper por ahora
            drawWooper();
            glPopMatrix();


            //BANDERA//


            // --- Conjunto Bandera (a la izquierda) ---
            glPushMatrix();
            glTranslatef(-2.5f, 0.0f, 0.0f); // posiciona el conjunto de la bandera

            glRotatef(baseRotY, 0, 1, 0);
            // --- 1. Base (Cubo) ---
            glPushMatrix();
            paintCube();
            glPopMatrix();

            // --- 2. Esfera Armilar (Estática, Hija de la Base) ---
            glPushMatrix();
            drawEsferaArmilar(0.4);
            glPopMatrix();

            // --- 3. Mástil (Hijo de la Base) ---
            glPushMatrix();
            glRotatef(mastilRotY, 0, 1, 0); // <-- GRADO DE LIBERTAD (Mástil)
            drawMastil(1.5);

            // --- 3.1. Bandera (Hija del Mástil) ---
            glPushMatrix();
            glTranslatef(0, banderaPosY, 0); // <-- GRADO DE LIBERTAD (Bandera)

            glScaled(1.5, 1, 0.2);
            glTranslatef(0.9, 5, 0);
            drawFlag(1.5);

            // --- 3.1.1. Logo (Hijo de la Bandera) ---
            glPushMatrix();
            glScaled(0.3, 0.45, 1);
            glTranslatef(0, 0, 0.2);
            glRotated(45, 0, 0, 1);

            glRotatef(logoRotZ, 0, 0, 1); // <-- GRADO DE LIBERTAD (Logo)
            drawLogo(1);
            glPopMatrix(); // Fin Logo
            glPopMatrix(); // Fin Bandera
            glPopMatrix(); // Fin Mástil

            glPopMatrix(); // Fin conjunto de la bandera
            glPopMatrix(); // fin escala global
            break;
        }

        case 3: // Escena C (Picking + Monedas)
        {

            //Practica 3
            // Lights are applied before scene transformations so they remain fixed
            // TODO: SECTION A: Define and apply the point light specified in the practice script
            lightbulb->apply(); // Create the lights, materials, and texture in the constructor so they are not generated with each window update

            /* TODO: SECTION E: Define and apply the spotlight type specified in the practice script*/
            spotlight->apply();

            /* TODO: Section B: Define and apply the material properties indicated in the practice script */
            material->apply();

            /* TODO: Section D: Replace the values corresponding to the R component of the diffuse coefficient,
            the R component of the specular coefficient, and the Phong exponent, with the value
            of the corresponding attribute of the igvScene class */

            if(texture==nullptr){
                texture = new cgvTexture((char *) "../map.png"); // Only load it once //FIXME poner la foto que quieras
            }
            texture->apply();
            paint_quad(50, 50);

            glPushMatrix();

            glTranslatef(transforms[2].tx, transforms[2].ty, transforms[2].tz);

            glRotatef(transforms[2].rx, 1, 0, 0); // Rotación X
            glRotatef(transforms[2].ry, 0, 1, 0); // Rotación Y
            glRotatef(transforms[2].rz, 0, 0, 1); // Rotación Z

            glScalef(transforms[2].s, transforms[2].s, transforms[2].s);

            glScaled(0.2, 0.2, 0.2); // Escala global

            // 1. DIBUJAR MONEDAS (Decoración)
            // Solo las dibujamos si NO estamos seleccionando (para que no molesten al click)
            if (!selectionMode) {
                for (std::vector<Coin>::iterator it = coins.begin(); it != coins.end(); it++) {
                    drawCoin(*it);
                }
            }

            // Posiciono el conjunto de la bandera en el mismo sitio que en la escena 2
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f); // misma traslación que escena 2


            // --- ID 1: BASE ---
            glPushMatrix();
            glRotatef(baseRotY, 0, 1, 0);
            applyColorMaterial(1, 0.35f, 0.16f, 0.14f);
            paintCube();

            glPopMatrix();

            // --- ESFERA (Decorativa) ---
            glPushMatrix();
            glRotatef(baseRotY, 0, 1, 0);
            // La esfera la dejamos sin ID (no seleccionable), pero si no estamos en selectionMode pintamos su color
            if (!selectionMode) {
                drawEsferaArmilar(0.4);
            }
            glPopMatrix();

            // --- ID 2: MÁSTIL ---
            glPushMatrix();
            glRotatef(baseRotY, 0, 1, 0);
            glRotatef(mastilRotY, 0, 1, 0);
            applyColorMaterial(2, 0.3f, 0.3f, 0.3f);
            drawMastil(1.5);

            // --- ID 3: BANDERA ---
            glPushMatrix();
            glTranslatef(0, banderaPosY, 0);
            glScaled(1.5, 1, 0.2);
            glTranslatef(0.9, 5, 0);
            applyColorMaterial(3, 1.0f, 0.0f, 0.0f);
            drawFlag(1.5);


            // --- ID 4: LOGO ---
            glPushMatrix();
            glScaled(0.3, 0.45, 1);
            glTranslatef(0, 0, 0.2);
            glRotated(45, 0, 0, 1);
            glRotatef(logoRotZ, 0, 0, 1);
            applyColorMaterial(4, 0.3f, 0.3f, 0.3f);
            drawLogo(1);
            glPopMatrix(); // Fin Logo

            glPopMatrix(); // Fin Bandera
            glPopMatrix(); // Fin Mástil

            glPopMatrix(); // Fin conjunto bandera
            glPopMatrix(); // fin escala global
            break;
        }
    }

    glPopMatrix(); // restores the modelling matrix (el push global del principio)
}

/**
 * Method to check whether the axes should be drawn or not
 * @retval true If the axes should be drawn
 * @retval false If the axes should not be drawn
 */
bool cgvScene3D::get_axes ()
{  return axes;
}

/**
 * Method to enable or disable the drawing of the axes
 * @param axes Indicates whether to draw the axes (true) or not (false)
 * @post The status of the object changes with regard to drawing axes,
 *       according to the value passed as a parameter
 */
void cgvScene3D::set_axes ( bool axes )
{  this->axes = axes; //Arreglado
}

double cgvScene3D::getRotX() const {
    return rotX;
}

void cgvScene3D::setRotX(double rotX) {
    cgvScene3D::rotX = rotX;
}

double cgvScene3D::getRotY() const {
    return rotY;
}

void cgvScene3D::setRotY(double rotY) {
    cgvScene3D::rotY = rotY;
}

double cgvScene3D::getRotZ() const {
    return rotZ;
}

void cgvScene3D::setRotZ(double rotZ) {
    cgvScene3D::rotZ = rotZ;
}


//ESCENAS
// --- ESCENA A ---
void cgvScene3D::renderSceneA()
{
    currentScene = 1;
    if (mesh != nullptr) delete mesh;
    mesh = new cgvCylinder(1.0f, 1.0f, 40, 2);
    axes = true;
    glutPostRedisplay();
}

// --- ESCENA B ---
void cgvScene3D::renderSceneB()
{
    currentScene = 2;
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }

    axes = true;
    glutPostRedisplay();
}

// --- ESCENA C ---
void cgvScene3D::renderSceneC()
{
    currentScene = 3;
    if (mesh != nullptr) {
        delete mesh;
        mesh = nullptr;
    }

    axes = true;
    glutPostRedisplay();
}

void cgvScene3D::drawWooper() {
    // --- Colores ---
    GLfloat cian[] = {0.0f,0.8f,1.0f};
    GLfloat azul[] = {0.0f,0.0f,1.0f};
    GLfloat negro[] = {0.0f,0.0f,0.0f};
    GLfloat rosa[] = {1.0f, 0.0f, 0.5f};
    GLfloat morado[] = {0.5f, 0.0f, 0.5f};

    glMaterialfv(GL_FRONT, GL_EMISSION, cian);

    // Cuerpo
    glPushMatrix();
    glScalef(1.0f,1.5f,1.0f);
    glutSolidSphere(1.0,25,25);
    glPopMatrix();

    // Cola
    glPushMatrix();
    glRotated(30,1,0,0);
    glRotatef(wooperColaZ, 0, 0, 1);
    glScalef(0.5f,0.5f,1.5f);
    glTranslatef(0.0f,-1.5f,-0.65f);
    glutSolidSphere(1.0f,25,25);
    glPopMatrix();

    // Branquias Internas (Panza)
    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glPushMatrix();
    glScalef(1.5f,1.0f,1.0f);
    glTranslatef(0.0f,0.65f,0.6f);
    glutSolidSphere(0.4, 25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.65f);
    glutSolidSphere(0.45, 25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,-0.65f,0.5f);
    glutSolidSphere(0.5, 25,25);
    glPopMatrix();

    //Patas
    glMaterialfv(GL_FRONT, GL_EMISSION, cian);
    glPushMatrix();
    glRotatef(wooperPatasRotZ, 0, 0, 1);

    // Pata 1
    glPushMatrix();
    glScalef(1.5f,0.5f,0.5f);
    glTranslatef(-0.2f,-2.65f,0.0f);
    glutSolidSphere(0.5f,25,25);
    glPopMatrix();

    // Pata 2
    glPushMatrix();
    glScalef(1.5f,0.5f,0.5f);
    glTranslatef(0.2f,-2.65f,0.0f);
    glutSolidSphere(0.5f,25,25);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix(); // Conjunto cabeza

    glTranslatef(0.0f, 2.0f, 0.0f);
    glRotatef(wooperCabezaRotZ, 0, 0, 1);

    //Cabezon
    glMaterialfv(GL_FRONT, GL_EMISSION, cian);
    glPushMatrix();
    glScalef(1.5f,1.0f,1.0f);
    glutSolidSphere(1.0,25,25);
    glPopMatrix();

    // Ojos (Hijos estáticos de la Cabeza)
    glMaterialfv(GL_FRONT, GL_EMISSION, negro);
    glPushMatrix();
    glTranslatef(-0.7f, 0.25f, 0.75f);
    glutSolidSphere(0.25, 25,25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.25f, 0.75f);
    glutSolidSphere(0.25, 25,25);
    glPopMatrix();

    // Boca (Hijo estático de la Cabeza)
    glMaterialfv(GL_FRONT, GL_EMISSION, rosa);
    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.75f);
    glutSolidSphere(0.35, 25,25);
    glPopMatrix();


    glPushMatrix(); // INICIO GRUPO BRANQUIAS EXTERNAS

    glRotatef(wooperBranquiasRotX, 1, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, morado);

    // Branquias Horizontales
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glScalef(2.0f,0.5f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    glScalef(2.0f,0.5f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();


    glPushMatrix(); // INICIO GRUPO BRANQUIAS PEQUEÑAS

    // Branquias Verticales
    glPushMatrix();
    glTranslatef(2.3f, 0.0f, 0.0f);
    glRotatef(wooperBranquiasPequesRotY, 0, 1, 0);
    glScalef(0.5f,2.0f,0.5f);
    glutSolidCube(0.35);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.3f, 0.0f, 0.0f);
    glRotatef(wooperBranquiasPequesRotY, 0, 1, 0);
    glScalef(0.5f,2.0f,0.5f);
    glutSolidCube(0.35);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8f, 0.0f, 0.0f);
    glRotatef(wooperBranquiasPequesRotY, 0, 1, 0);
    glScalef(0.5f,2.15f,0.5f);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, 0.0f);
    glRotatef(wooperBranquiasPequesRotY, 0, 1, 0);
    glScalef(0.5f,2.15f,0.5f);
    glutSolidCube(0.4);
    glPopMatrix();

    glPopMatrix(); // FIN GRUPO BRANQUIAS PEQUEÑAS
    glPopMatrix(); // FIN GRUPO BRANQUIAS EXTERNAS
    glPopMatrix(); // FIN GRUPO CABEZA
}

int cgvScene3D::getObjetoSeleccionado() const {
    return objetoSeleccionado;
}

void cgvScene3D::setObjetoSeleccionado(int objetoSeleccionado) {
    cgvScene3D::objetoSeleccionado = objetoSeleccionado;
}

void cgvScene3D::controlarParte(int parte, double incremento) {

    if (objetoSeleccionado == 1) { // --- BANDERA ---
        switch (parte) {
            case 1: // 'b'/'B' -> Base (Rotar Y)
                baseRotY += incremento;
                break;
            case 2: // 'c'/'C' -> Mástil (Rotar Y)
                mastilRotY += incremento;
                break;
            case 3: // 'm'/'M' -> Bandera (Mover Y)
                banderaPosY += incremento * 0.1;
                if (banderaPosY > 0) banderaPosY = 0;
                if (banderaPosY < -3.5) banderaPosY = -3.5;
                break;
            case 4: // 'n'/'N' -> Logo (Rotar Z)
                logoRotZ += incremento;
                break;
        }
    } else if (objetoSeleccionado == 2) { // --- WOOPER ---
        switch (parte) {
            case 1: // 'b'/'B' -> Patas (Rotar Z)
                wooperPatasRotZ += incremento;

                if (wooperPatasRotZ > 15.0) wooperPatasRotZ = 15.0;
                if (wooperPatasRotZ < -15.0) wooperPatasRotZ = -15.0;
                break;
            case 2: // 'c'/'C' -> Cabeza (Rotar X)
                wooperCabezaRotZ += incremento;
                if (wooperCabezaRotZ > 10.0) wooperCabezaRotZ = 10.0;
                if (wooperCabezaRotZ < -10.0) wooperCabezaRotZ = -10.0;
                break;
            case 3: // 'm'/'M' -> Branquias Externas (Rotar X)
                wooperBranquiasRotX += incremento;
                break;
            case 4: // 'n'/'N' -> Branquias Pequeñas (Rotar Y)
                wooperBranquiasPequesRotY += incremento;
                break;
        }
    }
}

int cgvScene3D::getCurrentScene() const {
    return currentScene;
}

void cgvScene3D::setCurrentScene(int currentScene) {
    cgvScene3D::currentScene = currentScene;
}

void cgvScene3D::toggleAnimation() {
    animation = !animation;
}

void cgvScene3D::updateAnimation() {
    if(!animation){
        return;
    }
    if (currentScene == 3) {
        for (std::vector<Coin>::iterator it = coins.begin(); it != coins.end(); it++){
            it -> rot += 3.5;
        }
    }
    if (currentScene == 2) {
        timer += 0.05;
        if(objetoSeleccionado == 1){
            // La bandera sube y baja por el mástil
            baseRotY = timer*20;
            mastilRotY = -(timer*50);
            banderaPosY = -1.75 + (sin(timer)*1.75);
            logoRotZ = timer * 100;
        }
        else if (objetoSeleccionado == 2){
            wooperPatasRotZ = sin(timer)*15;
            wooperCabezaRotZ = -(sin(timer)*15);
            wooperBranquiasRotX = sin(timer*1.5)*30;
            wooperBranquiasPequesRotY = -(sin(timer * 1.5) * 60);
            wooperColaZ = sin(timer)*30;
        }
    }
}

bool cgvScene3D::isAnimationActive() {
    return animation;
}

//Para que haga lo que pedia el enunciado de que al seleccionar las teclas x y o z se añadieran o quitaran cajas pues como no tengo cajas voy a poner moneas, TODO preguntar a gema
void cgvScene3D::drawCoin(Coin& c) {
    // Las monedas NO son seleccionables

    if (selectionMode) return; // No dibujar monedas en modo selección para no estorbar

    GLfloat gold[] = {1.0f, 0.84f, 0.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, gold);

    glPushMatrix();
    glTranslatef(c.x, c.y, c.z);
    glRotatef(c.rot, 0, 1, 0); // Girar sobre su eje Y
    glScalef(0.3, 0.3, 0.05);  // Aplastada como una moneda
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void cgvScene3D::addCoin() {
    Coin c;

    // Posición central de la bandera
    const double flagX = 0.0;
    const double flagY = 0.0;
    const double flagZ = 0.0;

    // 1. Elegimos un ángulo aleatorio (en radianes)
    // rand() % 6283 / 1000.0 nos da un número entre 0.0 y 6.283 (aprox. 2*PI)
    double angle = (rand() % 6283) / 1000.0;

    // 2. Elegimos una distancia aleatoria desde el poste
    // Por ejemplo, entre -3.0 y 3.0 unidades de distancia
    double radius = -1.0 + (rand() % 600) / 100.0;  // Rango: [-1.0, 0.99]

    // 3. Calculamos X y Z usando trigonometría
    c.x = flagX + radius * cos(angle);
    c.z = flagZ + radius * sin(angle);

    // 4. HAcemos q floten
    c.y = flagY + (rand() % 400 / 100.0); // Rango: [0.0, 3.99]

    c.rot = 0;
    coins.push_back(c);
}

void cgvScene3D::removeCoin() {
    if (!coins.empty()) {
        coins.pop_back();
    }
}


//Seleccion

void cgvScene3D::applyColorMaterial(int id, float r, float g, float b) {
    if (selectionMode) {
        // MODO PICKING: El color es el ID. Intentare hacer si me da tiempo que el color se vea en la pantalla

        glColor3ub((GLubyte)id, 0, 0);
    } else {
        // MODO VISUALIZACIÓN:
        if (id == idToHighlight) {
            // Si es el objeto seleccionado -> AMARILLO
            GLfloat yellow[] = {1.0f, 1.0f, 0.0f};
            glMaterialfv(GL_FRONT, GL_EMISSION, yellow);
        } else {
            // Si no -> SU COLOR ORIGINAL
            GLfloat color[] = {r, g, b};
            glMaterialfv(GL_FRONT, GL_EMISSION, color);
        }
    }
}

void cgvScene3D::setSelectionMode(bool active) {
    selectionMode = active;
}

void cgvScene3D::setIdToHighlight(int id) {
    idToHighlight = id;
}

void cgvScene3D::controlarParteSceneC(int id, double incremento)
{
    switch(id)
    {
        case 1: // BASE
            baseRotY += incremento * 0.5; // Suave
            break;

        case 2: // MÁSTIL
            mastilRotY += incremento * 0.5;
            break;

        case 3: // BANDERA -> movimiento vertical
        {
            double nuevaY = banderaPosY + incremento * 0.05;

            if (nuevaY > 0) nuevaY = 0;
            if (nuevaY < -3.5) nuevaY = -3.5;

            banderaPosY = nuevaY;
            break;
        }

        case 4: // LOGO
            logoRotZ += incremento * 0.5;
            break;

        default:
            break;
    }
}

void cgvScene3D::applyTranslation(float dx, float dy, float dz) {
    int idx;

    // Si estamos en la escena 3, usamos el índice 2
    if (currentScene == 3) {
        idx = 2;
    } else {
        // Si no, usamos el objeto que tengamos seleccionado (0 o 1)
        idx = selected;
    }

    transforms[idx].tx += dx;
    transforms[idx].ty += dy;
    transforms[idx].tz += dz;
}

void cgvScene3D::applyScaling(float factor) {
    int idx;

    if (currentScene == 3) {
        idx = 2;
    } else {
        idx = selected;
    }

    transforms[idx].s *= factor;

    // Seguridad para que no desaparezca
    if (transforms[idx].s < 0.1f) {
        transforms[idx].s = 0.1f;
    }
}

void cgvScene3D::applyRotation(float rx, float ry, float rz) {
    int idx;

    if (currentScene == 3) {
        idx = 2;
    } else {
        idx = selected;
    }

    transforms[idx].rx += rx;
    transforms[idx].ry += ry;
    transforms[idx].rz += rz;
}

void cgvScene3D::renderSceneContent()
{
    if (axes)
        paint_axes();
    if (currentScene == 1)
        renderSceneA();
    else if (currentScene == 2)
        renderSceneB();
    else if (currentScene == 3)
        renderSceneC();
}