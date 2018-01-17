#include "element.h"
#include "bsp_ili9341_lcd.h"
#include "stdlib.h"


#define TANK_BLOCK_SIZE 	6
#define TANK_BLOCK_SPACE	1
#define BULLET_SIZE	4
#define TANK_STEP	4
#define BULLET_STEP	16
#define BRICK_SIZE 4
#define RAND_TANK_SIZE 	4
#define RAND_TANK_SPACE	1


u16 x,y;

void delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

u8 sort(int *l)
{
        u8 i;
        u8 pos = 0;
        int min = *l;
        for(i=1;i!=4;i++)
        {
                if(*(l+i)<min)
                {
                        min =*(l+i);
                        pos = i;
                }
        }
        return pos;
}



u8 is_Wall(u16 x, u16 y)
{
				if((y >13)&&(y < 101))
				{
					if((x > 12) && (x<52))
					{
						return 1;
					}
					if((x > 59) && (x<100))
					{
						return 1;
					}

					if((x >208) && (x<250))
					{
						return 1;
					}
					if((x >258) && (x<301))
					{
						return 1;
					}
				}//up1
				if((y > 13)&&(y < 83))
				{
					if((x > 109) && (x<154))
					{
						return 1;
					}
					if((x > 159) && (x<201))
					{
						return 1;
					}
				}//up2
				if((y >89)&&(y < 128))
				{
					if((x > 110) && (x < 152))
					{
						return 1;
					}
					if((x > 160) && (x < 201))
					{
						return 1;
					}							
				}//mid1
				if((y > 109)&&(y < 147))
				{
					if((x > 33) && (x < 102))
					{
						return 1;
					}
					if((x > 207) && (x < 277))
					{
						return 1;
					}
				}//mid2
				if((y > 151) && (y < 223))
				{
					if((x > 12) && (x < 52))
					{
						return 1;
					}
					if((x > 59) && (x<102))
					{
						return 1;
					}
					if((x >208) && (x<250))
					{
						return 1;
					}
					if((x >258) && (x<300))
					{
						return 1;		
					}						
			  }
				return 0;
}
/**
 * @brief  A*算法
 * @param  (x,y)起点（dx,dy)终点
 * @retval 无
 */
void A_star(u16 x, u16 y, u16 dx, u16 dy, Tank *myTank)
{
	int l[4] = {0,0,0,0};
	//int min;
	u8 i = 0;
	while((x!=dx) || (y!=dy))
	{
		if((!is_Wall(x+1,y)) && (x+1<313) && (y>7) && (y<233))
		{
			l[0] = abs(dx-(x+1)) + abs(dy-y);
		}
		else
		{
			l[0] = 20000;
		}
		if((!is_Wall(x,y+1)) && (x>7) && (y+1<313)&& (y+1<233))
		{
			l[1] = abs(dx-x) + abs(dy-(y+1));
		}
		else
		{
			l[1] = 20001;
		}
		if((!is_Wall(x-1,y)) && (x-1>7) && (y<233) && (y>7))
		{
			l[2] = abs(dx-(x-1)) + abs(dy-y);
		}
		else
		{
			l[2] = 20002;
		}
		if((!is_Wall(x,y-1)) && (x<313) && (x>7) && (y-1>7))
		{
			l[3] = abs(dx-x) + abs(dy-(y-1));
		}
		else
		{
			l[3] = 20003;
		}
		i = sort(l);
		switch(i)
		{
			case 0: 
				x = x+1;Tank_turn(myTank,3); break;
			case 1:
				y = y+1;Tank_turn(myTank,0);break;
			case 2: 
				x = x-1;Tank_turn(myTank,1);break;
			case 3: 
				y = y-1;Tank_turn(myTank,2);break;
			default :	LCD_SetColors(CYAN ,BLACK); ILI9341_SetPointPixel(x,y); break;
		}
		myTank->x = x;
		myTank->y = y;
		//LCD_SetColors(RED,BLACK);
		Tank_move(myTank);
		draw_Tank(myTank);
		delay(100000);
//		ILI9341_SetPointPixel(x,y);
	}

}

/**
 * @brief  绘制坦克
 * @param  myTank ：tankA或tankB
 * @retval 无
 */
void draw_Tank(Tank *myTank)							//根据坦克的xy[3][3]成员属性在屏幕上对应栅格位置显示坦克
{
		if(myTank->No==1)
		{
			if(myTank->blood <= 3)
			{
				LCD_SetColors(RED ,BLACK);
			}
			else 
				LCD_SetColors(YELLOW ,BLACK);
		}			
		if(myTank->No==2)
		{
			if(myTank->blood <= 3)
			{
				LCD_SetColors(RED ,BLACK);
			}
			else
				LCD_SetColors(MAGENTA, BLACK);
		}
		if(myTank->No > 2) 
			LCD_SetColors(WHITE ,BLACK);
		if(myTank->No==1 || myTank->No==2)
		{
			if(myTank->blood > 0)
			{
				switch(myTank->direction)
				{
					case 0://right
						ILI9341_DrawRectangle ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//7
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//1
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//8
						break;
					case 1://up
						ILI9341_DrawRectangle ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//7
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//9
						break;
					case 2://left
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//8
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//3
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE , 1 );//9
						break;
					case 3://down
						ILI9341_DrawRectangle ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//1
						ILI9341_DrawRectangle ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//3
						ILI9341_DrawRectangle ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, 1 );//8
						break;
					default : break; 
				}
			}
			else
			{
				delay(500000);
			}
	}
		else
		{
			if(myTank->blood > 0)
			{
				switch(myTank->direction)
				{
					case 0://right
						ILI9341_DrawRectangle ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//7
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//1
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//8
						break;
					case 1://up
						ILI9341_DrawRectangle ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//7
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y+RAND_TANK_SIZE+RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//9
						break;
					case 2://left
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//2
						ILI9341_DrawRectangle ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//8
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//3
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE , 1 );//9
						break;
					case 3://down
						ILI9341_DrawRectangle ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//5
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SPACE-RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//1
						ILI9341_DrawRectangle ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//3
						ILI9341_DrawRectangle ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE , 1 );//4
						ILI9341_DrawRectangle ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//6
						ILI9341_DrawRectangle ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE, 1 );//8
						break;
					default : break; 
				}
			}
			else
			{
				delay(500000);
			}
		}
}
/**
 * @brief  坦克移动
 * @param  myTank ：tankA或tankB
 * @retval 无
 */
void Tank_move(Tank *myTank)
{
	x = myTank->x;
	y = myTank->y;
	if(myTank->No==1 || myTank->No==2)
	{
	switch(myTank->direction)
	{
		case 0://right
			  ILI9341_Clear(myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear(myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				myTank->x = myTank->x;
				myTank->y = myTank->y+4;
				if(myTank->y>(240-2*TANK_BLOCK_SIZE-TANK_BLOCK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
				
				break;
		case 1://up
				ILI9341_Clear( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//5
				ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
				ILI9341_Clear( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//7
				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//9
				myTank->x = myTank->x-4;
				myTank->y = myTank->y;	
				if(myTank->x<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
				break;
		case 2://left
				ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
			  ILI9341_Clear ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//5
			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//8
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//3
			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//9
				myTank->x = myTank->x;
				myTank->y = myTank->y-4;	
				if(myTank->y<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
				break;		
		case 3://down
				ILI9341_Clear ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//5
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//1
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//3
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//4
				ILI9341_Clear ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
		   	ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//8
				myTank->x = myTank->x+4;
				myTank->y = myTank->y;
				if(myTank->x >= (320-2*TANK_BLOCK_SIZE-TANK_BLOCK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
				break;	
				
		default : break;		
			}
		}
	else
	{	    switch(myTank->direction)
				{
					case 0://right
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE );//7
						ILI9341_Clear ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE );//1
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//8
						myTank->x = myTank->x;
						myTank->y = myTank->y+2;
						if(myTank->y>(240-2*RAND_TANK_SIZE-RAND_TANK_SPACE))
						{
							myTank->x = x;
							myTank->y = y;
						}
						if(is_Wall(myTank->x, myTank->y))
						{
							myTank->x = x;
							myTank->y = y;					
						}
								break;
					case 1://up
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE  );//4
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//7
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y+RAND_TANK_SIZE+RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//9
									myTank->x = myTank->x-2;
				myTank->y = myTank->y;	
				if(myTank->x<(RAND_TANK_SIZE+RAND_TANK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
						break;
					case 2://left
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//4
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//8
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE);//3
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//9
									myTank->x = myTank->x;
				myTank->y = myTank->y-2;	
				if(myTank->y<(RAND_TANK_SIZE+RAND_TANK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
						break;
					case 3://down
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SPACE-RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//1
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//3
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE  );//4
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE);//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//8
									myTank->x = myTank->x+2;
				myTank->y = myTank->y;
				if(myTank->x >= (320-2*RAND_TANK_SIZE-RAND_TANK_SPACE))
				{
					myTank->x = x;
					myTank->y = y;
				}
				if(is_Wall(myTank->x, myTank->y))
				{
					myTank->x = x;
					myTank->y = y;					
				}
						break;
					default : break; 
				}
			}
	//draw_tank(Tank *myTank);
}
/**
 * @brief  坦克转向
 * @param  myTank ：tankA或tankB
 * @param  dir ：0：右；1：上；2：左；3：下
 * @retval 无
 */
void Tank_turn(Tank *myTank, u8 dir)
{
	if(myTank->No==1 || myTank->No==2){
	switch(myTank->direction)
	{
		case 0://right
			  ILI9341_Clear(myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear(myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				ILI9341_Clear(myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
				break;
		case 1://up
				ILI9341_Clear( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//5
				ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
				ILI9341_Clear( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//7
				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//9
				break;
		case 2://left
				ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
			  ILI9341_Clear ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//5
			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//8
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//3
			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//9
				break;		
		case 3://down
				ILI9341_Clear ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//5
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//1
			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//3
				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//4
				ILI9341_Clear ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
		   	ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//8
				break;			
		default : break;		
			}
		}
	else
	{
				switch(myTank->direction)
				{
					case 0://right
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE );//7
						ILI9341_Clear ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE );//1
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//8
						break;
					case 1://up
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE  );//4
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//7
						ILI9341_Clear ( myTank->x+RAND_TANK_SIZE+RAND_TANK_SPACE, myTank->y+RAND_TANK_SIZE+RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//9
						break;
					case 2://left
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//2
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE);//4
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//8
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE);//3
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//9
						break;
					case 3://down
						ILI9341_Clear ( myTank->x, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE);//5
						ILI9341_Clear ( myTank->x-RAND_TANK_SIZE-RAND_TANK_SPACE, myTank->y-RAND_TANK_SPACE-RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//1
						ILI9341_Clear ( myTank->x-RAND_TANK_SPACE-RAND_TANK_SIZE, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE );//3
						ILI9341_Clear ( myTank->x, myTank->y-RAND_TANK_SIZE-RAND_TANK_SPACE, RAND_TANK_SIZE, RAND_TANK_SIZE  );//4
						ILI9341_Clear ( myTank->x, myTank->y+RAND_TANK_SPACE+RAND_TANK_SIZE, RAND_TANK_SIZE, RAND_TANK_SIZE);//6
						ILI9341_Clear ( myTank->x+RAND_TANK_SPACE+RAND_TANK_SIZE, myTank->y, RAND_TANK_SIZE, RAND_TANK_SIZE );//8
						break;
					default : break; 
			}
	}
	//draw_tank(Tank *myTank);
	myTank->direction = dir;
}


/**
 * @brief  子弹装填，在子弹初始位置绘制子弹
 * @param  myBullet
 * @param  myTank 
 * @retval 无
 */
//void Bullet_load(Bullet *myBullet,Tank *myTank)
//{
//		if(myBullet->No==1)
//		LCD_SetColors(YELLOW ,BLACK);	
//		else
//		LCD_SetColors(MAGENTA, BLACK);
//	switch(myTank->direction)
//	{
//		case 0://right
//			    myBullet->x = myTank->x+1;
//					myBullet->y = myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE+BULLET_SIZE;
//			    ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
////				ILI9341_Clear(myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
////				ILI9341_Clear(myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
////				ILI9341_Clear(myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
////				ILI9341_Clear(myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
////				ILI9341_Clear(myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);
////				if((myTank->x<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))|(myTank->y<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE)))
////				{
////					
////					myTank->y = y;
////				}
//				break;
//		case 1://up
//	      	myBullet->x = myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE-BULLET_SIZE;
//					myBullet->y = myTank->y+1;					
//				  ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
////				ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//2
////				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
////				ILI9341_Clear( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
////				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//7
////				ILI9341_Clear ( myTank->x+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, myTank->y+TANK_BLOCK_SIZE+TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//9
////				myBullet->x = myBullet->x-BULLET_STEP;
////				myBullet->y = myBullet->y;	
////				if((myTank->x<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))|(myTank->y<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE)))
////				{
////					myTank->x = x;
////					myTank->y = y;
////				}
//				break;
//		case 2://left
//					myBullet->x = myTank->x+1;
//					myBullet->y = myTank->y-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE-BULLET_SIZE;			
//				  ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
////				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//4
////			  ILI9341_Clear ( myTank->x, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//5
////			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//8
////			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//3
////			  ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//9
////				myBullet->x = myBullet->x;
////				myBullet->y = myBullet->y-BULLET_STEP;	
////				if((myTank->x<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))|(myTank->y<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE)))
////				{
////					myTank->x = x;
////					myTank->y = y;
////				}
//				break;		
//		case 3://down
//			    myBullet->x = myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE+BULLET_SIZE;
//					myBullet->y = myTank->y+1;		
//				  ILI9341_DrawRectangle(myBullet->x, myBullet->y, BULLET_SIZE, BULLET_SIZE,1);
////			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//1
////			  ILI9341_Clear ( myTank->x-TANK_BLOCK_SPACE-TANK_BLOCK_SIZE, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//3
////				ILI9341_Clear ( myTank->x, myTank->y-TANK_BLOCK_SIZE-TANK_BLOCK_SPACE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE);//4
////				ILI9341_Clear ( myTank->x, myTank->y+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//6
////		   	ILI9341_Clear ( myTank->x+TANK_BLOCK_SPACE+TANK_BLOCK_SIZE, myTank->y, TANK_BLOCK_SIZE, TANK_BLOCK_SIZE );//8
////				myBullet->x = myBullet->x+BULLET_STEP;
////				myBullet->y = myBullet->y;	
////				if((myTank->x<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE))|(myTank->y<(TANK_BLOCK_SIZE+TANK_BLOCK_SPACE)))
////				{
////					myTank->x = x;
////					myTank->y = y;
////				}
//				break;		
//		default : break;		
//			}	
//	
//	
//}

/**
 * @brief  绘制砖块
 * @param  x:在特定扫描方向下该点的X坐标
 * @param  y:在特定扫描方向下该点的y坐标
 * @retval 无
 */
//void draw_Brick(u16 x, u16 y)
//{
//	ILI9341_DrawRectangle ( x-BRICK_SIZE, y-BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, 1 );//1
//	ILI9341_DrawRectangle ( x-BRICK_SIZE, y+BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, 1 );//3
//	ILI9341_DrawRectangle ( x+BRICK_SIZE, y+BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, 1 );//9
//	ILI9341_DrawRectangle ( x+BRICK_SIZE, y-BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, 1 );//7
//	ILI9341_DrawRectangle ( x, y, BRICK_SIZE, BRICK_SIZE, 1 );//5
//}

/**
 * @brief  绘制墙
 * @param  x:在特定扫描方向下该点的X坐标 
 * @param  y:在特定扫描方向下该点的y坐标
 * @param  L:墙的长度
 * @param  dir:墙的延伸方向 0：下；1：右
 * @retval 无
 */
//void draw_Wall(u16 x, u16 y, u16 L, u8 dir)
//{
//	int i = 0;
//	LCD_SetColors(WHITE ,BLACK);	
//	switch(dir)
//	{
//		case 0:
//			for(i=0;i!=L/12;i++)
//		{
//				draw_Brick(x, y);
//				x = x + 3*BRICK_SIZE;
//		}
//		break;
//		case 1:
//			for(i=0;i!=L/12;i++)
//		{
//				draw_Brick(x, y);
//				y = y + 3*BRICK_SIZE;
//		}
//		break;
//		default : break;		
//	}		
//}


