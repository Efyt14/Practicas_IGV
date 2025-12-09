#include "cgvScene3D.h"


// Constructor: inicializa transforms y modo
cgvScene3D::cgvScene3D() {
    modeRST = true;
    deferredMode = false;
    selected = 0;

    for (int i=0; i<3; i++) {
        transforms[i] = {0,0,0, 0,0,0, 1};
        ops[i].clear();
    }
}

/**
* Method for painting the coordinate axes by calling OpenGL functions
*/
void cgvScene3D::paint_axes ()
{
    GLfloat red[] = { 1,0,0,1.0 };
    GLfloat green[] = { 0,1,0,1.0 };
    GLfloat blue[] = { 0,0,1,1.0 };

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_EMISSION, red);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, green);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, blue);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void cgvScene3D::shoeBox() {
    GLfloat part_color[] = { 0,0.25,0 };
    GLfloat part_color2[] = { 0,0.3,0 };

    glMaterialfv(GL_FRONT, GL_EMISSION, part_color);

    glPushMatrix();
    glScalef(1, 1, 2);
    glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, part_color2);
    glPushMatrix();
    glTranslatef(0, 0.4, 0);
    glScalef(1.1, 0.2, 2.1);
    glutSolidCube(1);
    glPopMatrix();
}

void cgvScene3D::incrStacksX() {
    nStacksX++;
};

void cgvScene3D::decrStacksX() {
    if (nStacksX > 1)
        nStacksX--;
};

void cgvScene3D::incrStacksY() {
    nStacksY++;
};

void cgvScene3D::decrStacksY() {
    if (nStacksY > 1)
        nStacksY--;
};

void cgvScene3D::incrStacksZ() {
    nStacksZ++;
};

void cgvScene3D::decrStacksZ() {
    if (nStacksZ > 1)
        nStacksZ--;
};

/**
* Method with OpenGL calls to display the scene
* @param scene Identifier of the scene type to draw
* @pre Assumes the parameter value is correct
*/
void cgvScene3D::display(int scene)
{
    // clear the window and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Lights
    GLfloat light0[] = { 10, 8, 9, 1 }; // point light source
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    glPushMatrix(); // save the modeling matrix

    // paint the axes
    if(axes)
    { paint_axes();
    }

    // Scene selected via the menu (right-click)
    if(scene == SceneA)
    { renderSceneA();
    }
    else
    { if ( scene == SceneB )
        { renderSceneB();
        }
        else
        { if ( scene == SceneC )
            { renderSceneC();
            }
        }
    }

    glPopMatrix();
    glutSwapBuffers();
}
/**
* Renders scene A by calling OpenGL functions

void cgvScene3D::renderSceneA()
{
    shoeBox();
}
*/


/**
* Paints scene B by calling OpenGL functions

*/
/**
void cgvScene3D::renderSceneB ()
{
    GLfloat piece_color[] = { 0, 0, 0.5 };

    glMaterialfv(GL_FRONT, GL_EMISSION, piece_color);
    for (int yStack = 0; yStack < nStacksY; yStack++) {
        glPushMatrix();
        glTranslatef(0, yStack, 0);
        shoeBox();
        glPopMatrix();
    }
}
*/

/**
* Paints scene C by calling OpenGL functions
 */

/**
void cgvScene3D::renderSceneC ()
{
    GLfloat part_color[] = { 0,0,0.5 };
    GLfloat xSeparation = 1.5;
    GLfloat zSeparation = 2.5;

    glMaterialfv(GL_FRONT, GL_EMISSION, part_color);
    for (int yStacks = 0; yStacks < nStacksY; yStacks++) {
        for (int xStacks = 0; xStacks < nStacksX; xStacks++) {
            for (int zStacks = 0; zStacks < nStacksZ; zStacks++) {
                glPushMatrix();
                glTranslatef(xStacks * xSeparation, yStacks, zStacks * zSeparation);
                shoeBox();
                glPopMatrix();
            }
        }
    }
}
*/

void cgvScene3D::renderSceneA(){
    glScalef(2.0f,2.0f,2.0f);
    //Rotaciones para ver que me ha quedado de todos los lados bien
    //glRotated(90,0,0,0);
    glPushMatrix();
    // apply transforms for object 0 (SceneA)
    Transform &t = transforms[0];
    if (modeRST) {
    // To achieve application order R then S then T on the object, we call the GL functions in the order: Translate, Scale, Rotate.
        glTranslatef(t.tx, t.ty, t.tz);
        glScalef(t.s, t.s, t.s);
    // apply rotations so that X rotation happens first, then Y, then Z
        glRotatef(t.rz, 0.0f, 0.0f, 1.0f);
        glRotatef(t.ry, 0.0f, 1.0f, 0.0f);
        glRotatef(t.rx, 1.0f, 0.0f, 0.0f);
    } else {
    // apply operations in the order they were recorded
        for (std::function<void()>& op : ops[0]) {
            op();
        }
    }
    drawGun();
    glPopMatrix();
}

void cgvScene3D::renderSceneB(){
    //Rotaciones para ver que me ha quedado de todos los lados bien
    //glRotated(90,0,1,0);
    glPushMatrix();
    Transform &t = transforms[1];
    if (modeRST) {
        glTranslatef(t.tx, t.ty, t.tz);
        glScalef(t.s, t.s, t.s);
        glRotatef(t.rz, 0.0f, 0.0f, 1.0f);
        glRotatef(t.ry, 0.0f, 1.0f, 0.0f);
        glRotatef(t.rx, 1.0f, 0.0f, 0.0f);
    } else {
        for (std::function<void()>& op : ops[1]) {
            op();
        }
    }
    drawLock();
    glPopMatrix();}

void cgvScene3D::renderSceneC() {
    //Rotaciones para ver que me ha quedado de todos los lados bien
    //glRotated(90,0,1,0);
    glPushMatrix();
    Transform &t = transforms[2];
    if (modeRST) {
        glTranslatef(t.tx, t.ty, t.tz);
        glScalef(t.s, t.s, t.s);
        glRotatef(t.rz, 0.0f, 0.0f, 1.0f);
        glRotatef(t.ry, 0.0f, 1.0f, 0.0f);
        glRotatef(t.rx, 1.0f, 0.0f, 0.0f);
    } else {
        for (std::function<void()> &op: ops[2]) {
            op();
        }
    }
    drawWooper();
    glPopMatrix();
    }


/**
* Method to check whether the axes should be drawn or not
* @retval true If the axes should be drawn
* @retval false If the axes should not be drawn
*/
bool cgvScene3D::get_axes()
{ return axes;
}

/**
* Method to enable or disable axes drawing
* @param _ejes Indicates whether the axes should be drawn (true) or not (false)
* @post The state of the object changes with respect to axes drawing,
* according to the value passed as a parameter
*/
void cgvScene3D::set_axes(bool _axes )
{ axes = _axes;
}

// Pistola negra
void cgvScene3D::drawGun() { //Basada en la pistola de persona 5 royal

    // CUERPO / SLIDE (parte superior del armazón) -- Mas claro

    GLfloat grey[] = {0.15f, 0.15f, 0.15f};
    glMaterialfv(GL_FRONT, GL_EMISSION, grey);

    glPushMatrix();
    glTranslatef(0.6f, -0.15f, 0.0f);
    glScalef(1.8f, 0.18f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Color negro
    GLfloat black[] = { 0.0f, 0.0f, 0.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, black);

    // CAÑÓN (pieza alargada)
    glPushMatrix();
    glTranslatef(0.6f, -0.3f, 0.0f);
    glScalef(1.8f, 0.18f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // EMPUÑADURA
    glPushMatrix();
    glTranslatef(-0.3f, -0.8f, 0.0f);
    glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.28f, 0.9f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();


    // GATILLO (Accionador)
    glPushMatrix();
    glTranslatef(-0.055f, -0.45f, 0.0f);
    glRotated(90,1,0,0);
    glScalef(1.5f, 0.75f, 1.25f);
    glutSolidSphere(0.08f, 12, 6);
    glPopMatrix();

    // GUARDABISAGRA (esfera achatada como desencadenador / arco)
    glPushMatrix();
    glTranslatef(-0.05f, -0.45f, 0.0f);
    glScalef(0.1f, 0.25f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //Recubre Gatillo
    glPushMatrix();
    glTranslatef(0.0f, -0.45f, 0.0f);
    glScalef(1.55f,1.5f,1.2f);
    glutSolidTorus(0.035f, 0.115f, 30, 40);
    glPopMatrix();

    // Mirilla
    glPushMatrix();
    glTranslatef(-0.1f, -0.05f, 0.07f); // En el lateral del cuerpo/slide 1
    glRotated(90, 0, 1, 0);
    glScalef(0.1f, 0.05f, 0.025f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.05f, -0.07f); // En el lateral del cuerpo/slide 2
    glRotated(90, 0, 1, 0);
    glScalef(0.1f, 0.05f, 0.025f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.05f, 0.07f); // En el lateral del cuerpo/slide 3 (alzillo)
    glRotated(90, 0, 1, 0);
    glScalef(0.075f, 0.15f, 0.025f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, -0.05f, -0.07f); // En el lateral del cuerpo/slide 4 (alzillo 2)
    glRotated(90, 0, 1, 0);
    glScalef(0.075f, 0.15f, 0.025f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Punto de Mira (Delante)
    glPushMatrix();
    glTranslatef(1.4f, -0.05f, 0.0f); // En la punta del cañón
    glScalef(0.1f, 0.1f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Seguro (Detrás)
    glPushMatrix();
    glTranslatef(-0.28f, -0.07f, 0.0f); // Detrás del cuerpo/slide
    glutSolidSphere(0.05f,15,2);
    glPopMatrix();

    //Silenciador
    glMaterialfv(GL_FRONT, GL_EMISSION, grey);
    glPushMatrix();
    glTranslatef(1.47f,-0.3f,0.0f);
    glutSolidSphere(0.05f, 15,15);
    glPopMatrix();

    //Salida de la bala -- Formada por un toroide que represente la forma circular y una esfera que sea el boquete
    GLfloat white[] = { 0.3f, 0.3f, 0.3f};
    glMaterialfv(GL_FRONT, GL_EMISSION, white);
    glPushMatrix();
    glTranslatef(1.49f,-0.15f,0.0f);
    glRotated(90,0,1,0);
    glutSolidTorus(0.025f,0.025f,15,15);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glPushMatrix();
    glTranslatef(1.49f, -0.15f, 0.0f);
    glutSolidSphere(0.025f, 15, 15);
    glPopMatrix();
}

void cgvScene3D::drawLock() {
    GLfloat blue[] = {0.0f,0.0f,1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, blue);

    //Arco del candado
    glPushMatrix();
    glScalef(0.85f,1.35f,0.35f);
    glTranslatef(0.0f,0.75f,0.0f);
    glutSolidTorus(0.35f,0.8f,30,30);
    glPopMatrix();

    //Cuerpo del candado
    glPushMatrix();
    glScalef(1.0f,1.0f,0.5f);
    glutSolidCube(2.0f);
    glPopMatrix();

    //Cilindro para la llave del candado (Formado por un cirulo arriba y un rectangulo abajo) color blanco
    GLfloat white[] = {1.0f,1.0f,1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, white);


    //Esfera
    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.5f);
    glutSolidSphere(0.2f,22,22);
    glPopMatrix();

    //Rectangulo
    glPushMatrix();
    glScalef(0.5f,1.4f,1.0f);
    glTranslatef(0.0f,-0.15f,0.45f);
    glutSolidCube(0.3f);
    glPopMatrix();

}

void cgvScene3D::drawWooper() {
    GLfloat cian[] = {0.0f,0.8f,1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, cian);

    //Cabezon
    glPushMatrix();
    glTranslatef(0.0f,2.0f,0.0f);
    glScalef(1.5f,1.0f,1.0f);
    glutSolidSphere(1.0,25,25);
    glPopMatrix();

    //Cuerpo
    glPushMatrix();
    glScalef(1.0f,1.5f,1.0f);
    glutSolidSphere(1.0,25,25);
    glPopMatrix();

    //Cola
    glPushMatrix();
    glRotated(30,1,0,0);
    glScalef(0.5f,0.5f,1.5f);
    glTranslatef(0.0f,-1.5f,-0.65f);
    glutSolidSphere(1.0f,25,25);
    glPopMatrix();

    //Pata 1
    glPushMatrix();
    glScalef(1.5f,0.5f,0.5f);
    glTranslatef(-0.2f,-2.65f,0.0f);
    glutSolidSphere(0.5f,25,25);
    glPopMatrix();

    //Pata 2
    glPushMatrix();
    glScalef(1.5f,0.5f,0.5f);
    glTranslatef(0.2f,-2.65f,0.0f);
    glutSolidSphere(0.5f,25,25);
    glPopMatrix();

    //Branquias Internas
    GLfloat azul[] = {0.0f,0.0f,1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, azul);

    glPushMatrix();
    glScalef(1.5f,1.0f,1.0f);
    glTranslatef(0.0f,0.65f,0.6f);
    glutSolidSphere(0.4, 25,25);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5f,1.0f,1.0f);
    glTranslatef(0.0f,0.0f,0.65f);
    glutSolidSphere(0.45, 25,25);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5f,1.0f,1.0f);
    glTranslatef(0.0f,-0.65f,0.5f);
    glutSolidSphere(0.5, 25,25);
    glPopMatrix();


    GLfloat negro[] = {0.0f,0.0f,0.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, negro);
    //Ojo derecho
    glPushMatrix();
    glTranslatef(-0.7f,2.25f,0.75f);
    glutSolidSphere(0.25, 25,25);
    glPopMatrix();

    //Ojo Izqierdo
    glPushMatrix();
    glTranslatef(0.7f,2.25f,0.75f);
    glutSolidSphere(0.25, 25,25);
    glPopMatrix();

    //Boca
    GLfloat rosa[] = {1.0f, 0.0f, 0.5f};
    glMaterialfv(GL_FRONT, GL_EMISSION, rosa);

    glPushMatrix();
    glTranslatef(0.0f,1.8f,0.75f);
    glutSolidSphere(0.35, 25,25);
    glPopMatrix();

    //Branquias Externas
    GLfloat morado[] = {0.5f, 0.0f, 0.5f};
    glMaterialfv(GL_FRONT, GL_EMISSION, morado);

    glPushMatrix();
    glTranslatef(2.0f,2.0f,0.0f);
    glScalef(2.0f,0.5f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f,2.0f,0.0f);
    glScalef(2.0f,0.5f,0.5f);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.3f,2.0f,0.0f);
    glScalef(0.5f,2.0f,0.5f);
    glutSolidCube(0.35);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.3f,2.0f,0.0f);
    glScalef(0.5f,2.0f,0.5f);
    glutSolidCube(0.35);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8f,2.0f,0.0f);
    glScalef(0.5f,2.15f,0.5f);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f,2.0f,0.0f);
    glScalef(0.5f,2.15f,0.5f);
    glutSolidCube(0.4);
    glPopMatrix();
}


//Apartado 2

void cgvScene3D::applyTranslation(float dx, float dy, float dz) {
    if (deferredMode) {
        // Guardar pero no aplicar todavía
        ops[selected].push_back([=](){ transforms[selected].tx += dx;
            transforms[selected].ty += dy;
            transforms[selected].tz += dz; });
    } else {
        // Aplicar inmediatamente
        transforms[selected].tx += dx;
        transforms[selected].ty += dy;
        transforms[selected].tz += dz;
    }
}

void cgvScene3D::applyRotation(float rx, float ry, float rz) {
    if (deferredMode) {
        // Guardar la operación para aplicarla luego
        ops[selected].push_back([=]() {
            transforms[selected].rx += rx;
            transforms[selected].ry += ry;
            transforms[selected].rz += rz;
        });
    } else {
        // Aplicar inmediatamente
        transforms[selected].rx += rx;
        transforms[selected].ry += ry;
        transforms[selected].rz += rz;
    }
}

void cgvScene3D::applyScaling(float factor) {
    if (deferredMode) {
        // Guarda la operación de escala para ejecutarla en el render (orden pulsado)
        ops[selected].push_back([=]() {
            glScalef(factor, factor, factor);
        });
    } else {
        // Acumula escala homogénea en 's'
        transforms[selected].s *= factor;
    }
}


void cgvScene3D::renderSceneContent(int scene)
{
    if (axes)
        paint_axes();

    if (scene == SceneA)
        renderSceneA();
    else if (scene == SceneB)
        renderSceneB();
    else if (scene == SceneC)
        renderSceneC();
}