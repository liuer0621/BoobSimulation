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
#define ROTFACTOR 2.0f
#define XLATEFACTOR 2.0f

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = -10.0f;

//obj define
objLoader boob;

//camera movement
int Button;
float MouseX,MouseY,ThetaX,ThetaY,Pan,Tilt,Approach;

void init(void)
{
    //init obj boob
    boob.load("/Volumes/PERSONAL/Documents/Development/BoobSimulation/BoobSimulation/BoobSimulation/obj/boob.obj");

    //initial camera move attributes
    ThetaX = 0.0f;
    ThetaY = 0.0f;
    MouseX = 0.0f;
    MouseY = 0.0f;
    Pan = 0.0f;
    Tilt = 0.0f;
    Approach = 0.0f;
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
    
    //lighting setup
    GLfloat LightAmbient[] = {0.3f,0.3f,0.3f,1.0f};
    GLfloat LightDiffuse[] = {0.8f,0.8f,0.8f,1.0f};
    GLfloat LightSpecular[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat LightPosition[] = {10.0f,10.0f,0.0f,0.0f};
    glShadeModel(GL_SMOOTH); //emable smooth shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    
    //two sides lighting
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_CULL_FACE); //cut the invisible face
    
    //rotate the camera
    glTranslatef(cameraX, cameraY, cameraZ);
    glRotatef(Pan, 0.0f, 1.0f, 0.0f);
    glRotatef(Tilt, 1.0f, 0.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glTranslatef(0.0f, 0.0f, Approach);
    
    //rotate the object
    glRotatef(ThetaY, 0.0f, 1.0f, 0.0f);
    glRotatef(ThetaX, 1.0f, 0.0f, 0.0f);
    
    //draw a sphere
    glColor3f(1.0f, 1.0f, 1.0f);
    //glutSolidSphere(5.0, 10, 10);
    
    //draw the obj
    boob.drawObj();
    
    glutSwapBuffers();
}


void handleButtons(int button, int state, int x, int y)
{
    if(state == GLUT_UP)
        Button = 0;  // no button pressed
    else
    {
        MouseY = -y;  //invert y window coordinate to correspond with openGL
        MouseX = x;
        
        Button = button; //store which button pressed
    }
}


void handleMotion(int x, int y)
{
    //left button - right : positive rotation about model's y axis ; left : negative rotation about model's y axix
    //left button - up : negative rotation about model's x axis, left: positive rotation about model's x axis
    
    int delta;
    
    y = -y;
    int dy = y - MouseY;
    int dx = x - MouseX;
    
    switch(Button)
    {
        case GLUT_LEFT_BUTTON:
            ThetaX -= ROTFACTOR * dy;
            ThetaY += ROTFACTOR * dx;
            glutPostRedisplay();
            break;
        
        case GLUT_MIDDLE_BUTTON:
            Pan -= ROTFACTOR * dx;
            Tilt += ROTFACTOR * dy;
            glutPostRedisplay();
            break;
            
        case GLUT_RIGHT_BUTTON:
            delta = (abs(dx) > abs(dy)? dx: dy);
            Approach -= XLATEFACTOR * delta;
            glutPostRedisplay();
            break;
    }
    
    MouseX = x;
    MouseY = y;
}

void handlekey(unsigned char key, int x, int y)
{
    
    std::cout << "cameraX " << cameraX << "\n";
    std::cout << "cameraZ " << cameraZ << "\n";

    switch (key) {
        
        case 'j' :
            cameraX -= 100;
            break;
        
        case 'l' :
            cameraX += 100;
            break;
            
        case 'i' :
            cameraZ += 100;
            break;
            
        case 'k' :
            cameraZ -= 100;
            break;
        
        case 'q':
        case 27:
            exit(0);
            break;
            
        default:
            return;
    }
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
    glutMouseFunc(handleButtons);
    glutMotionFunc(handleMotion);
    glutKeyboardFunc(handlekey);
    
    //openGL.Init
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    std::cout << "Hello, World!\n";
    
    glutMainLoop();
    
    
       return 0;
}
