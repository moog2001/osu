#include <windows.h>
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES // for C


static int width = 600;
static int height = 800;

static int cellsSize = 20;


struct Grid
{
    float x;
    float y;
};
typedef struct Grid Grid;

Grid initialFood;
int refreshRate = 10;

float time = 20;
float speed = 0.1;

int lives= 3;

bool started = false;

Grid grid[20][20];


void randomFood()
{
    Grid tempFood;
    tempFood.x = rand() % 20;
    tempFood.y = rand() % 20;
    if(tempFood.x != initialFood.x && tempFood.y != initialFood.y)
    {
        initialFood = tempFood;
    }
    else
    {
        randomFood();
    }
}
void food()
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex2f(initialFood.x, initialFood.y);
    glVertex2f(initialFood.x, initialFood.y+1);
    glVertex2f(initialFood.x+1, initialFood.y+1);
    glVertex2f(initialFood.x+1, initialFood.y);
    glEnd();
}

void start()
{
    started = true;
    glPushMatrix();
    for (int i =0 ; i < 20; i++)
    {
        for (int j =0; j <20 ; j++)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2f(grid[i][j].x, grid[i][j].y);
            glVertex2f(grid[i][j].x, grid[i][j].y+1);
            glVertex2f(grid[i][j].x+1, grid[i][j].y+1);
            glVertex2f(grid[i][j].x+1, grid[i][j].y);
            glEnd();
        }
    }
    glPopMatrix();

    glPushMatrix();
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex2f(0,22);
    glVertex2f(time,22);
    glVertex2f(time,21);
    glVertex2f(0,21);
    glEnd();
    glPopMatrix();

     glPushMatrix();
     glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2f(9,-2);
    glVertex2f(9+lives,-2);
    glVertex2f(9+lives,-1);
    glVertex2f(9,-1);
    glPopMatrix();

    glPushMatrix();
    food();
    glPopMatrix();

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glLineWidth(2);
    glPointSize(10);

    if(!started)
    {

        glPushMatrix();
        glPolygonMode(GL_FRONT,GL_FILL);
        glColor3f(0,1,0);
        glBegin(GL_QUADS);
        glVertex2f(2,9);
        glVertex2f(2,11);
        glVertex2f(5,11);
        glVertex2f(5,9);
        glEnd();
        glColor3f(1,1,0);
        glBegin(GL_QUADS);
        glVertex2f(8.5,9);
        glVertex2f(8.5,11);
        glVertex2f(11.5,11);
        glVertex2f(11.5,9);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex2f(15,9);
        glVertex2f(15,11);
        glVertex2f(18,11);
        glVertex2f(18,9);
        glEnd();
        glPopMatrix();
    }
    else
    {
        start();
    }




    glutSwapBuffers();
}


void timer()

{
    if(started)
    {
        time-=speed;
        if(time<0 && lives >= 0)
        {
            time = 20;
            lives --;
        }
        if(lives < 0)
        {
            exit(0);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}
void keyboard(unsigned char key,int x, int y)
{
    switch(key)
    {
    case 'q':
        exit(0);
        break;
    }
}
void ChangeSize(GLsizei w, GLsizei h)
{
    // Set Viewport to window dimensions
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,20,-3,23);
    glMatrixMode(GL_MODELVIEW);


}
mouse (int button, int state,int x, int y)
{



    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(!started)
        {
            if(y > 18.5*20 && y < 23.5*20)
            {
                if(x < 7.5*20 && x > 3*20)
                {
                    speed = 0.1;
                    started = true;

                }
                else if(x > 11.5*20 && x < 17.5*20)
                {
                    speed = 0.2;
                    started = true;
                }
                else if(x > 22.5*20 && x < 27*20)
                {
                    speed = 0.4;
                    started = true;
                }
            }
        }
        else
        {

            if(x > initialFood.x*30 && x < (initialFood.x+1)*30 && y > (19-initialFood.y)*30 && (19-initialFood.y+1)*30)
            {
                speed+=0.005;
                time = 20;
                randomFood();
            }
            else{
                time-=2;
            }
        }
    }

}

int main(int argc, char* argv[])
{
    MessageBox(0, "Aim game\n Nogoon - Amarhan \n Shar - Engiin \n Ulaan - Hetsuu \nNogoon dorvoljndeer daraarai", "Introduction", 0);
    int cellOffsetX = 0;
    int cellOffsetY = 0;

    for(int i = 0; i < 20; i++)
    {


        for(int j = 0; j < 20; j++)
        {
            grid[i][j].x = cellOffsetX;
            grid[i][j].y = cellOffsetY;
            cellOffsetX += 1;
        }
        cellOffsetY+=1;
        cellOffsetX = 0;
    }


    randomFood();
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Snake");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(500, timer, 0);
    glClearColor(0, 0, 0, 1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
