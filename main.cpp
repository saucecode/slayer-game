#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const int WIDTH = 800, HEIGHT = 600;

typedef struct GameState {
	int mouse_x, mouse_y;
	bool keys[256];
	float x, y;
} GameState;

GameState* gamestate = (GameState*) malloc(sizeof(GameState));

void init(){
	gamestate->mouse_x = 0;
	gamestate->mouse_y = 0;
	gamestate->x = 10;
	gamestate->y = 10;
}

void initGL(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,0);
}

void clearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void update(){
	if(gamestate->keys['w']) gamestate->y += 4;
	if(gamestate->keys['s']) gamestate->y -= 4;
	if(gamestate->keys['a']) gamestate->x -= 4;
	if(gamestate->keys['d']) gamestate->x += 4;
}

void render(){
	update();
	clearScreen();
	
	glBegin(GL_QUADS);
	glVertex2f(gamestate->x,gamestate->y);
	glVertex2f(gamestate->x+10,gamestate->y);
	glVertex2f(gamestate->x+10,gamestate->y+10);
	glVertex2f(gamestate->x,gamestate->y+10);
	
	glVertex2f(gamestate->mouse_x,gamestate->mouse_y);
	glVertex2f(gamestate->mouse_x+10,gamestate->mouse_y);
	glVertex2f(gamestate->mouse_x+10,gamestate->mouse_y+10);
	glVertex2f(gamestate->mouse_x,gamestate->mouse_y+10);
	glEnd();
	
	
	//usleep(16667);
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y){
	gamestate->keys[key] = true;
}

void keyReleased(unsigned char key, int x, int y){
	gamestate->keys[key] = false;
}

void mouseMotion(int x, int y){
	gamestate->mouse_x = x;
	gamestate->mouse_y = HEIGHT - y;
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WIDTH,HEIGHT);
	int window = glutCreateWindow("slayer");
	
	init();
	initGL();
	
	glutDisplayFunc(&render);
	glutIdleFunc(&render);
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyReleased);
	glutPassiveMotionFunc(&mouseMotion);
	glutMainLoop();
	
	glutDestroyWindow(window);
	free(gamestate);
	
	return 0;
}
