#include "mapdata.h"
#include "./lcd/bsp_ili9341_lcd.h"

void map(void)
{
	int xx ;
	int yy ;
	u16 color;
	for(xx = 0;xx != 240;xx++)
	{
		for(yy = 0;yy != 320;yy++)
		{
			color = gImage_pic[(yy*240+xx)*2+1];
			color<<=8;
			color = color + gImage_pic[(yy*240+xx)*2];
			LCD_SetTextColor(color);
		  ILI9341_SetPointPixel (xx,yy);
		}
	}
}

void map_start(void)
{
	int xx ;
	int yy ;
	u16 color;
	for(xx = 0;xx != 240;xx++)
	{
		for(yy = 0;yy != 320;yy++)
		{
			color = gImage_start[(yy*240+xx)*2+1];
			color<<=8;
			color = color + gImage_start[(yy*240+xx)*2];
			LCD_SetTextColor(color);
		  ILI9341_SetPointPixel (xx,yy);
		}
	}
}
	
void map_end(void)
{
	int xx ;
	int yy ;
	u16 color;
	for(xx = 0;xx != 240;xx++)
	{
		for(yy = 0;yy != 320;yy++)
		{
			color = gImage_end[(yy*240+xx)*2+1];
			color<<=8;
			color = color + gImage_end[(yy*240+xx)*2];
				LCD_SetTextColor(color);
				ILI9341_SetPointPixel (xx,yy);
			
		}
	}
}

