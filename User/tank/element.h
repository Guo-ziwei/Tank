#ifndef _ELEMENT_H
#define _ELEMENT_H

#include "stm32f10x.h"

typedef struct Tank{
	u8 No;
	int blood;
	u16 x;
	u16 y;
	u8 direction;
	u8 kind;
	u8 dunpai;
	u8 speed;
}Tank;	
	
	
void draw_Tank(Tank *ptr);
void Tank_move(Tank *ptr);
void Tank_turn(Tank *myTank, u8 dir);
u8 sort(int *l);
u8 is_Wall(u16 x, u16 y);
typedef struct Bullet{
	u8 kind;
	u8 No;
	u8 disapper;
	u16 x;
	u16 y;
	u8 direction;
	u8 speed;
}Bullet;	
//void draw_Bullet(Bullet *ptr);
//void Bullet_load(Bullet *ptr, Tank *myTank);

//void draw_Wall(u16 x, u16 y, u16 L, u8 dir);
void A_star(u16 x, u16 y, u16 dx, u16 dy, Tank *myTank);

#endif
