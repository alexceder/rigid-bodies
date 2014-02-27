#include "precompiled.h"


sgct::Engine *gEngine;
Scene *scene;

void initOpenGL();
void calcPhysics();
void drawScene();
void keyCallback(int key, int action);
void mouseCallback(int button, int action);

bool stop = false;
bool mouseLeftButton = false;
double  mousePos[] = {0.0f, 0.0f};

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
    gEngine->setMouseButtonCallbackFunction( mouseCallback );

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
    RigidBody *rb3 = new RigidBody(glm::vec2(0.0f, -0.8f), 0.0f, new Box(2.4f, 0.2f));
    rb3->setStatic(true);

    // // Fence
    RigidBody *rb4 = new RigidBody(glm::vec2(-1.1f, -0.2), 0.0f, new Box(0.2f, 0.5f));
    rb4->setStatic(true);
    RigidBody *rb5 = new RigidBody(glm::vec2(1.1f, -0.2), 0.0f, new Box(0.2f, 0.5f));
    rb5->setStatic(true);

    // scene->addBody(rb1);
    scene->addBody(rb3);
    scene->addBody(rb4);
    scene->addBody(rb5);

    int sign = 1;
    for (float f = 0.8f; f < 5.0f; f += 0.2f)
    {
        sign *= -1;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        RigidBody *temp = new RigidBody(glm::vec2(sign * 0.2f + r * 0.01f, f), 0.0f, new Circle(0.1f*r + 0.1f));
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

void mouseCallback(int button, int action)
{
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseLeftButton = (action == GLFW_PRESS ? true : false);
            if(mouseLeftButton == true)
            {
                sgct::Engine::getMousePos(0, &mousePos[0], &mousePos[1]);
                double tempX = (mousePos[0]/960 - 0.5) * 3.56;
                double tempY = (-mousePos[1]/540 + 0.5) * 2;
                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                RigidBody *temp1 = new RigidBody(glm::vec2(tempX, tempY), 0.0f, new Circle(0.1f*r + 0.1f));
                scene->addBody(temp1);
            }
        break;
    }
}

void keyCallback(int key, int action)
{
    // TODO
}
