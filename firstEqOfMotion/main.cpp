#include <iostream>
#include <GLUT/glut.h> // GLUT, include glu.h and gl.h

using std::cout, std::cin;

// Global variable
// GLfloat angle = 0.0f;  // Current rotational angle of the shapes
float vi, vf, acc, ti, tf;
GLfloat x = -1.50f,
        xIncrease,
        acceleration;

auto start = std::chrono::high_resolution_clock::now();

float time_value = 1.00f;
float t;

/* Initialize OpenGL Graphics */
void initGL()
{
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Called back when there is no other event to be handled */
void idle()
{
    glutPostRedisplay(); // Post a re-paint request to activate display()
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */




/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    cout << "please enter a intial velocity: ";
    cin >> vi;
    cout << "Please enter intial time: ";
    cin >> ti;
    cout << "please enter final time: ";
    cin >> tf;
    cout << "please enter acceleration of that body: ";
    cin >> acc;
    vf = vi + acc * (tf - ti);
    start = std::chrono::high_resolution_clock::now();

    xIncrease = vi * 0.0001f,
    acceleration = acc * 0.0001f;
    t = tf - ti;

    return 0;
}