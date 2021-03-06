#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#define PI 3.14159

const int WIDTH = 800, HEIGHT = 600;
const int WORLD_WIDTH = 2048, WORLD_HEIGHT = 2048;

typedef struct GameState {
	int mouse_x, mouse_y;
	bool keys[256];
	bool LMB_DOWN, RMB_DOWN;
	float x, y;
	unsigned int textures[32];
	unsigned int weapon_textures[16];
	time_t current_time;
	
} GameState;

GameState* gamestate = (GameState*) malloc(sizeof(GameState));

float random_float(){
	return ((float)(rand() % 100000)) / 100000.0;
}

#include "texture_loader.cpp"
/*
	void loadTexture(string filename, unsigned int* texture_id);
*/
#include "game.cpp"
/*
	void game_init(GameState* gamestate);
	void game_update(GameState* gamestate);
	void game_render(GameState* gamestate);
	void game_destroy(GameState* gamestate);
*/

void init(){
	gamestate->mouse_x = 0;
	gamestate->mouse_y = 0;
	gamestate->x = 10;
	gamestate->y = 10;
	
	game_init(gamestate);
	
	srand(time(NULL));
}

void initGL(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void clearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void update(){
	time(&gamestate->current_time);
	game_update(gamestate);
}

void render(){
	update();
	clearScreen();
	
	game_render(gamestate);
	
	//usleep(16667);
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y){
	gamestate->keys[key] = true;
}

void keyReleased(unsigned char key, int x, int y){
	gamestate->keys[key] = false;
}

void mouseEvent(int button, int state, int x, int y){
	gamestate->LMB_DOWN = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
	gamestate->RMB_DOWN = button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN;
	gamestate->mouse_x = x;
	gamestate->mouse_y = HEIGHT - y;
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
	glutMouseFunc(&mouseEvent);
	glutMotionFunc(&mouseMotion);
	glutPassiveMotionFunc(&mouseMotion);
	
	glutMainLoop();
	
	glutDestroyWindow(window);
	game_destroy(gamestate);
	free(gamestate);
	
	return 0;
}
