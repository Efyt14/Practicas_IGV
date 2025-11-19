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
cgvScene3D::cgvScene3D ()
{  //Section B: Insert code to create a cylinder
    mesh = new cgvCylinder(1.0f, 1.0f, 40, 2);
    axes = true;
    rotX = rotY = rotZ = 0.0f;

    currentScene = 2;

    // TODO: Initialize attributes for controlling the model's degrees of freedom
    x = 0;
    y = 0;
    z = 0;
    z2 = 0;

    objetoSeleccionado = 1;
    timer = 0.0;
}

/**
 * Destructor
 */
cgvScene3D::~cgvScene3D ()
{  if ( mesh != nullptr )
    {  delete mesh;
        mesh = nullptr;
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
    //FIXME buscar marron oscuro muy oscuro
    GLfloat color_cube[] = {0.35, 0.16, 0.14};

    glMaterialfv(GL_FRONT, GL_EMISSION, color_cube);

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
    GLfloat mastilColor[] = {0.3,0.3,0.3};

    glMaterialfv(GL_FRONT,GL_EMISSION,mastilColor);

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
    GLfloat esferaColor[] = {1.0,1.0,0.0};

    glMaterialfv(GL_FRONT, GL_EMISSION,esferaColor);

    glPushMatrix();
    glTranslatef(0.0,6,0.0);
    glutSolidSphere(lenght, 25,25);
    glPopMatrix();
}

void cgvScene3D::drawFlag(float lenght) {
    GLfloat flagColor[] = {1.0,0.0,0.0};

    glMaterialfv(GL_FRONT, GL_EMISSION,flagColor);

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

//TODO diamante aka, cuadrado aplastado y rotado jaja lol
void cgvScene3D::drawLogo(float lenght) {
    GLfloat flagColor[] = {0.3,0.3,0.3};

    glMaterialfv(GL_FRONT, GL_EMISSION,flagColor);

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
    GLfloat mesh_colour[] = { 0, 0.25, 0 };
    // create lights   // point light to display the cube
    GLfloat light0[4] = { 2.0, 2.5, 3.0, 1 };

    // the light is placed here if it remains fixed and does not move with the scene
    glLightfv ( GL_LIGHT0, GL_POSITION, light0 );
    glEnable(GL_LIGHT0);

    // create the model
    glPushMatrix(); // save the modelling matrix

    // paint the axes
    if (axes) paint_axes();

    // create the model
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // the light is placed here if it moves with the scene
    glLightfv(GL_LIGHT0,GL_POSITION,light0);
    glMaterialfv ( GL_FRONT, GL_EMISSION, mesh_colour );

    // Section B: the following call must be replaced by the call to the mesh visualisation method
    /*GLUquadric *cyl = gluNewQuadric ();
    gluCylinder ( cyl, 1, 1, 1, 20, 5 );
    gluDeleteQuadric ( cyl );
    cyl = nullptr;
     */
    switch (currentScene)
    {
        case 1: // Escena A
            if (mesh != nullptr)
                mesh->display();
            break;

        case 2: // Escena B
            //Objeto 1

            glScaled(0.2, 0.2, 0.2);

            glPushMatrix();
            drawWooper();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(-5, 0, 0); // Posiciona  el conjunto de la bandera

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
            break;

        case 3: // Escena C
            glScaled(0.2, 0.2, 0.2);
            glPushMatrix();
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
            break;
    }
    glPopMatrix (); // restores the modelling matrix
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
    timer += 0.05;

    if(objetoSeleccionado == 1){
        // La bandera sube y baja por el mástil (usamos sin() para oscilar). 3.5 (limite)/2 = 1.75
        baseRotY = timer*20;
        mastilRotY = -(timer*50);
        banderaPosY = -1.75 + sin(timer)*1.75;
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