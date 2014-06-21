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
