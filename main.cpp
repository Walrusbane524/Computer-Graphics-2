#include <GL/freeglut.h>

void myDisplay(){
    // Clear the viewport
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //OpenGL draw calls here

    //Swap buffers
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: //ESC
            glutLeaveMainLoop();
            break;
    }
    glutPostRedisplay();
}

void myKeyboard2(int key, int x, int y){
    // Handle keyboard input here
}

void myMouse(int button, int state, int x, int y){
    // Handle mouse buttons here
}

void myMouseMotion(int x, int y){
    // Handle mouse motion here while a button is down
}

void myMousePassive(int x, int y){
    // Handle mouse motion here while no button is down
}

void myReshape(int x, int y){
    // do what you want when window size changes
}

float redValue = 0.0f;
bool increasing = true;

void myIdle(){
    // Handle animations here

    // Example animation:

    const float step = 0.01f; // Rate of color change

    // If red component is increasing and hasn't reached 1.0 yet
    if (increasing && redValue < 1.0f) {
        redValue += step;
    }

    // If red component is decreasing and hasn't reached 0.0 yet
    else if (!increasing && redValue > 0.0f) {
        redValue -= step;
    }

    // If red component has reached its limit, change direction
    else {
        increasing = !increasing;
    }

    glClearColor(redValue, 0, 0, 0);

    // Tell GLUT to redraw
    glutPostRedisplay();
}

int main(int argc, char** argv){

    // 1. Initializations
    // Initialize glut
    glutInit(&argc, argv);

    // Create a window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    // Double buffering, RGBA and Depth buffers
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutCreateWindow("Window title");

    // Register display callback function
    glutDisplayFunc(myDisplay);

    // Register keyboard callback function
    glutKeyboardFunc(myKeyboard);

    // Register special keyboard callback
    glutSpecialFunc(myKeyboard2);

    // Register mouse callback function
    glutMouseFunc(myMouse);

    // Register mouse motion callback
    glutMotionFunc(myMouseMotion);

    // Register mouse "passive" motion
    glutPassiveMotionFunc(myMousePassive);

    // Register window reshape callback
    glutReshapeFunc(myReshape);

    // Register idle callback function
    glutIdleFunc(myIdle);

    // 2. OpenGL Initializations
    // Set background color
    glClearColor(0, 0, 0, 0);

    // 3. Call main loop
    glutMainLoop();
    return 0;
}