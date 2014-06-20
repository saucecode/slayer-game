
typedef struct Player {
	float x, y;
} Player;

Player player;

void load_texture(std::string filename, unsigned int* texture_id){
	unsigned int tex_id;
	ilGenImages(1, &tex_id);
	ilBindImage(tex_id);
	ilLoadImage(filename.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	glGenTextures(1, texture_id);
	glBindTexture(GL_TEXTURE_2D, *texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,ilGetData());
	ilDeleteImages(1, &tex_id);
}

void game_init(GameState* gamestate){
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	
	load_texture("res/player.png", &(gamestate->textures[0]));
}

void game_update(GameState* gamestate){
	if(gamestate->keys['w']) gamestate->y += 4;
	if(gamestate->keys['s']) gamestate->y -= 4;
	if(gamestate->keys['a']) gamestate->x -= 4;
	if(gamestate->keys['d']) gamestate->x += 4;
}

void game_render(GameState* gamestate){

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, gamestate->textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(gamestate->x,gamestate->y);
	glTexCoord2f(1,0);
	glVertex2f(gamestate->x+32,gamestate->y);
	glTexCoord2f(1,1);
	glVertex2f(gamestate->x+32,gamestate->y+32);
	glTexCoord2f(0,1);
	glVertex2f(gamestate->x,gamestate->y+32);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex2f(gamestate->mouse_x,gamestate->mouse_y);
	glVertex2f(gamestate->mouse_x+10,gamestate->mouse_y);
	glVertex2f(gamestate->mouse_x+10,gamestate->mouse_y+10);
	glVertex2f(gamestate->mouse_x,gamestate->mouse_y+10);
	glEnd();
}
