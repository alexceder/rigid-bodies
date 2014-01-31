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
    // ..
    RigidBody *rb = new RigidBody(glm::vec2(0.0f, 0.0f), 0.0f, new Circle(0.5f));

    scene->addBody(rb);
}

void calcPhysics()
{
    // scene->step();
}

void drawScene()
{
    scene->draw();
}
