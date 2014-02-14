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
    // RigidBody *rb1 = new RigidBody(glm::vec2(0.0f, 0.0f), 0.0f, new Circle(0.2f));
    // rb1->_isStatic = true;

    // Ground
    RigidBody *rb3 = new RigidBody(glm::vec2(0.0f, -0.8f), 0.0f, new Box(2.5f, 0.2f));
    rb3->_isStatic = true;

    // // Fence
    // RigidBody *rb4 = new RigidBody(glm::vec2(-0.75f, -0.4), 0.0f, new Box(0.1f, 0.2f));
    // rb4->_isStatic = true;
    // RigidBody *rb5 = new RigidBody(glm::vec2(0.75f, -0.4), 0.0f, new Box(0.1f, 0.2f));
    // rb5->_isStatic = true;

    // scene->addBody(rb1);
    scene->addBody(rb3);
    // scene->addBody(rb4);
    // scene->addBody(rb5);

    int sign = 1;
    for (float f = 0.8f; f < 10.0f; f += 0.2f)
    {
        sign *= -1;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        RigidBody *temp = new RigidBody(glm::vec2(sign * 0.2f + r * 0.01f, f), 0.0f, new Circle(0.1f));
        scene->addBody(temp);
    }
}

void calcPhysics()
{
    // scene->step();
}

void drawScene()
{
    scene->step();
    scene->draw();
}

void keyCallback(int key, int action)
{
    // TODO
}
