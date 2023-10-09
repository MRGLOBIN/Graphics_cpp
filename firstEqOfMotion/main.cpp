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


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();
    if (width >= height)
    {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

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
    glutInit(&argc, argv);                           // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);                // Enable double buffered mode
    glutInitWindowSize(1400, 720);                    // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50);                  // Position the window's initial top-left corner
    glutCreateWindow("Animation via Idle Function"); // Create window with the given title
    glutDisplayFunc(display);                        // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);                        // Register callback handler for window re-size event
    glutIdleFunc(idle);                              // Register callback handler if no other event
    initGL();                                        // Our own OpenGL initialization
    glutMainLoop();                                  // Enter the infinite event-processing loop
    cin >> t;
    return 0;
}