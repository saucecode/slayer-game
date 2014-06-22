typedef struct Box {
	float x, y;
	GLuint display_list_id;
	unsigned char w, h;
} Box;

void create_box(Box* box, float x, float y, unsigned char w, unsigned char h){
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;
	
	box->display_list_id = glGenLists(1);
	glNewList(box->display_list_id, GL_COMPILE);
		
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
		
	glEndList();
}

void draw_box(Box* box){
	/* IMMEDIATE-DRAW MODE - removed in favor of display list calls
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 0);
	glVertex2f(box->x, box->y);
	
	glTexCoord2f(1, 0);
	glVertex2f(box->x + box->w, box->y);
	
	glTexCoord2f(1, 1);
	glVertex2f(box->x + box->w, box->y + box->h);
	
	glTexCoord2f(0, 1);
	glVertex2f(box->x, box->y + box->h);
	
	glEnd();*/
	
	glCallList(box->display_list_id);
}
