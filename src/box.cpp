typedef struct Box {
	float x, y;
	unsigned char w, h;
} Box;

void create_box(Box* box, float x, float y, unsigned char w, unsigned char h){
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;
}

void draw_box(Box* box){
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 0);
	glVertex2f(box->x, box->y);
	
	glTexCoord2f(1, 0);
	glVertex2f(box->x + box->w, box->y);
	
	glTexCoord2f(1, 1);
	glVertex2f(box->x + box->w, box->y + box->h);
	
	glTexCoord2f(0, 1);
	glVertex2f(box->x, box->y + box->h);
	
	glEnd();
}
