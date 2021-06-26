#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string>
#include <ctime>
#define ROWS 40.0
#define COLUMNS 40.0
#define MAX 60
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2
#define fps 20

using namespace std;
bool game_over=false;
int score=0;
void unit(int,int);
void random(int &,int &);
void output(int , int , char *);
void drawstring(int , int , char *,void* );
bool food=true;
int gridy=40,gridx=40;
int sDirection = RIGHT;
int foodx,foody;
int posx[MAX+1]={20,20,20,20,20};
int posy[MAX+1]={20,19,18,17,16};
int length=5,df=10;
void keyboard(unsigned char key,int x,int y)
{

   if(df==10 && key==13)
    df=0;
   else if((df==0 )&& key==27)
    df=10;
   else if((df==0 )&& key=='1')
    df=1;
   else if(df==0 && key=='2')
   df=2;
   else if(df==0 && key=='3')
   df=3;
   else if(key==27)
   df=0;
  glutPostRedisplay ();
}

void frontscreen(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1,1,1);
    drawstring(30,3," Press ENTER to go To next screen",GLUT_BITMAP_HELVETICA_18 );
	drawstring(3,3,"Maximize window for better view",GLUT_BITMAP_HELVETICA_12);
    glColor3f(1,1,0);
	output(19,20,"SRMIST");
	glColor3f(1,1,0);
	output(12,18,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1,0,1);
	output(12,36,"");
	glColor3f(0,1,0.5);
	output(15,38,"\"SNAKE GAME USING OPENGL\"");
	glColor3f(1,0,1);
	output(28,9,"By :");
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex2f(13,37);
	glVertex2f(26,37);
	glEnd();
	glColor3f(1,0,0);
	output(30,9,"AAYUSH SAXENA");
    output(40,80,"");
	glFlush();

}
void startscreen()
{

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,1.0,0.0);
output(16,30,"WELCOME TO THE GAME OF SNAKE ");
output(18,26,"1.NEW GAME");
output(18,24,"2.INSTRUCTIONS");
output(18,22,"3.QUIT");
glFlush();
}

void instructions()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,0.0);
    output(18,38,"INSTRUCTIONS:");
	glBegin(GL_LINES);
	glVertex2f(17,37);
	glVertex2f(24,37);
	glEnd();
	glColor3f(0,1,0);
  output(8,30,"* Use your cursor keys: up, left, right, and down.");
  output(8,28,"* Don't run the snake into the wall, or its own tail: you'll die.");
  output(8,26,"* Eat the yellow food to gain points");
  output(8,24,"* PRESS ESC TO GO TO MAIN MENU");
   glFlush();
}

void output(int x, int y, char *string)
{
      int len, i;

           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
			}
}

void drawstring(int x, int y, char *string,void *font)
{
      int len, i;

           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(font,string[i]);
			}
}

void draw_grid()
{
    //left line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1,0,0);
        glVertex2d(0,0);
         glColor3d(1,0,0);
        glVertex2d(1,0);
         glColor3d(1,0,0);
        glVertex2d(1,40);
         glColor3d(1,0,0);
        glVertex2d(0,40);
    glEnd();// ending drawing
   //right line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1,0,0);
        glVertex2d(39,0);
         glColor3d(1,0,0);
        glVertex2d(40,0);
         glColor3d(1,0,0);
        glVertex2d(40,40);
         glColor3d(1,0,0);
        glVertex2d(39,40);
    glEnd();// ending drawing
   //top line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1,0,0);
        glVertex2d(0,39);
         glColor3d(1,0,0);
        glVertex2d(40,39);
         glColor3d(1,0,0);
        glVertex2d(40,40);
         glColor3d(1,0,0);
        glVertex2d(0,40);
    glEnd();// ending drawing

    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1,0,0);
        glVertex2d(0,0);
         glColor3d(1,0,0);
        glVertex2d(40,0);
         glColor3d(1,0,0);
        glVertex2d(40,1);
         glColor3d(1,0,0);
        glVertex2d(0,1);
    glEnd();// ending drawing

}
void draw_snake()
{
    for(int i =length-1;i>0;i--)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
    }

            switch(sDirection)
            {
            case UP:
                posy[0]++;
                break;
            case DOWN:
                posy[0]--;
                break;
            case RIGHT:
                posx[0]++;
                break;
            case LEFT:
                posx[0]--;
                break;
            }
            for(int i=0;i<length;i++)
            {
                if(i==0)
                {
                    glColor3f(0.0,1.0,0.0);
                }
                else
                {
                    glColor3f(0.0,1.0,1.0);
                 }
                     glBegin(GL_QUADS);
                         glVertex2d(posx[i],posy[i]);
                         glVertex2d(posx[i]+1,posy[i]);
                         glVertex2d(posx[i]+1,posy[i]+1);
                         glVertex2d(posx[i],posy[i]+1);
                      glEnd();

            }
            if(posx[0]==0||posx[0]==gridx-1||posy[0]==0||posy[0]==gridy-1) //snake touches red boundary
                game_over=true;
            else if(posx[0]==foodx && posy[0]==foody)
            {    length++;
                food=true;
                score++;
                if(length>MAX)
                   length=MAX;

            }
            for(int j=1;j<length;j++)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=true;
            }

}
void draw_food()
{
    if(food)
      random(foodx,foody);
     food=false;
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_QUADS);
        glVertex2d(foodx,foody);
        glVertex2d(foodx+1,foody);
        glVertex2d(foodx+1,foody+1);
        glVertex2d(foodx,foody+1);
    glEnd();
}

void random(int &_min,int &_max)
{


        srand(time(NULL));
        int a=0,b=0;
        a=gridx-2;
        b=gridy-2;
        int m=1;

    _min=m+rand()%(a-m);
    _max=m+rand()%(b-m);

}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

//Callbacks
void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); //we are clearing color for every buffer so that our screen should get color what we set in init() function
    if(df==10)
     frontscreen();

    else  if(df==0)
      startscreen();
    else if(df==1)
     {

    draw_grid();
    draw_snake();
    draw_food();
    if(game_over)
    {   string fscore;
        string tmp=to_string(score);
        string text = "Your score : "+tmp;
        int n = text.length();
        char char_array[n + 1];
        strcpy(char_array, text.c_str());
        MessageBox(NULL,char_array,"Game Over",MB_OK);
        exit(0);

    }
     }

    else if(df==2)
        instructions();
    else if(df==3)
     {
      exit(0);
     }
    glFlush();
glutSwapBuffers();// swap the buffers as we used double buffer mode

}

void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h); //view port is the area in which objects are drawn
    glMatrixMode(GL_PROJECTION); // for setting projection we need to be in projection mode
    glLoadIdentity(); //this make sure that no changes are made to matrix

    gluOrtho2D(0,COLUMNS,0,ROWS); //set projection-mapping column*row coordinate system in our window

    glMatrixMode(GL_MODELVIEW); //setting back to model view
    glLoadIdentity();
}
void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/fps,timer_callback,0);
}
void keyboard_callback(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);//Initializing GLUT
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);//Initializing Display Mode
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT)-100);// opens window at max w,h
    glutCreateWindow("SNAKE");//Name of window
    glutDisplayFunc(display_callback);//sets display callback for current window
    glutReshapeFunc(reshape_callback);//mainly used for setting view port and projection in reshape_callback
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0,timer_callback,0);
    init();//initialization function
    glutMainLoop(); //all the processing will start by calling this line,it holds window on screen
    return 0;
}

