#include "myLib.h"

void drawImage3(int r, int c, int width, int height, const u16 *image) {
  for (int row = 0; row < height; row++) {
    REG_DMA3SAD = (u32)(&image[OFFSET(row, 0, width)]);
    REG_DMA3DAD = (u32)(&videoBuffer[OFFSET(row+r, c, 240)]);
    //DMA_DESTINATION_INCREMENT is on by default, but we set it just for clarity here
    REG_DMA3CNT = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
  }
}

//struct for individual ball/rect/etc that keeps track of old location and new location
//to move: erase and then redraw
//update after you're done with your logic that depends on the location of the balls
//collision check: boundaries of rectangle

void drawRect(int row, int col, int height, int width, volatile u16 color) {
  for (int r = 0; r < height; r++) {
    REG_DMA3SAD = (u32)&color;
    REG_DMA3DAD = (u32)(&videoBuffer[OFFSET(row + r, col, 240)]);
    REG_DMA3CNT = width | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
  }
}

void fillScreen(volatile u16 color) {
  drawRect(0, 0, 160, 240, color);

  // for (int r = 0; r < 160; r++) {
  //   REG_DMA3SAD = (u32)&color;
  //   REG_DMA3DAD = (u32)(&videoBuffer[r]);
  //   REG_DMA3CNT = 240 | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
  // }

}


void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row,col, 240)] = color;
}

//TWO FUNCTIONS BELOW COPIED FROM BILL'S CODE:
void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<5000*n; i++)
	{
		x = x + 1;
	}
}

void waitForVBlank()
{
	while(*SCANLINECOUNTER > 160);
	while(*SCANLINECOUNTER < 160);
}
