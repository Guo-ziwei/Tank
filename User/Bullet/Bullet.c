#include "Bullet.h"
#include "stm32f10x.h"
#include <stdlib.h> 

#define TANK_BLOCK_SIZE 	6  // 小方块尺寸
#define TANK_BLOCK_SPACE	2  // 间隔尺寸
#define BULLET_SIZE	4        // 子弹尺寸
#define BULLET_Middle_SIZE 6 // 中子弹尺寸
#define BULLET_Big_SIZE	8    // 大子弹尺寸
#define BULLET_STEP	16       // 子弹步长
#define BRICK_SIZE 4         //
#define PACKAGE_SIZE 22      // 技能包尺寸
//int Flag_Move = 0;
int pose_num=-1,property_num=-1;

//重弹
void draw_heavy_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//子弹种类
		{
		case 0://right
			   			ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+29, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+22, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
					   	ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+15, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹		       
				break;
		case 1://up
			   			ILI9341_DrawRectangle ( myBullet->x-27, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x-20, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
			   			ILI9341_DrawRectangle ( myBullet->x-13, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
				break;
		case 2://left
			   			ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-27, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-20, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
					   	ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-13, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹	
				break;		
		case 3://down
			   			ILI9341_DrawRectangle ( myBullet->x+29, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x+22, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹	
			   			ILI9341_DrawRectangle ( myBullet->x+15, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹		      
				break;		
		default : break;		
		}
}
//消除重弹药
void clear_heavy_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//子弹种类
		{
		case 0://right
			   			ILI9341_Clear ( myBullet->x+1, myBullet->y+29, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x+1, myBullet->y+22, BULLET_SIZE, BULLET_SIZE);//绘制子弹
					   	ILI9341_Clear ( myBullet->x+1, myBullet->y+15, BULLET_SIZE, BULLET_SIZE);//绘制子弹	
				break;
		case 1://up
              ILI9341_Clear ( myBullet->x-27, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹
		          ILI9341_Clear ( myBullet->x-20, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹
			   			ILI9341_Clear ( myBullet->x-13, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹
				break;
		case 2://left
			   			ILI9341_Clear ( myBullet->x+1, myBullet->y-27, BULLET_SIZE, BULLET_SIZE);//绘制子弹
		          ILI9341_Clear ( myBullet->x+1, myBullet->y-20, BULLET_SIZE, BULLET_SIZE);//绘制子弹
					   	ILI9341_Clear ( myBullet->x+1, myBullet->y-13, BULLET_SIZE, BULLET_SIZE);//绘制子弹	
				break;		
		case 3://down
			   			ILI9341_Clear ( myBullet->x+29, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹
		          ILI9341_Clear ( myBullet->x+22, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹	
			   			ILI9341_Clear ( myBullet->x+15, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//绘制子弹		      
				break;		
		default : break;		
		}
}
//三弹
void draw_3_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//子弹种类
		{
		case 0://right
			   			ILI9341_DrawRectangle ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
				break;
		case 1://up
			   			ILI9341_DrawRectangle ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹	
				break;
		case 2://left
			   			ILI9341_DrawRectangle ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹	
				break;		
		case 3://down
			   			ILI9341_DrawRectangle ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE, 1 );//绘制子弹	
				break;		
		default : break;		
		}
}

//消除三弹
void clear_3_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//子弹种类
		{
		case 0://right
			   			ILI9341_Clear ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
				break;
		case 1://up
			   			ILI9341_Clear ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE);//绘制子弹	
				break;
		case 2://left
			   			ILI9341_Clear ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//绘制子弹	
				break;		
		case 3://down
			   			ILI9341_Clear ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE );//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE);//绘制子弹
		          ILI9341_Clear ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE );//绘制子弹	
				break;		
		default : break;		
		}
}
//绘制子弹
void draw_Bullet(Bullet *myBullet)
{
	myBullet->disapper = 0;
	if(myBullet->No==1)//子弹归属
	LCD_SetColors(YELLOW ,BLACK);	
		else
		LCD_SetColors(MAGENTA, BLACK);
	switch(myBullet->kind)//子弹种类
		{
			case 0: //普通子弹
			myBullet->speed=10;
			//if(BulletHittingWall(myBullet)==0)
			ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );
			 break;
			case 1: //低速子弹
			myBullet->speed=8;
			//if(BulletHittingWall(myBullet)==0)
			ILI9341_DrawRectangle ( myBullet->x-2, myBullet->y-2, BULLET_Big_SIZE, BULLET_Big_SIZE, 1 );//绘制子弹	
		  break;
			case 2: //三弹连发
			myBullet->speed=18;
			//if(BulletHittingWall(myBullet)==0)
      draw_3_Bullet(myBullet);
			break;
			case 3: //重弹
			myBullet->speed=16;
			//if(BulletHittingWall(myBullet)==0)
      draw_heavy_Bullet(myBullet);
			break;
		}
}


//坦克装弹
void Bullet_load(Bullet *myBullet,Tank *myTank)
{   
	  myBullet->kind=myTank->kind;//根据坦克类型确定弹药类型
	  myBullet->No = myTank->No;
	 // myBullet->disapper =0;
//		if(myTank->No==1)
//		  { //myBullet->kind=0; 
//		    LCD_SetColors(YELLOW ,BLACK);
//			  myBullet->No = myTank->No;
//		  }			
//		else
//			{ //myBullet->kind=3;//试验重弹 
//		    LCD_SetColors(MAGENTA ,BLACK);
//			  myBullet->No = myTank->No;
//		  }   
	switch(myTank->direction)
	{
		case 0://right
			    myBullet->x = myTank->x+1;
					myBullet->y = myTank->y+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE + 1;
		      myBullet->direction=0;
			    //ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
				break;
		case 1://up
	      	myBullet->x = myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE-BULLET_SIZE - 1;
					myBullet->y = myTank->y+1;	
          myBullet->direction=1;		
				break;
		case 2://left
					myBullet->x = myTank->x+1;
					myBullet->y = myTank->y-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE-BULLET_SIZE - 1;
          myBullet->direction=2;		
				break;		
		case 3://down
			    myBullet->x = myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE + 1;
					myBullet->y = myTank->y+1;
		      myBullet->direction=3;
				  //ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
				break;		
		default : break;		
			}	
}
//子弹移动
int BulletMove(Bullet *myBullet)
 { 
   int speed=myBullet->speed;
	//if(myBullet->disapper == 1) return 1;
	 switch (myBullet->direction)
	 {
		 case 0://right
			      if(BulletHittingWall(myBullet)==0)
						BulletDisappear(myBullet);
						myBullet->y+=speed;
						if(BulletHittingWall(myBullet)==1) {
							myBullet->y-=speed;
							
					 }	
						else draw_Bullet(myBullet);						
					break;//draw_Bullet(myBullet);
	   case 1://up
            //ILI9341_Clear(myBullet->x,myBullet->y,BULLET_SIZE,BULLET_SIZE);
		        if(BulletHittingWall(myBullet)==0)
		        BulletDisappear(myBullet);
						myBullet->x-=speed;
						if(BulletHittingWall(myBullet)==1) {
							myBullet->x+=speed;
							
					 }	
						else draw_Bullet(myBullet);		
					 break;//      
		 case 2://left
			      if(BulletHittingWall(myBullet)==0)
            BulletDisappear(myBullet);
						myBullet->y-=speed;
						if(BulletHittingWall(myBullet)==1) {
						myBullet->y+=speed;
							
					 }	
						else draw_Bullet(myBullet);		
					 break; //draw_Bullet(myBullet);
		 case 3://down
            //ILI9341_Clear(myBullet->x,myBullet->y,BULLET_SIZE,BULLET_SIZE);
		        if(BulletHittingWall(myBullet)==0)
		        BulletDisappear(myBullet);
						myBullet->x+=speed;
						if(BulletHittingWall(myBullet)==1) {
							myBullet->x-=speed;
							
					 }	
						else draw_Bullet(myBullet);		
					 break; //draw_Bullet(myBullet)
	 }
	 return 0;
 }
//判断子弹是否在矩形里面
int Rectangle(int Bullet_x,int Bullet_y,int X,int Y,int L,int W)
{
  if((X <= Bullet_x)&&(Bullet_x < X + L)&&(Y <= Bullet_y)&&(Bullet_y < Y + W))
    return 1;//在矩形里面返回1
  else
	  return 0;//矩形外返回0
}
//子弹消失函数
void BulletDisappear(Bullet *myBullet)
{
	switch(myBullet->kind)//子弹种类
		{
			case 0:
				//if(BulletHittingWall(myBullet))
			ILI9341_Clear(myBullet->x,myBullet->y,BULLET_SIZE,BULLET_SIZE);break;//擦除
			case 1:
			ILI9341_Clear(myBullet->x-2,myBullet->y-2,BULLET_Big_SIZE,BULLET_Big_SIZE);break;
		  case 2:
      clear_3_Bullet(myBullet); break;
			case 3:
			clear_heavy_Bullet(myBullet);break;
		}
}
//判断子弹是否撞墙
int BulletHittingWall(Bullet *mybullet)//1表示不正常区域，0表示显示屏内非墙区域
{
  if(Rectangle(mybullet->x, mybullet->y, 0, 0, 111, 240) == 1)
    {
		  if(Rectangle(mybullet->x, mybullet->y, 20, 19, 29, 76) == 1 ||
				 Rectangle(mybullet->x, mybullet->y, 70, 19, 29, 76) == 1 ||
			   Rectangle(mybullet->x, mybullet->y, 43, 115, 56, 25) == 1||
			   Rectangle(mybullet->x, mybullet->y, 20, 160, 29, 55) == 1||
			   Rectangle(mybullet->x, mybullet->y, 70, 160, 29, 55) == 1  )
				{
				 // BulletDisappear(mybullet);
					mybullet->disapper = 1;
					return 1;
				}
			else
				return 0;
		}
  else if(Rectangle(mybullet->x, mybullet->y, 111, 0, 100, 240) == 1)
    {
		  if(Rectangle(mybullet->x, mybullet->y, 119, 19, 29, 45) == 1 ||
				 Rectangle(mybullet->x, mybullet->y, 168, 19, 30, 57) == 1 ||
			   Rectangle(mybullet->x, mybullet->y, 119, 96, 29, 25) == 1 ||
			   Rectangle(mybullet->x, mybullet->y, 168, 96, 30, 25) == 1  )
			   {
				//  BulletDisappear(mybullet);
					mybullet->disapper = 1;
					return 1;
				 }
		  else
			  return 0;
		}
	else if(Rectangle( mybullet->x, mybullet->y, 211, 0, 109, 240) == 1)
    {
		  if(Rectangle(mybullet->x, mybullet->y, 219, 19, 29, 76) == 1 ||
				 Rectangle(mybullet->x, mybullet->y, 269, 19, 27, 76) == 1 ||
			   Rectangle(mybullet->x, mybullet->y, 217, 115, 56, 25) == 1||
			   Rectangle(mybullet->x, mybullet->y, 219, 160, 29, 55) == 1||
			   Rectangle(mybullet->x, mybullet->y, 269, 160, 27, 55) == 1  )
				 {
				//  BulletDisappear(mybullet);
					mybullet->disapper = 1;
					return 1;
				 }
			else
				return 0;
		}
		else 
			BulletDisappear(mybullet);
		  mybullet->disapper = 1;
		  return 1;
}
//判断子弹击中坦克
void BulletHittingTank(Bullet *mybullet,Tank *OpposingTankA, Tank *OpposingTankB,Tank *OpposingTankC,Tank *OpposingTankD)
{
	if(Rectangle(mybullet->x, mybullet->y, (OpposingTankA->x)-8, (OpposingTankA->y)-8, 22, 22) == 1)
	 {if(mybullet->No != OpposingTankA->No)
	    { if(OpposingTankA->dunpai==0)//没有盾牌才扣血
       	{switch(mybullet->kind)
					{ case 0:
					OpposingTankA->blood -= 1;break;
					case 1:
					OpposingTankA->blood -= 3;break;
					case 2:
					OpposingTankA->blood -= 2;break;
					case 3:
					OpposingTankB->blood -= 4;break;
				  }
				}
		  	mybullet->disapper = 1;
		  	BulletDisappear(mybullet);
				OpposingTankA->kind=0;OpposingTankA->speed=4;OpposingTankA->dunpai=0;
	    }
	}
	else if(Rectangle(mybullet->x, mybullet->y, (OpposingTankB->x)-8, (OpposingTankB->y)-8, 22, 22) == 1)
	    {if(mybullet->No != OpposingTankB->No)
	       { if(OpposingTankB->dunpai==0)//没有盾牌才扣血
				{switch(mybullet->kind)
					{ case 0:
					OpposingTankB->blood -= 1;break;
					case 1:
					OpposingTankB->blood -= 3;break;
					case 2:
					OpposingTankB->blood -= 2;break;
					case 3:
					OpposingTankB->blood -= 4;break;
				  }
				}
		  	mybullet->disapper = 1;
		  	BulletDisappear(mybullet);
				OpposingTankB->kind=0;OpposingTankB->speed=4;OpposingTankB->dunpai=0;
	    }
		}
	else if(Rectangle(mybullet->x, mybullet->y, (OpposingTankC->x)-5, (OpposingTankC->y)-5, 14, 14) == 1)
	  {if(mybullet->No != OpposingTankC->No) 
	    { if(OpposingTankB->dunpai==0)//没有盾牌才扣血
				{switch(mybullet->kind)
					{ case 0:
					OpposingTankC->blood -= 1;break;
					case 1:
					OpposingTankC->blood -= 3;break;
					case 2:
					OpposingTankC->blood -= 2;break;
					case 3:
					OpposingTankC->blood -= 4;break;
				  }
				}
		  	mybullet->disapper = 1;
		  	BulletDisappear(mybullet);
				OpposingTankC->kind=0;OpposingTankC->speed=4;OpposingTankC->dunpai=0;
	    }
		}
  else if(Rectangle(mybullet->x, mybullet->y, (OpposingTankD->x)-5, (OpposingTankD->y)-5, 14, 14) == 1)
    {if(mybullet->No != OpposingTankD->No) 
	   { if(OpposingTankB->dunpai==0)//没有盾牌才扣血
				{switch(mybullet->kind)
					{ case 0:
					OpposingTankD->blood -= 1;break;
					case 1:
					OpposingTankD->blood -= 3;break;
					case 2:
					OpposingTankD->blood -= 2;break;
					case 3:
					OpposingTankD->blood -= 4;break;
				  }
				}
		  	mybullet->disapper = 1;
		  	BulletDisappear(mybullet);
				OpposingTankD->kind=0;OpposingTankD->speed=4;OpposingTankD->dunpai=0;
	    }
		}		 
//	if(mybullet->No==1)
//	 {
//		
//    {
//	  return OpposingTankB->blood;
//	  }
//	}
//	else if(mybullet->No==2)
//	 {
   		
	 // return 1;	 
}


void draw_package(Package *myPack)
{ 

	//switch(myPack->property)
		{ //case 0:
      if(myPack->property==0||myPack->property==1||myPack->property==2)
			{LCD_SetColors(BLUE ,BLACK);//蓝子弹
	ILI9341_DrawCircle(myPack->x,myPack->y,10,0);
	ILI9341_DrawCircle(myPack->x,myPack->y,9,0);	
	ILI9341_DrawLine(myPack->x,myPack->y+9,myPack->x-7,myPack->y-4);
	ILI9341_DrawLine(myPack->x,myPack->y+9,myPack->x+7,myPack->y-4);
	ILI9341_DrawLine(myPack->x-7,myPack->y-4,myPack->x+7,myPack->y-4);		
  ILI9341_DrawLine(myPack->x,myPack->y-9,myPack->x-7,myPack->y+4);
  ILI9341_DrawLine(myPack->x,myPack->y-9,myPack->x+7,myPack->y+4);
	ILI9341_DrawLine(myPack->x-7,myPack->y+4,myPack->x+7,myPack->y+4);}
			//break;
			
					//case 1:
	     else if(myPack->property==3)
			 { LCD_SetColors(WHITE ,BLACK);//白加速
			ILI9341_DrawCircle(myPack->x,myPack->y,10,0);
	ILI9341_DrawCircle(myPack->x,myPack->y,9,0);
  ILI9341_DrawLine(myPack->x-7,myPack->y+4,myPack->x+7,myPack->y+4);
  ILI9341_DrawLine(myPack->x-7,myPack->y-4,myPack->x+7,myPack->y-4);
  ILI9341_DrawLine(myPack->x-2,myPack->y+4,myPack->x-7,myPack->y-4);
  ILI9341_DrawLine(myPack->x-2,myPack->y-4,myPack->x+2,myPack->y+4);
	ILI9341_DrawLine(myPack->x+2,myPack->y-4,myPack->x+7,myPack->y+4);
  ILI9341_DrawLine(myPack->x-2,myPack->y-4,myPack->x-7,myPack->y+4);
  ILI9341_DrawLine(myPack->x-2,myPack->y+4,myPack->x+2,myPack->y-4);
	ILI9341_DrawLine(myPack->x+2,myPack->y+4,myPack->x+7,myPack->y-4);}
			//break;
			//case 2:
       
	     else //if(myPack->property==4)
			 {LCD_SetColors(RED ,BLACK);//红加盾
			  ILI9341_DrawCircle(myPack->x,myPack->y,10,0);
	ILI9341_DrawCircle(myPack->x,myPack->y,9,0);
  ILI9341_DrawLine(myPack->x-7,myPack->y+4,myPack->x-2,myPack->y+4);
  ILI9341_DrawLine(myPack->x+2,myPack->y+4,myPack->x+7,myPack->y+4);
  ILI9341_DrawLine(myPack->x-7,myPack->y-4,myPack->x-2,myPack->y-4);
  ILI9341_DrawLine(myPack->x+2,myPack->y-4,myPack->x+7,myPack->y-4);
  ILI9341_DrawLine(myPack->x-2,myPack->y-4,myPack->x+2,myPack->y+4);
  ILI9341_DrawLine(myPack->x-2,myPack->y+4,myPack->x+2,myPack->y-4);
  ILI9341_DrawLine(myPack->x-5,myPack->y,myPack->x-7,myPack->y-4);
  ILI9341_DrawLine(myPack->x+5,myPack->y,myPack->x+7,myPack->y-4);
  ILI9341_DrawLine(myPack->x-5,myPack->y,myPack->x-7,myPack->y+4);
  ILI9341_DrawLine(myPack->x+5,myPack->y,myPack->x+7,myPack->y+4);	
  ILI9341_DrawLine(myPack->x-5,myPack->y,myPack->x-7,myPack->y-4);
  ILI9341_DrawLine(myPack->x+5,myPack->y,myPack->x+5,myPack->y);}
			//break;
      //default: break;
	  } 
	//ILI9341_DrawRectangle(myPack->x-5, myPack->y-5, PACKAGE_SIZE, PACKAGE_SIZE,1);
	

  
  


  
//	ILI9341_DrawCircle(myPack->x,myPack->y,10,0);
//	ILI9341_DrawCircle(myPack->x,myPack->y,9,0);	
//	ILI9341_DrawLine(myPack->x,myPack->y+9,myPack->x-7,myPack->y-4);
//	ILI9341_DrawLine(myPack->x,myPack->y+9,myPack->x+7,myPack->y-4);
//	ILI9341_DrawLine(myPack->x-7,myPack->y-4,myPack->x+7,myPack->y-4);		
//  ILI9341_DrawLine(myPack->x,myPack->y-9,myPack->x-7,myPack->y+4);
//  ILI9341_DrawLine(myPack->x,myPack->y-9,myPack->x+7,myPack->y+4);
//	ILI9341_DrawLine(myPack->x-7,myPack->y+4,myPack->x+7,myPack->y+4);
//	ILI9341_DrawLine(myPack->x-2,myPack->y-4,myPack->x+2,myPack->y+4);
//  ILI9341_DrawLine(myPack->x-2,myPack->y+4,myPack->x+2,myPack->y-4);
//	ILI9341_DrawLine(myPack->x+5,myPack->y,myPack->x+5,myPack->y);
	
}

void clear_package(Package *myPack)
{ 
	ILI9341_Clear(myPack->x-11,myPack->y-11,PACKAGE_SIZE,PACKAGE_SIZE);//擦除
//	switch(pose_no)
//		{ case 0:
//       ILI9341_DrawRectangle(50, 50, PACKAGE_SIZE, PACKAGE_SIZE,1);break;
//			case 1:
//       ILI9341_DrawRectangle(50, 50, PACKAGE_SIZE, PACKAGE_SIZE,1);break;
//			case 2:
//       ILI9341_DrawRectangle(50, 50, PACKAGE_SIZE, PACKAGE_SIZE,1);break;
//			case 3:
//       ILI9341_DrawRectangle(50, 50, PACKAGE_SIZE, PACKAGE_SIZE,1);break;
//	  } 
}

void creat_package(Package *myPack)
{  	 
	 //srand(100);
	 //pose_num=rand()%7;
	
	 if(pose_num++>5) {pose_num=0;}
	 //else {pose_num++;}
   //property_num=rand()%4;

	 if(property_num>4){property_num=0;}
	 else property_num++;
	 
   switch(pose_num)
	 {
	   case 0:
			 myPack->x=25;myPack->y=125;break;
	   case 1:
			 myPack->x=300;myPack->y=125;break;
	   case 2:
			 myPack->x=130;myPack->y=170;break;
	   case 3:
			 myPack->x=25;myPack->y=125;break;
		 case 4:
			 myPack->x=110;myPack->y=50;break;
		 case 5:
			 myPack->x=162;myPack->y=50;break;
		 case 6:
			 myPack->x=220;myPack->y=110;break;
		 default: break;
	 }
   myPack->property=property_num; 
}

void Tank_change(Package *myPack,Tank *tank)
{   
	  //给予坦克弹药类型
//	  tank->kind=myPack->property;
    switch(myPack->property)
		{
		  //case 0: tank->kind=0;break;//一旦中弹，所有技能失效  蓝
		  case 0: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//子弹升级,子弹暂时只有4种
			case 1: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//子弹升级,子弹暂时只有4种
			case 2: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//子弹升级,子弹暂时只有4种
		  //case 2: tank->kind=myPack->property; break;
      case 3:	tank->speed=8; break;//中速  速度有问题？	  白
			//case 4: tank->speed=12; break;//高速
			case 4: tank->dunpai=1; break;//加盾，盾牌暂定只有一次效果   红
	    default: break;
		}
}

void Tank_eatPackage(Package *myPack,Tank *OpposingTank)
{    
     if(Rectangle(myPack->x, myPack->y, (OpposingTank->x)-8, (OpposingTank->y)-8, 22, 22) == 1)
     {
			 Tank_change(myPack,OpposingTank);//先改变坦克属性
			 creat_package(myPack);//重新添加包       
     }
}


