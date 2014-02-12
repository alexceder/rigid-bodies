#include "precompiled.h"

sgct::Engine *gEngine;
Scene *scene;

void initOpenGL();
void calcPhysics();
void drawScene();
void keyCallback(int key, int action);

bool stop = false;

int main( int argc, char* argv[] )
{
    // Allocate
    gEngine = new sgct::Engine( argc, argv );
    scene = new Scene();

    // Bind your functions
    gEngine->setInitOGLFunction( initOpenGL );
    gEngine->setPreSyncFunction( calcPhysics );
    gEngine->setDrawFunction( drawScene );
    gEngine->setKeyboardCallbackFunction( keyCallback );

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
    RigidBody *rb1 = new RigidBody(glm::vec2(0.0f, 0.0f), 0.0f, new Circle(0.3f));
    RigidBody *rb2 = new RigidBody(glm::vec2(0.15f, 0.9f), 0.0f, new Circle(0.15f));

    // Ground
    // RigidBody *rb3 = new RigidBody(glm::vec2(0.0f, -0.8f), 0.0f, new Box(1.6f, 0.1f));
    // rb3->_isStatic = true;
    // Ground
    //RigidBody *rb3 = new RigidBody(glm::vec2(0.0f, -0.2f), 0.0f, new Circle(0.5f));
    //rb3->_isStatic = true;

    // Fence
    // RigidBody *rb4 = new RigidBody(glm::vec2(-0.8f, -0.6f), 0.0f, new Box(0.1f, 0.2f));
    // rb4->_isStatic = true;
    // RigidBody *rb5 = new RigidBody(glm::vec2(0.8f, -0.6f), 0.0f, new Box(0.1f, 0.2f));
    // rb5->_isStatic = true;

    scene->addBody(rb1);
    scene->addBody(rb2);
    //scene->addBody(rb3);
    // scene->addBody(rb4);
    // scene->addBody(rb5);
}

void calcPhysics()
{
    scene->step();
}

void drawScene()
{
    // scene->step();
    scene->draw();
}

void keyCallback(int key, int action)
{
    // TODO
}
