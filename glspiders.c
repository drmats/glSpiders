// ...
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


GLfloat camera_rotation_angle;
GLfloat floor_position;
GLdouble spider_leg_angle;
GLdouble ant_angle;
GLdouble spider2_movement;
GLdouble spider3_angle;

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   camera_rotation_angle = 0.0;
   floor_position = -5.0;
   spider_leg_angle = 0.0;
   ant_angle = 0.0;
   spider2_movement = 0.0;
   spider3_angle = 0.0;
}

void leg(GLdouble o, GLdouble s){
    int a=0;

    glPushMatrix();
      glRotatef(-27, 1.0, 0.0, 0.0);
      glRotatef((s*spider_leg_angle)+o, 0.0, 0.0, 1.0);
      glPushMatrix();      
        glRotatef(-15.0, 1.0, 0.0, 0.0);
        glRotatef(-((s*spider_leg_angle)+o), 0.0, 0.0, 1.0);
        glColor3f(1.0, 0.2, 0.2);
        glutWireCone(0.04, 1.2, 6, 6);

        glTranslatef(0.0, 0.0, 1.2);
        if((spider_leg_angle)>=0 && (spider_leg_angle)<180.0)
          a=-((spider_leg_angle)/4);
        else
          a=-((360-(spider_leg_angle))/4);
        glRotatef(70+a, 1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 1.0);
        glutWireCone(0.02, 1.0, 6, 6);

        glTranslatef(0.0, 0.0, 1.0);
        glRotatef(50+a/2, 1.0, 0.0, 0.0);
        glColor3f(0.5, 0.5, 1.0);
        glutWireCone(0.01, 0.7, 6, 6);
      glPopMatrix();
    glPopMatrix();
}

void tarantula(void){
  glPushMatrix();
    //belly and head
    glPushMatrix();
      glScalef(1.0, 0.7, 1.3);
      glColor3f(1.0, 0.2, 0.2);
      glutWireSphere(0.2, 12, 12);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0, 0.0, 0.2*1.3+0.06);
      glColor3f(0.5, 0.5, 1.0);
      glutWireSphere(0.06, 6, 6);
    glPopMatrix();

    //legs
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(80.0, 0.0, 1.0, 0.0);
    for(int i=0; i<3; i++){
        glRotatef(-40.0, 0.0, 1.0, 0.0);
        leg(i*120.0, 1.0);
    }
    glPopMatrix();

    glRotatef(180.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(-80.0, 0.0, 1.0, 0.0);
    for(int i=0; i<3; i++){
        glRotatef(40.0, 0.0, 1.0, 0.0);
        leg((GLdouble)((((i+1)*120)%360)+60), -1.0);
    }

    glPopMatrix();
  glPopMatrix();
}

void display(void)
{
    //glClearDepth(0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   glLoadIdentity();             /* clear the matrix */
   glRotatef(camera_rotation_angle, 0.0, 1.0, 0.0);
   glRotatef(15, 1.0, 0.0, 0.0);
   glTranslatef(0.0, 3.0, 2.0);
    
   //grid :)
   glPushMatrix();
     glColor3f(0.2, 0.2, 0.2);
     glPushMatrix();
       glTranslatef(-50.0, 0.0, 0.0);
       for(int i=0; i<50; i++){
         glTranslatef(2.0, 0.0, 0.0);
         glBegin(GL_LINES);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(0.0, 0.0, 50.0);
         glEnd();
         glBegin(GL_LINES);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(0.0, 0.0, -50.0);
         glEnd();
       }
     glPopMatrix();
     glPushMatrix();
       glTranslatef(0.0, 0.0, -50.0);
       for(int i=0; i<50; i++){
         glTranslatef(0.0, 0.0, 2.0);
         glBegin(GL_LINES);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(50.0, 0.0, 0.0);
         glEnd();
         glBegin(GL_LINES);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(-50.0, 0.0, 0.0);
         glEnd();
       }
     glPopMatrix();
     //axes
     glBegin(GL_LINES);
       glColor3f(1.0, 1.0, 1.0);
       glVertex3f(0.0, 0.0, 0.0);
       glColor3f(1.0, 0.0, 0.0);
       glVertex3f(3.0, 0.0, 0.0);
     glEnd();
     glBegin(GL_LINES);
       glColor3f(1.0, 1.0, 1.0);
       glVertex3f(0.0, 0.0, 0.0);
       glColor3f(0.0, 1.0, 0.0);
       glVertex3f(0.0, 3.0, 0.0);
     glEnd();
     glBegin(GL_LINES);
       glColor3f(1.0, 1.0, 1.0);
       glVertex3f(0.0, 0.0, 0.0);
       glColor3f(0.0, 0.0, 1.0);
       glVertex3f(0.0, 0.0, 3.0);
     glEnd();

    glPopMatrix();

    glPushMatrix();
      glTranslatef(0.0, 5.0, 0.0);
      //conveyor belt
      glPushMatrix();
        glScalef(1.3, 0.01, 0.9);
        glTranslatef(0.0, 0.0, -(25*5)+floor_position);
        glColor3f(0.8, 0.8, 0.0);
        for(int i=0; i<50; i++){
          glutWireCube(5.0);
          glTranslatef(0.0, 0.0, 5.0);
        }
      //spider on conveyor belt
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0.0, 0.9, 0.0);
        tarantula();
      glPopMatrix();
      //flies :)
      for(int i=0; i<7; i++){
        glPushMatrix();
          glTranslatef(0.0, 1.5, 4.0);
          glRotatef(ant_angle*(i+1)*0.5,
                    (GLdouble)((i+1)%2),
                    (GLdouble)((i+4)%2),
                    (GLdouble)((i+8)%2));
          glTranslatef(0.0, 0.2+(GLdouble)i/8.0, 0.0);
          glColor3f(0.4, 1.0, (GLdouble)i/7.0);
          glutWireCube(0.05);
        glPopMatrix();
      }
    glPopMatrix();
    
  //1st spider running around
  glPushMatrix();
    glRotatef(spider3_angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 5.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    tarantula();
  glPopMatrix();

  //2nd spider running around
  glPushMatrix();
    glTranslatef(25.0, 0.0, 15.0);
    glRotatef(-spider3_angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 6.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    tarantula();
  glPopMatrix();

  //3rd spider running around
  glPushMatrix();
    glTranslatef(-25.0, 0.0, 5.0);
    glRotatef(-spider3_angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 4.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    tarantula();
  glPopMatrix();

  //1st spider running from "far away"
  glPushMatrix();
    glTranslatef(-75.0+spider2_movement, 0.0, -12.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    tarantula();
  glPopMatrix();

  //2nd spider running from "far away"
  glPushMatrix();
    glTranslatef(-12, 0.0, 75.0-spider2_movement);
    glRotatef(180, 0.0, 1.0, 0.0);
    tarantula();
  glPopMatrix();

  //squiggle :)
  glPushMatrix();
    glTranslatef(10.0, 2.1, -70.0);
    for(int i=0; i<288; i++){
        if(i%12==(int)(floor(camera_rotation_angle*0.7))%12) glColor3f(1.0, 1.0, 0.0);
        else glColor3f(0.0, 0.4, 0.4);
        glTranslatef(0.0, 0.0, 0.5);
        glRotatef(10.0, 0.0, 0.0, 1.0);
        glTranslatef(0.0, 0.3, 0.0);
        glutWireCube(0.5);
    }
  glPopMatrix();

    glutSwapBuffers();
}

void animation(void)
{
    camera_rotation_angle+=0.9; //0.5
    if(camera_rotation_angle>360.0)
        camera_rotation_angle-=360.0;

    floor_position-=0.21; //0.06
    if(floor_position<0.0)
            floor_position+=5.0;
    
    spider2_movement+=0.21*0.9;
    if(spider2_movement>150.0)
            spider2_movement-=150.0;

    spider_leg_angle+=12; //4
    if(spider_leg_angle>360.0)
        spider_leg_angle-=360.0;
    
    ant_angle+=5; //5
    if(ant_angle>7*360.0)
        ant_angle-=8*360.0;

    spider3_angle+=1.5; //4
    if(spider3_angle>360.0)
        spider3_angle-=360.0;


    glutPostRedisplay();
    return;
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, (GLdouble)w/(GLdouble)h, 1.5, 100);
   gluLookAt(10.0, 11.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glRotatef(90, 0.0, 1.0, 0.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'q':
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   //glEnable(GL_DEPTH_TEST);
   //glDepthFunc(GL_LESS);
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(animation);
   glutFullScreen();
   glutMainLoop();
   return 0;
}
