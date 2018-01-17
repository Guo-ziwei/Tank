
#ifndef BULLET_H
#define BULLET_H


#include "element.h"
#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "fonts.h"



	
int Rectangle(int Bullet_x,int Bullet_y,int X,int Y,int L,int W);
void BulletDisappear(Bullet *myBullet);
int BulletHittingWall(Bullet * mybullet);
void draw_Bullet(Bullet *myBullet);
void Bullet_load(Bullet *myBullet,Tank *myTank);
int BulletMove(Bullet *myBullet);
void BulletHittingTank(Bullet *mybullet,Tank *OpposingTankA, Tank *OpposingTankB,Tank *OpposingTankC,Tank *OpposingTankD);
void draw_3_Bullet(Bullet *myBullet);
void clear_3_Bullet(Bullet *myBullet);

typedef struct package{
    int x;
	  int y;
    int property;
}Package;
void draw_package(Package *myPack);
void clear_package(Package *myPack);
void creat_package(Package *myPack);
void Tank_eatPackage(Package *myPack,Tank *OpposingTank);
void draw_heavy_Bullet(Bullet *myBullet);
void clear_heavy_Bullet(Bullet *myBullet);

#endif

