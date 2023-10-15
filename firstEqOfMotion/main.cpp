#include <iostream>
#include <GLUT/glut.h> // GLUT, include glu.h and gl.h

using std::cout, std::cin;

// Global variable
int option;

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
void display()
{

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    if (duration.count() > time_value)
    {
        if (time_value > t)
        {
            if (option == 1)
            {
                cout << "value for final velocity is: " << vf << "m/s";
            }
            else
            {
                float t = tf - ti;
                float x = vi * t + 0.5f * acc * t * t;
                cout << "Displacement of body is: "
                     << x;
            }
            cin >> t;
            exit(0);
        }
        time_value++;
        xIncrease += acceleration;
    }
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);   // To operate on Model-View matrix
    glLoadIdentity();             // Reset the model-view matrix

    glPushMatrix();              // Save model-view matrix setting
    glTranslatef(x, 0.4f, 0.0f); // Translate
                                 //    glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
    glBegin(GL_QUADS);           // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(-0.3f, 0.3f);
    glEnd();
    glPopMatrix(); // Restore the model-view matrix

    glutSwapBuffers(); // Double buffered - swap the front and back buffers

    // Change the rotational angle after each display()
    //    angle += 0.2f;
    x += xIncrease;
}

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
    cout << "\t\tWelcome to Graphical representation for equation of motion\n";
    cout << "What do you want to find: \n"
         << "1.Final Velocity\n2.Displacement of body\n";
    cin >> option;
    cout << "Please provide following information of body" << std::endl;
    cout << "please enter a intial velocity(m/s): ";
    cin >> vi;
    cout << "Please enter intial time(s): ";
    cin >> ti;
    cout << "please enter final time(s): ";
    cin >> tf;
    cout << "please enter acceleration of that body(m/s-2): ";
    cin >> acc;
    vf = vi + acc * (tf - ti);
    start = std::chrono::high_resolution_clock::now();

    xIncrease = vi * 0.0001f,
    acceleration = acc * 0.0001f;
    t = tf - ti;
    glutInit(&argc, argv);                           // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);                // Enable double buffered mode
    glutInitWindowSize(1400, 720);                   // Set the window's initial width & height - non-square
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