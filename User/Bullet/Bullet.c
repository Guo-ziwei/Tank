#include "Bullet.h"
#include "stm32f10x.h"
#include <stdlib.h> 

#define TANK_BLOCK_SIZE 	6  // С����ߴ�
#define TANK_BLOCK_SPACE	2  // ����ߴ�
#define BULLET_SIZE	4        // �ӵ��ߴ�
#define BULLET_Middle_SIZE 6 // ���ӵ��ߴ�
#define BULLET_Big_SIZE	8    // ���ӵ��ߴ�
#define BULLET_STEP	16       // �ӵ�����
#define BRICK_SIZE 4         //
#define PACKAGE_SIZE 22      // ���ܰ��ߴ�
//int Flag_Move = 0;
int pose_num=-1,property_num=-1;

//�ص�
void draw_heavy_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//�ӵ�����
		{
		case 0://right
			   			ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+29, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+22, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
					   	ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y+15, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�		       
				break;
		case 1://up
			   			ILI9341_DrawRectangle ( myBullet->x-27, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x-20, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
			   			ILI9341_DrawRectangle ( myBullet->x-13, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
				break;
		case 2://left
			   			ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-27, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-20, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
					   	ILI9341_DrawRectangle ( myBullet->x+1, myBullet->y-13, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�	
				break;		
		case 3://down
			   			ILI9341_DrawRectangle ( myBullet->x+29, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x+22, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�	
			   			ILI9341_DrawRectangle ( myBullet->x+15, myBullet->y+1, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�		      
				break;		
		default : break;		
		}
}
//�����ص�ҩ
void clear_heavy_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//�ӵ�����
		{
		case 0://right
			   			ILI9341_Clear ( myBullet->x+1, myBullet->y+29, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x+1, myBullet->y+22, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
					   	ILI9341_Clear ( myBullet->x+1, myBullet->y+15, BULLET_SIZE, BULLET_SIZE);//�����ӵ�	
				break;
		case 1://up
              ILI9341_Clear ( myBullet->x-27, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
		          ILI9341_Clear ( myBullet->x-20, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
			   			ILI9341_Clear ( myBullet->x-13, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
				break;
		case 2://left
			   			ILI9341_Clear ( myBullet->x+1, myBullet->y-27, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
		          ILI9341_Clear ( myBullet->x+1, myBullet->y-20, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
					   	ILI9341_Clear ( myBullet->x+1, myBullet->y-13, BULLET_SIZE, BULLET_SIZE);//�����ӵ�	
				break;		
		case 3://down
			   			ILI9341_Clear ( myBullet->x+29, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
		          ILI9341_Clear ( myBullet->x+22, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�	
			   			ILI9341_Clear ( myBullet->x+15, myBullet->y+1, BULLET_SIZE, BULLET_SIZE);//�����ӵ�		      
				break;		
		default : break;		
		}
}
//����
void draw_3_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//�ӵ�����
		{
		case 0://right
			   			ILI9341_DrawRectangle ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
				break;
		case 1://up
			   			ILI9341_DrawRectangle ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�	
				break;
		case 2://left
			   			ILI9341_DrawRectangle ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�	
				break;		
		case 3://down
			   			ILI9341_DrawRectangle ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�
		          ILI9341_DrawRectangle ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE, 1 );//�����ӵ�	
				break;		
		default : break;		
		}
}

//��������
void clear_3_Bullet(Bullet *myBullet)
{

	switch(myBullet->direction)//�ӵ�����
		{
		case 0://right
			   			ILI9341_Clear ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
				break;
		case 1://up
			   			ILI9341_Clear ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE);//�����ӵ�	
				break;
		case 2://left
			   			ILI9341_Clear ( myBullet->x+7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x-7, myBullet->y, BULLET_SIZE, BULLET_SIZE );//�����ӵ�	
				break;		
		case 3://down
			   			ILI9341_Clear ( myBullet->x, myBullet->y+7, BULLET_SIZE, BULLET_SIZE );//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE);//�����ӵ�
		          ILI9341_Clear ( myBullet->x, myBullet->y-7, BULLET_SIZE, BULLET_SIZE );//�����ӵ�	
				break;		
		default : break;		
		}
}
//�����ӵ�
void draw_Bullet(Bullet *myBullet)
{
	myBullet->disapper = 0;
	if(myBullet->No==1)//�ӵ�����
	LCD_SetColors(YELLOW ,BLACK);	
		else
		LCD_SetColors(MAGENTA, BLACK);
	switch(myBullet->kind)//�ӵ�����
		{
			case 0: //��ͨ�ӵ�
			myBullet->speed=10;
			//if(BulletHittingWall(myBullet)==0)
			ILI9341_DrawRectangle ( myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE, 1 );
			 break;
			case 1: //�����ӵ�
			myBullet->speed=8;
			//if(BulletHittingWall(myBullet)==0)
			ILI9341_DrawRectangle ( myBullet->x-2, myBullet->y-2, BULLET_Big_SIZE, BULLET_Big_SIZE, 1 );//�����ӵ�	
		  break;
			case 2: //��������
			myBullet->speed=18;
			//if(BulletHittingWall(myBullet)==0)
      draw_3_Bullet(myBullet);
			break;
			case 3: //�ص�
			myBullet->speed=16;
			//if(BulletHittingWall(myBullet)==0)
      draw_heavy_Bullet(myBullet);
			break;
		}
}


//̹��װ��
void Bullet_load(Bullet *myBullet,Tank *myTank)
{   
	  myBullet->kind=myTank->kind;//����̹������ȷ����ҩ����
	  myBullet->No = myTank->No;
	 // myBullet->disapper =0;
//		if(myTank->No==1)
//		  { //myBullet->kind=0; 
//		    LCD_SetColors(YELLOW ,BLACK);
//			  myBullet->No = myTank->No;
//		  }			
//		else
//			{ //myBullet->kind=3;//�����ص� 
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
//�ӵ��ƶ�
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
//�ж��ӵ��Ƿ��ھ�������
int Rectangle(int Bullet_x,int Bullet_y,int X,int Y,int L,int W)
{
  if((X <= Bullet_x)&&(Bullet_x < X + L)&&(Y <= Bullet_y)&&(Bullet_y < Y + W))
    return 1;//�ھ������淵��1
  else
	  return 0;//�����ⷵ��0
}
//�ӵ���ʧ����
void BulletDisappear(Bullet *myBullet)
{
	switch(myBullet->kind)//�ӵ�����
		{
			case 0:
				//if(BulletHittingWall(myBullet))
			ILI9341_Clear(myBullet->x,myBullet->y,BULLET_SIZE,BULLET_SIZE);break;//����
			case 1:
			ILI9341_Clear(myBullet->x-2,myBullet->y-2,BULLET_Big_SIZE,BULLET_Big_SIZE);break;
		  case 2:
      clear_3_Bullet(myBullet); break;
			case 3:
			clear_heavy_Bullet(myBullet);break;
		}
}
//�ж��ӵ��Ƿ�ײǽ
int BulletHittingWall(Bullet *mybullet)//1��ʾ����������0��ʾ��ʾ���ڷ�ǽ����
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
//�ж��ӵ�����̹��
void BulletHittingTank(Bullet *mybullet,Tank *OpposingTankA, Tank *OpposingTankB,Tank *OpposingTankC,Tank *OpposingTankD)
{
	if(Rectangle(mybullet->x, mybullet->y, (OpposingTankA->x)-8, (OpposingTankA->y)-8, 22, 22) == 1)
	 {if(mybullet->No != OpposingTankA->No)
	    { if(OpposingTankA->dunpai==0)//û�ж��Ʋſ�Ѫ
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
	       { if(OpposingTankB->dunpai==0)//û�ж��Ʋſ�Ѫ
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
	    { if(OpposingTankB->dunpai==0)//û�ж��Ʋſ�Ѫ
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
	   { if(OpposingTankB->dunpai==0)//û�ж��Ʋſ�Ѫ
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
			{LCD_SetColors(BLUE ,BLACK);//���ӵ�
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
			 { LCD_SetColors(WHITE ,BLACK);//�׼���
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
			 {LCD_SetColors(RED ,BLACK);//��Ӷ�
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
	ILI9341_Clear(myPack->x-11,myPack->y-11,PACKAGE_SIZE,PACKAGE_SIZE);//����
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
	  //����̹�˵�ҩ����
//	  tank->kind=myPack->property;
    switch(myPack->property)
		{
		  //case 0: tank->kind=0;break;//һ���е������м���ʧЧ  ��
		  case 0: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//�ӵ�����,�ӵ���ʱֻ��4��
			case 1: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//�ӵ�����,�ӵ���ʱֻ��4��
			case 2: tank->kind++; if(tank->kind>4) {tank->kind=0;} break;//�ӵ�����,�ӵ���ʱֻ��4��
		  //case 2: tank->kind=myPack->property; break;
      case 3:	tank->speed=8; break;//����  �ٶ������⣿	  ��
			//case 4: tank->speed=12; break;//����
			case 4: tank->dunpai=1; break;//�Ӷܣ������ݶ�ֻ��һ��Ч��   ��
	    default: break;
		}
}

void Tank_eatPackage(Package *myPack,Tank *OpposingTank)
{    
     if(Rectangle(myPack->x, myPack->y, (OpposingTank->x)-8, (OpposingTank->y)-8, 22, 22) == 1)
     {
			 Tank_change(myPack,OpposingTank);//�ȸı�̹������
			 creat_package(myPack);//������Ӱ�       
     }
}


