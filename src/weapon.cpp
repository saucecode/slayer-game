const int BULLET_VELOCITY = 10;

typedef struct Weapon {
	unsigned short weapon_id;
	unsigned short bullet_count;
	unsigned short shoot_interval;
	unsigned short reload_interval;
	unsigned short magazine_length;
	unsigned short accuracy;
	unsigned short damage;
	std::string name;
} Weapon;

typedef struct Bullet {
	float x, y, dx, dy, angle;
	bool destroyed;
} Bullet;

// create_weapon(Weapon*, id, bullet_count, shoot_interval, reload_interval, magazine_length, accuracy, damage);
void create_weapon(Weapon* w, std::string name, unsigned short id, unsigned short bullet_count,
	unsigned short shoot_interval, unsigned short reload_interval,
	unsigned short magazine_length, unsigned short accuracy,
	unsigned short damage){

	w->weapon_id = id;
	w->bullet_count = bullet_count;
	w->shoot_interval = shoot_interval;
	w->reload_interval = reload_interval;
	w->magazine_length = magazine_length;
	w->accuracy = accuracy;
	w->damage = damage;
	w->name = name;
}

void create_bullet(Bullet* b, float x, float y, float angle){
	b->x = x;
	b->y = y;
	b->angle = angle;
	b->dx = sin(angle*PI/180) * BULLET_VELOCITY;
	b->dy = -cos(angle*PI/180) * BULLET_VELOCITY;
	b->destroyed = false;
}
