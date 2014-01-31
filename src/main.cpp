#include "precompiled.h"

sgct::Engine * gEngine;

void initOpenGL();
void calcPhysics();
void drawScene();

int main( int argc, char* argv[] )
{
    // // Allocate
    // gEngine = new sgct::Engine( argc, argv );

    // // Bind your functions
    // gEngine->setInitOGLFunction( initOpenGL );
    // gEngine->setPreSyncFunction( calcPhysics );
    // gEngine->setDrawFunction( drawScene );

    // // Init the engine
    // if( !gEngine->init() )
    // {
    //     delete gEngine;
    //     return EXIT_FAILURE;
    // }

    // // Main loop
    // gEngine->render();

    // delete gEngine;

    std::cout << "HELLO" << std::endl;

    exit( EXIT_SUCCESS );
}

void initOpenGL()
{
    // std::cout << PI << std::endl;
}

void calcPhysics()
{
    // TODO
}

void drawScene()
{
    // TODO
}