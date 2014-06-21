
#include "box.cpp"

typedef struct Player {
	float x, y, move_x, move_y;
} Player;

Player player;
Box* boxes = (Box*) malloc(sizeof(Box) * 64);

void draw_string(float x, float y, std::string text){
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*) (text.c_str()));
}

void translate_player(){
	glTranslatef(-player.x, -player.y, 0);
}

void game_init(GameState* gamestate){
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	
	load_texture("res/player.png", &(gamestate->textures[0]));
	create_box(&boxes[0], 100, 30, 32, 32);
}

void game_update(GameState* gamestate){
	if(gamestate->keys['w']) player.y += 4;
	if(gamestate->keys['s']) player.y -= 4;
	if(gamestate->keys['a']) player.x -= 4;
	if(gamestate->keys['d']) player.x += 4;
	
}

void game_render(GameState* gamestate){
	translate_player();
	//Draw boxes
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 0, 0);
	draw_box(&boxes[0]);
	
	//Draw text
	/*unsigned char* s = (unsigned char*) "there is no spoon.";
	glRasterPos2f(player.x + WIDTH/2, player.y + HEIGHT/2 - 50);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, s);
	*/
	draw_string(90,62, "hello world!");

	//Draw player
	glLoadIdentity();
	glTranslatef(WIDTH/2, HEIGHT/2, 0);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, gamestate->textures[0]);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-16, -16);
	glTexCoord2f(1,0);
	glVertex2f(16,-16);
	glTexCoord2f(1,1);
	glVertex2f(16,16);
	glTexCoord2f(0,1);
	glVertex2f(-16,16);
	glEnd();
}

void game_destroy(GameState* gamestate){
	free(boxes);
}
