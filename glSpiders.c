/**
 *  glSpiders v. 0.0.1
 *
 *  A very simple OpenGL animation app.
 *
 *  Wireframe spiders on a flat grid with rotating camera around.
 *  No lights. No textures. No shadows. No depth buffer.
 *
 *  Original code written in 2005.
 *
 *  Copyright (c) 2014, drmats
 *  All rights reserved.
 *
 *  https://github.com/drmats/glSpiders
 */

/**
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
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


/**
 *  Global variables.
 */
bool fullScreen = false;
struct screen_t {
    int width;
    int height;
} screen;

GLfloat
    cameraRotationAngle = 0.0,
    conveyorBeltPosition = -5.0,
    spiderLegAngle = 0.0,
    fliesAngle = 0.0,
    spider2Movement = 0.0,
    spider3Angle = 0.0;


/**
 *  Grid drawing routine.
 */
inline void drawGrid (void) {
    GLfloat p[2][8] = {
        { -50.0, 0.0, 2.0, 0.0, 0.0, 50.0, 0.0, -50.0 },
        { 0.0, -50.0, 0.0, 2.0, 50.0, 0.0, -50.0, -0.0 }
    };

    glColor3f(0.2, 0.2, 0.2);
    for (int i = 0;  i < 2;  i++) {
        glPushMatrix();
            glTranslatef(p[i][0], 0.0, p[i][1]);
            for (int j = 0;  j < 50;  j++) {
                glTranslatef(p[i][2], 0.0, p[i][3]);
                glBegin(GL_LINES);
                    glVertex3f(0.0, 0.0, 0.0);
                    glVertex3f(p[i][4], 0.0, p[i][5]);
                glEnd();
                glBegin(GL_LINES);
                    glVertex3f(0.0, 0.0, 0.0);
                    glVertex3f(p[i][6], 0.0, p[i][7]);
                glEnd();
            }
        glPopMatrix();
    }
}


/**
 *  Color axes drawing routine.
 */
inline void drawAxes (void) {
    GLfloat p[3][6] = {
        { 1.0, 0.0, 0.0,    3.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0,    0.0, 3.0, 0.0 },
        { 0.0, 0.0, 1.0,    0.0, 0.0, 3.0 }
    };

    for (int i = 0;  i < 3;  i++) {
        glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(0.0, 0.0, 0.0);
            glColor3f(p[i][0], p[i][1], p[i][2]);
            glVertex3f(p[i][3], p[i][4], p[i][5]);
        glEnd();    
    }
}


/**
 *  Conveyor belt drawing routine.
 */
inline void drawConveyorBelt (void) {
    glPushMatrix();
        glScalef(1.3, 0.01, 0.9);
        glTranslatef(0.0, 0.0, -(25*5) + conveyorBeltPosition);
        glColor3f(0.8, 0.8, 0.0);
        for (int i = 0;  i < 50;  i++) {
            glutWireCube(5.0);
            glTranslatef(0.0, 0.0, 5.0);
        }
    glPopMatrix();
}


/**
 *  Spider's leg drawing routine.
 */
void drawLeg (GLfloat o, GLfloat s) {
    GLfloat a;

    glPushMatrix();
        glRotatef(-27.0, 1.0, 0.0, 0.0);
        glRotatef((s * spiderLegAngle) + o, 0.0, 0.0, 1.0);

        glRotatef(-15.0, 1.0, 0.0, 0.0);
        glRotatef(-((s * spiderLegAngle) + o), 0.0, 0.0, 1.0);
        glColor3f(1.0, 0.2, 0.2);
        glutWireCone(0.04, 1.2, 6, 6);

        glTranslatef(0.0, 0.0, 1.2);
        if (spiderLegAngle >= 0.0  &&  spiderLegAngle < 180.0 ) {
            a = -(spiderLegAngle / 4.0);
        } else {
          a = -((360.0 - spiderLegAngle) / 4.0);
        }
        glRotatef(70.0 + a, 1.0, 0.0, 0.0);
        glColor3f(0.2, 0.2, 1.0);
        glutWireCone(0.02, 1.0, 6, 6);

        glTranslatef(0.0, 0.0, 1.0);
        glRotatef(50 + a/2.0, 1.0, 0.0, 0.0);
        glColor3f(0.5, 0.5, 1.0);
        glutWireCone(0.01, 0.7, 6, 6);
    glPopMatrix();
}


/**
 *  Spider drawing routine.
 */
void drawSpider (void) {
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
            for (int i = 0;  i < 3;  i++) {
                glRotatef(-40.0, 0.0, 1.0, 0.0);
                drawLeg(i * 120.0, 1.0);
            }
        glPopMatrix();

        glRotatef(180.0, 0.0, 1.0, 0.0);

        glPushMatrix();
            glRotatef(-80.0, 0.0, 1.0, 0.0);
            for (int i = 0;  i < 3;  i++) {
                glRotatef(40.0, 0.0, 1.0, 0.0);
                drawLeg((((i+1) * 120) % 360) + 60, -1.0);
            }
        glPopMatrix();
    glPopMatrix();
}


/**
 *  "Flies" drawing routine.
 */
inline void drawFlies (void) {
    for (int i = 0;  i < 7;  i++) {
        glPushMatrix();
            glTranslatef(0.0, 1.5, 4.0);
            glRotatef(
                fliesAngle * (i+1) * 0.5,
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
inline void drawSquiggle (void) {
    glPushMatrix();
        glTranslatef(10.0, 2.1, -70.0);
        for (int i = 0;  i < 288;  i++) {
            if (i % 12 == (int)(floor(cameraRotationAngle * 0.7)) % 12) {
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(cameraRotationAngle, 0.0, 1.0, 0.0);
    glRotatef(15, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 3.0, 2.0);

    drawGrid();
    drawAxes();

    glPushMatrix();
        glTranslatef(0.0, 5.0, 0.0);

        drawConveyorBelt();

        /* spider on conveyor belt */
        glPushMatrix();
            glTranslatef(0.0, 0.9, 0.0);
            drawSpider();
        glPopMatrix();

        drawFlies();
    glPopMatrix();

    /* 3 spiders running around */
    GLfloat p1[3][6] = {
        { 0.0, 0.0, 0.0, spider3Angle, 5.0, 90.0 },
        { 25.0, 0.0, 15.0, -spider3Angle, 6.0, -90.0 },
        { -25.0, 0.0, 5.0, -spider3Angle, 4.0, -90.0 }
    };
    for (int i = 0;  i < 3;  i++) {
        glPushMatrix();
            glTranslatef(p1[i][0], p1[i][1], p1[i][2]);
            glRotatef(p1[i][3], 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, p1[i][4]);
            glRotatef(p1[i][5], 0.0, 1.0, 0.0);
            drawSpider();
        glPopMatrix();
    }

    /* 2 spiders from "far away" */
    GLfloat p2[2][3] = {
        { -75.0 + spider2Movement, -12.0, 90.0 },
        { -12.0, 75.0 - spider2Movement, 180.0 }
    };
    for (int i = 0;  i < 2;  i++) {
        glPushMatrix();
            glTranslatef(p2[i][0], 0.0, p2[i][1]);
            glRotatef(p2[i][2], 0.0, 1.0, 0.0);
            drawSpider();
        glPopMatrix();
    }

    drawSquiggle();

    glutSwapBuffers();
}


/**
 *  Periodically called for variables update.
 */
void animation (void) {
    cameraRotationAngle += 0.9;
    if (cameraRotationAngle > 360.0) {
        cameraRotationAngle -= 360.0;
    }

    conveyorBeltPosition -= 0.21;
    if (conveyorBeltPosition < 0.0) {
        conveyorBeltPosition += 5.0;
    }

    spider2Movement += 0.21 * 0.9;
    if (spider2Movement > 150.0) {
        spider2Movement -= 150.0;
    }

    spiderLegAngle += 12.0;
    if (spiderLegAngle > 360.0) {
        spiderLegAngle -= 360.0;
    }

    fliesAngle += 5.0;
    if (fliesAngle > 7.0 * 360.0) {
        fliesAngle -= 8.0 * 360.0;
    }

    spider3Angle += 1.5;
    if (spider3Angle > 360.0) {
        spider3Angle -= 360.0;
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
    gluLookAt(
        10.0, 11.0, 12.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}


/**
 *  Keyboard handler.
 */
void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            if (fullScreen) {
                glutReshapeWindow(screen.width/2, screen.height/2);
                glutPositionWindow(screen.width/4, screen.height/4);
                fullScreen = false;
            } else {
                glutFullScreen();
                fullScreen = true;
            }
            break;
        case 'q':
            exit(0);
            break;
    }
}


/**
 *  Program entry point.
 */
int main (int argc, char** argv) {
    char* appName = "glSpiders v. 0.0.1";

    fprintf(stderr, "%s\n", appName);

    /* glut initialization */
    glutInit(&argc, argv);
    screen.width = glutGet(GLUT_SCREEN_WIDTH);
    screen.height = glutGet(GLUT_SCREEN_HEIGHT);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screen.width/2, screen.height/2);
    glutInitWindowPosition(screen.width/4, screen.height/4);
    glutCreateWindow(appName);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* handlers assignment */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(animation);

    fprintf(stderr,
        "  [q] - quit\n"
        "  [f] - full screen toggle\n"
    );

    /* enter main loop */
    glutMainLoop();

    exit(0);
}
