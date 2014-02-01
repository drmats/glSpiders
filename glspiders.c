/**
 *  glspiders v. 0.0.1
 *
 *  Copyright (c) 2014, drmats
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 *  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _ISOC99_SOURCE

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


/**
 *  Global variables.
 */
GLfloat camera_rotation_angle = 0.0;
GLfloat floor_position = -5.0;
GLdouble spider_leg_angle = 0.0;
GLdouble fly_angle = 0.0;
GLdouble spider2_movement = 0.0;
GLdouble spider3_angle = 0.0;


/**
 *  Grid drawing routine.
 */
void draw_grid (void) {
    int i;

    glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
        glTranslatef(-50.0, 0.0, 0.0);
        for (i = 0;  i < 50;  i++) {
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
        for (i = 0;  i < 50;  i++) {
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
}


/**
 *  Color axes drawing routine.
 */
void draw_axes (void) {
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
}


/**
 *  Conveyor belt drawing routine.
 */
void draw_conveyor_belt (void) {
    int i;

    glPushMatrix();
        glScalef(1.3, 0.01, 0.9);
        glTranslatef(0.0, 0.0, -(25*5) + floor_position);
        glColor3f(0.8, 0.8, 0.0);
        for (i = 0;  i < 50;  i++) {
            glutWireCube(5.0);
            glTranslatef(0.0, 0.0, 5.0);
        }
    glPopMatrix();
}


/**
 *  Spider's leg drawing routine.
 */
void draw_leg (GLdouble o, GLdouble s) {
    int a = 0;

    glPushMatrix();
        glRotatef(-27, 1.0, 0.0, 0.0);
        glRotatef((s * spider_leg_angle) + o, 0.0, 0.0, 1.0);

        glRotatef(-15.0, 1.0, 0.0, 0.0);
        glRotatef(-((s * spider_leg_angle) + o), 0.0, 0.0, 1.0);
        glColor3f(1.0, 0.2, 0.2);
        glutWireCone(0.04, 1.2, 6, 6);

        glTranslatef(0.0, 0.0, 1.2);
        if (spider_leg_angle >= 0  &&  spider_leg_angle < 180.0 ) {
            a = -(spider_leg_angle / 4);
        } else {
          a = -((360 - spider_leg_angle) / 4);
        }
        glRotatef(70 + a, 1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 1.0);
        glutWireCone(0.02, 1.0, 6, 6);

        glTranslatef(0.0, 0.0, 1.0);
        glRotatef(50 + a/2, 1.0, 0.0, 0.0);
        glColor3f(0.5, 0.5, 1.0);
        glutWireCone(0.01, 0.7, 6, 6);
    glPopMatrix();
}


/**
 *  Spider drawing routine.
 */
void draw_spider (void) {
    int i;

    glPushMatrix();

        /* belly */
        glPushMatrix();
            glScalef(1.0, 0.7, 1.3);
            glColor3f(1.0, 0.2, 0.2);
            glutWireSphere(0.2, 12, 12);
        glPopMatrix();

        /* head */
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.2 * 1.3 + 0.06);
            glColor3f(0.5, 0.5, 1.0);
            glutWireSphere(0.06, 6, 6);
        glPopMatrix();

        glRotatef(90.0, 0.0, 1.0, 0.0);

        /* legs */
        glPushMatrix();
            glRotatef(80.0, 0.0, 1.0, 0.0);
            for (i = 0;  i < 3;  i++) {
                glRotatef(-40.0, 0.0, 1.0, 0.0);
                draw_leg(i * 120.0, 1.0);
            }
        glPopMatrix();

        glRotatef(180.0, 0.0, 1.0, 0.0);

        glPushMatrix();
            glRotatef(-80.0, 0.0, 1.0, 0.0);
            for (i = 0;  i < 3;  i++) {
                glRotatef(40.0, 0.0, 1.0, 0.0);
                draw_leg((((i+1) * 120) % 360) + 60, -1.0);
            }
        glPopMatrix();
    glPopMatrix();
}


/**
 *  "Flies" drawing routine.
 */
void draw_flies (void) {
    int i;

    for (i = 0;  i < 7;  i++) {
        glPushMatrix();
            glTranslatef(0.0, 1.5, 4.0);
            glRotatef(
                fly_angle * (i+1) * 0.5,
                (i+1) % 2,
                (i+4) % 2,
                (i+8) % 2
            );
            glTranslatef(0.0, 0.2 + (i / 8.0), 0.0);
            glColor3f(0.4, 1.0, i / 7.0);
            glutWireCube(0.05);
        glPopMatrix();
    }
}


/**
 * "Squiggle" drawing routine.
 */
void draw_squiggle (void) {
    int i;

    glPushMatrix();
        glTranslatef(10.0, 2.1, -70.0);
        for (i = 0;  i < 288;  i++) {
            if (i % 12 == (int)(floor(camera_rotation_angle * 0.7)) % 12) {
                glColor3f(1.0, 1.0, 0.0);
            } else {
                glColor3f(0.0, 0.4, 0.4);
            }
            glTranslatef(0.0, 0.0, 0.5);
            glRotatef(10.0, 0.0, 0.0, 1.0);
            glTranslatef(0.0, 0.3, 0.0);
            glutWireCube(0.5);
        }
    glPopMatrix();
}


/**
 *  Frame drawing function.
 */
void display (void) {
    int i;
    GLdouble
        p1[3][6] = {
            { 0.0, 0.0, 0.0, spider3_angle, 5.0, 90.0 },
            { 25.0, 0.0, 15.0, -spider3_angle, 6.0, -90.0 },
            { -25.0, 0.0, 5.0, -spider3_angle, 4.0, -90.0 }
        },
        p2[2][3] = {
            { -75.0 + spider2_movement, -12.0, 90.0 },
            { -12.0, 75.0 - spider2_movement, 180.0 }
        };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(camera_rotation_angle, 0.0, 1.0, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 3.0, 2.0);

    draw_grid();
    draw_axes();

    glPushMatrix();
        glTranslatef(0.0, 5.0, 0.0);

        draw_conveyor_belt();

        /* spider on conveyor belt */
        glPushMatrix();
            glTranslatef(0.0, 0.9, 0.0);
            draw_spider();
        glPopMatrix();

        draw_flies();
    glPopMatrix();

    /* 3 spiders running around */
    for (i = 0;  i < 3;  i++) {
        glPushMatrix();
            glTranslatef(p1[i][0], p1[i][1], p1[i][2]);
            glRotatef(p1[i][3], 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, p1[i][4]);
            glRotatef(p1[i][5], 0.0, 1.0, 0.0);
            draw_spider();
        glPopMatrix();
    }

    /* 2 spiders from "far away" */
    for (i = 0;  i < 2;  i++) {
        glPushMatrix();
            glTranslatef(p2[i][0], 0.0, p2[i][1]);
            glRotatef(p2[i][2], 0.0, 1.0, 0.0);
            draw_spider();
        glPopMatrix();
    }

    draw_squiggle();

    glutSwapBuffers();
}


/**
 *  Periodically called for variables update.
 */
void animation (void) {
    camera_rotation_angle += 0.9;
    if (camera_rotation_angle > 360.0) {
        camera_rotation_angle -= 360.0;
    }

    floor_position -= 0.21;
    if (floor_position < 0.0) {
        floor_position += 5.0;
    }

    spider2_movement += 0.21 * 0.9;
    if (spider2_movement > 150.0) {
        spider2_movement -= 150.0;
    }

    spider_leg_angle += 12;
    if (spider_leg_angle > 360.0) {
        spider_leg_angle -= 360.0;
    }

    fly_angle += 5;
    if (fly_angle > 7 * 360.0) {
        fly_angle -= 8 * 360.0;
    }

    spider3_angle += 1.5;
    if (spider3_angle > 360.0) {
        spider3_angle-=360.0;
    }

    glutPostRedisplay();
}


/**
 *  Viewport resize handler.
 */
void reshape (int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.5, 100);
    gluLookAt(10.0, 11.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}


/**
 *  Keyboard handler.
 */
void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
    }
}


/**
 *  Program entry point.
 */
int main (int argc, char** argv) {
    /* glut initialization */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* handlers assignment */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(animation);

    /* go full screen and enter main loop */
    glutFullScreen();
    glutMainLoop();

    exit(0);
}
