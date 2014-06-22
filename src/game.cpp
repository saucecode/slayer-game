
#include "box.cpp"
#include "weapon.cpp"

typedef struct Player {
	float x, y, move_x, move_y, prev_x, prev_y;
	float angle;
	unsigned int score;
	unsigned char health;
	unsigned short weapon_id;
	short can_shoot;
	short magazine;
} Player;

GLuint* background_display_list = (GLuint*) malloc(sizeof(GLuint));
Box* boxes = (Box*) malloc(sizeof(Box) * 64);
Weapon weapons[16];
std::vector<Bullet> bullets;
Player player;

bool player_intersects_box(Box box){
	char ph = 24;
	char pw = 24;
	return (player.x-12 < box.x + box.w && player.x-12 + pw > box.x && player.y-12 < box.y + box.h && ph + player.y-12 > box.y);
}

void draw_string(float x, float y, std::string text){
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*) (text.c_str()));
}

void generate_background(){
	*background_display_list = glGenLists(1);
	glNewList(*background_display_list, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, gamestate->textures[1]);
	glBegin(GL_QUADS);
	for(int x = 0; x < 2048; x += 128){
		for(int y = 0; y < 2048; y += 128){
			glTexCoord2f(0,0);
			glVertex2f(x,y);
			glTexCoord2f(1,0);
			glVertex2f(x+128,y);
			glTexCoord2f(1,1);
			glVertex2f(x+128,y+128);
			glTexCoord2f(0,1);
			glVertex2f(x,y+128);
		}
	}
	glEnd();
	glEndList();
}

void translate_player(){
	glTranslatef(-player.x+WIDTH/2, -player.y+HEIGHT/2, 0);
}

void update_player(GameState* gamestate){
	//Player angle to mouse
	player.angle = atan2(gamestate->mouse_x - WIDTH/2, -gamestate->mouse_y + HEIGHT/2) * 180 / PI;
	
	//Player input
	if(gamestate->keys['w']) player.y += 4;
	if(gamestate->keys['s']) player.y -= 4;
	if(gamestate->keys['a']) player.x -= 4;
	if(gamestate->keys['d']) player.x += 4;
	
	//Player shooting
	if(gamestate->LMB_DOWN && player.can_shoot <= 0){
		if(player.magazine < weapons[player.weapon_id].bullet_count){ //reload
			player.magazine = weapons[player.weapon_id].magazine_length;
			player.can_shoot = weapons[player.weapon_id].reload_interval;
		}else{
			player.can_shoot = weapons[player.weapon_id].shoot_interval;
			player.magazine -= weapons[player.weapon_id].bullet_count;
		
			for(int i=0;i<weapons[player.weapon_id].bullet_count;i++){
				Bullet b;
				create_bullet(&b, player.x, player.y, (player.angle-weapons[player.weapon_id].accuracy + weapons[player.weapon_id].accuracy*2*random_float()));
				bullets.push_back(b);
			}
		
			printf("Shots fired! %li\n", gamestate->current_time);
		}
	}
	
	//Player collisions with boxes
	for(int i=0;i<64;i++){
		if(boxes[i].w == 0) continue;
		if( player_intersects_box(boxes[i])){
			player.y = player.prev_y;
			player.x = player.prev_x;
		}
	}
	
	
	//Update can_shoot
	if(player.can_shoot > 0) player.can_shoot--;
	
	//Last player position updated
	player.prev_x = player.x;
	player.prev_y = player.y;
}

void update_bullets(GameState* gamestate){
	for(int i=0;i<bullets.size();i++){
		Bullet* b = &bullets.at(i);
		if(b->destroyed){
			bullets.erase(bullets.begin()+i);
			i--;
			continue;
		}
		b->x += b->dx;
		b->y += b->dy;
	}
}

void draw_player(){
	glLoadIdentity();
	glTranslatef(WIDTH/2, HEIGHT/2, 0);
	
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, gamestate->textures[0]);
	
	glRotatef(player.angle, 0,0,1);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-12, -12);
	glTexCoord2f(1,0);
	glVertex2f(12,-12);
	glTexCoord2f(1,1);
	glVertex2f(12,12);
	glTexCoord2f(0,1);
	glVertex2f(-12,12);
	glEnd();
}

void draw_bullets(){
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	for(int i=0;i<bullets.size();i++){
		Bullet* b = &bullets.at(i);
		if(b->destroyed) continue;
		glVertex2f(b->x, b->y);
		glVertex2f(b->x - b->dx, b->y - b->dy);
	}
	glEnd();
}

void draw_HUD(){
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, 0);
	draw_string(player.x-200,player.y+240, "Health: " + std::to_string(player.health)+"\nWeapon: " + weapons[player.weapon_id].name + "\nMagazine: " + std::to_string(player.magazine) + "/" + std::to_string(weapons[player.weapon_id].magazine_length));
}

void game_init(GameState* gamestate){
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	
	player.health = 100;
	player.weapon_id = 0;
	player.magazine = weapons[player.weapon_id].magazine_length;
	
	load_texture("res/player.png", &(gamestate->textures[0]));
	load_texture("res/grass_repeat.png", &(gamestate->textures[1]));
	
	create_box(&boxes[0], 100, 30, 32, 32);
	create_weapon(&weapons[0], "SubMachineGun", 0, 1, 7, 80, 30, 10, 4);
	
	generate_background();
}

void game_update(GameState* gamestate){
	update_player(gamestate);
	update_bullets(gamestate);
}

void game_render(GameState* gamestate){
	translate_player();
	glCallList(*background_display_list);
	
	draw_HUD();
	
	//Draw boxes
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 0, 0);
	for(int i=0;i<64;i++){
		if(boxes[i].w == 0) continue;
		draw_box(&boxes[i]);
	}
	
	draw_bullets();

	//Draw player - MUST be last
	draw_player();
}

void game_destroy(GameState* gamestate){
	free(boxes);
	free(background_display_list);
}
