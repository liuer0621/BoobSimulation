//
//  main.cpp
//  BoobSimulation
//
//  Created by Lana Sun on 3/9/15.
//  Copyright (c) 2015 Lana Sun. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include "objLoader.h"

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 350

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 50.0f;

//obj define
objLoader boob;

void init(void)
{
    //init obj boob
    boob.load("/Volumes/PERSONAL/Documents/Development/BoobSimulation/BoobSimulation/BoobSimulation/obj/boob.obj");
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLsizei)WINDOW_WIDTH/(GLsizei)WINDOW_HEIGHT, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //we reset the modelview matrix for every render
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //setup the camera
    gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    //draw a sphere
    glColor3f(1.0f, 1.0f, 1.0f);
    //glutSolidSphere(5.0, 10, 10);
    
    //draw the obj
    boob.drawObj();
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    //initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGB|GLUT_DOUBLE);
    
    //create window
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(50, 100);
    glutCreateWindow(argv[0]);
    init();
    
    //register callback
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    
    //openGL.Init
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
