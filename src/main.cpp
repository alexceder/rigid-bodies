#include "precompiled.h"

sgct::Engine *gEngine;
Scene *scene;

void initOpenGL();
void calcPhysics();
void drawScene();

int main( int argc, char* argv[] )
{
    // Allocate
    gEngine = new sgct::Engine( argc, argv );
    scene = new Scene();

    // Bind your functions
    gEngine->setInitOGLFunction( initOpenGL );
    gEngine->setPreSyncFunction( calcPhysics );
    gEngine->setDrawFunction( drawScene );

    // Init the engine
    if( !gEngine->init() )
    {
        delete gEngine;
        return EXIT_FAILURE;
    }

    // Main loop
    gEngine->render();

    delete gEngine;

    exit( EXIT_SUCCESS );
}

void initOpenGL()
{
    // Dynamic objects
    RigidBody *rb1 = new RigidBody(glm::vec2(0.2f, 0.0f), 0.0f, new Circle(0.2f));
    RigidBody *rb2 = new RigidBody(glm::vec2(0.05f, 0.5f), 0.0f, new Circle(0.1f));

    // Ground
    RigidBody *rb3 = new RigidBody(glm::vec2(-0.2f, 0.0f), 0.0f, new Box(glm::vec2(-0.8, -0.8), glm::vec2(0.8, -0.9)));
    rb3->_isStatic = true;

    // Fence
    RigidBody *rb4 = new RigidBody(glm::vec2(-0.2f, 0.0f), 0.0f, new Box(glm::vec2(-0.8, -0.5), glm::vec2(-0.7, -0.75)));
    rb4->_isStatic = true;
    RigidBody *rb5 = new RigidBody(glm::vec2(-0.2f, 0.0f), 0.0f, new Box(glm::vec2(0.8, -0.5), glm::vec2(0.7, -0.75)));
    rb5->_isStatic = true;

    scene->addBody(rb1);
    scene->addBody(rb2);
    scene->addBody(rb3);
    scene->addBody(rb4);
    scene->addBody(rb5);
}

void calcPhysics()
{
    scene->step();
}

void drawScene()
{
    scene->draw();
}
