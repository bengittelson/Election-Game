#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "gamePlay.h"


void moveObj(unsigned int* x, unsigned int* y, int height, int width, u16 backgroundColor) {
  //erase old rectangle (draw rect with the background color)
  drawRect(*x, *y, height, width, backgroundColor);
  if (KEY_DOWN_NOW(BUTTON_DOWN) && *x + height + 1 < 160) {
    *x = *x + 1;
  }

  if (KEY_DOWN_NOW(BUTTON_UP) && *x != 0) {
    *x = *x - 1;
  }

  if (KEY_DOWN_NOW(BUTTON_LEFT && *y != 0)) {
    *y = *y - 1;
  }

  if (KEY_DOWN_NOW(BUTTON_RIGHT) && *y + width + 1 < 240) {
    *y = *y + 1;
  }
}


//collision detection return 0 or 1
int collision(RECTANGLE* rect1, RECTANGLE* rect2) {
  RECTANGLE rectangle1 = *rect1;
  RECTANGLE rectangle2 = *rect2;

  if (rectangle1.y < rectangle2.y + rectangle2.width &&
    rectangle1.y + rectangle1.width > rectangle2.y && rectangle1.x < rectangle2.x +
  rectangle2.height && rectangle1.height + rectangle1.x > rectangle2.x) {
    return 1;
  }
  return 0;
}

int detectCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
  if (y1 < y2 + width2 && y1 + width1 > y2 && x1 < x2 + height2 && height1 + x1 > x2) {
    return 1;
  }
  return 0;
}
