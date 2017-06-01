#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "text.h"
#include "gamePlay.h"

#include "titlescreen.h"
#include "democrat.h"
#include "whitehouse.h"
#include "republican2.h"
#include "trump.h"
#include "pantsuit.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;
char *buffer;
char varBuffer[30];
int lives = 3;
int numEnemy;


enum GBAState {
	START,
	START_NODRAW,
	INSTRUCTIONS,
	INSTRUCTIONS_NODRAW,
	LOSE,
	LOSE_NODRAW,
	STATE3,
	STATE3_NODRAW,
	WIN,
	WIN_NODRAW
};

int main()
{
    //set REG_DISPCNT
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    enum GBAState state = START;
  	unsigned int prevPressed = 0;
		int party;

		party = 0;
		PLAYER myPlayer;
		myPlayer.y = 0;
		myPlayer.x = 0;
		myPlayer.height = DEMOCRAT_HEIGHT;
		myPlayer.width = DEMOCRAT_WIDTH;
		myPlayer.image = democrat;

		//create array of enemy structs
		numEnemy = 7;
		PLAYER enemies[numEnemy];

  	while(1) {
  		switch(state) {
  		case START:
				waitForVBlank();
				drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titlescreen);
				buffer = "WELCOME TO VOTE RUNNER!";
				drawString(10, 55, buffer, RED);
				buffer = "Press A to start.";
				drawString(149, 73, buffer, BLUE);
        state = START_NODRAW;
  			break;
  		case START_NODRAW:
  			if (KEY_DOWN_NOW(BUTTON_A) && prevPressed != KEY_DOWN_NOW(BUTTON_A)) {
  				state = INSTRUCTIONS;
  			}
  			break;

  		case INSTRUCTIONS:
				waitForVBlank();
				drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titlescreen);
				buffer = "Ready to get out the vote?";
				drawString(10, 35, buffer, BLUE);
				buffer = "Here's how to play: ";
				drawString(25, 20, buffer, BLUE);
				buffer = "1. Use the arrow keys to move.";
				drawString(35, 20, buffer, RED);
				buffer = "2. Dodge members of the opposing";
				drawString(45, 20, buffer, WHITE);
				buffer = "party to get your candidate to";
				drawString(55, 20, buffer, WHITE);
				buffer = "the White House.";
				drawString(65, 20, buffer, WHITE);
				buffer = "3. You have three lives.";
				drawString(75, 20, buffer, BLUE);
				buffer = "4. Press select to return to ";
				drawString(85, 20, buffer, RED);
				buffer = "the home screen at any time. ";
				drawString(95, 20, buffer, RED);
				buffer = "5. Now press L to play as a Democrat";
				drawString(105, 20, buffer, WHITE);
				buffer = "and R to play as a Republican.";
				drawString(115, 20, buffer, WHITE);
  			state = INSTRUCTIONS_NODRAW;
  			break;
  		case INSTRUCTIONS_NODRAW:
  			//if (KEY_DOWN_NOW(BUTTON_A) && prevPressed != KEY_DOWN_NOW(BUTTON_A)) {
				if (KEY_DOWN_NOW(BUTTON_L)) {
					//reset number of lives before going to the game play
					party = 0;
					myPlayer.height = DEMOCRAT_HEIGHT;
					myPlayer.width = DEMOCRAT_WIDTH;
					myPlayer.image = democrat;
					lives = 3;
  				state = STATE3;
  			}

				if (KEY_DOWN_NOW(BUTTON_R)) {
					party = 1;
					myPlayer.height = REPUBLICAN2_HEIGHT;
					myPlayer.width = REPUBLICAN2_WIDTH;
					myPlayer.image = republican2;
					lives = 3;
					state = STATE3;
				}

				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = START;
				}
  			break;

  		case STATE3:
					//reset screen
					fillScreen(BLACK);
					//return player to original position
					myPlayer.y = 0;
					myPlayer.x = 0;

					//create array of enemies
					if (party == 0) {
						for(int i = 0; i < numEnemy; i++) {
							enemies[i].y = 21 + 19*i;
							enemies[i].x = 10*rand()%500 + 60*rand()%500 - rand()%500;
							enemies[i].height = REPUBLICAN2_HEIGHT;
							enemies[i].width = REPUBLICAN2_WIDTH;
							enemies[i].image = republican2;
						}
					}

					if (party == 1) {
						for(int i = 0; i < numEnemy; i++) {
							enemies[i].y = 21 + 19*i;
							enemies[i].x = 10*rand()%500 + 60*rand()%500 - rand()%500;
							enemies[i].height = DEMOCRAT_HEIGHT;
							enemies[i].width = DEMOCRAT_WIDTH;
							enemies[i].image = democrat;
						}
					}

          state = STATE3_NODRAW;
  				break;

  		case STATE3_NODRAW:
					//draw White House
					drawImage3(0, 160, WHITEHOUSE_WIDTH, WHITEHOUSE_HEIGHT, whitehouse);
					drawRect(0, 159, 160, 1, RED);
					drawRect(0, 158, 160, 1, WHITE);
					drawRect(0, 157, 160, 1, BLUE);
					moveObj(&myPlayer.x, &myPlayer.y, myPlayer.height, myPlayer.width, BLACK);
					drawImage3(myPlayer.x, myPlayer.y, myPlayer.width, myPlayer.height, myPlayer.image);

					for (int i = 0; i < numEnemy; i++) {
						if (detectCollision(myPlayer.x, myPlayer.y, myPlayer.width,
							myPlayer.height, enemies[i].x, enemies[i].y, enemies[i].width, enemies[i].height)) {
								lives--;
								if (lives == 0) {
									state = LOSE;
								}
								else {
									state = STATE3;
								}
							}
					}

					waitForVBlank();
					for (int i = 0; i < numEnemy; i++) {
						drawRect(enemies[i].x, enemies[i].y, enemies[i].height, enemies[i].width, BLACK);
						enemies[i].x = (enemies[i].x + 1)%160;
						drawImage3(enemies[i].x, enemies[i].y, enemies[i].height, enemies[i].width, enemies[i].image);
					}

					//waitForVBlank();
					drawString(150, 5, varBuffer, BLACK);
					sprintf(varBuffer, "Lives remaining: %d", lives);
					drawString(150, 5, varBuffer, BLUE);

					//check if player has won
					if (myPlayer.y + myPlayer.width > 157) {
						state = WIN;
					}

					if (KEY_DOWN_NOW(BUTTON_SELECT)) {
						state = START;
					}
  				break;

				case LOSE:
					if (party == 0) {
						drawImage3(0, 0, TRUMP_WIDTH, TRUMP_HEIGHT, trump);
						buffer = "YOU LOST. PRESS SELECT TO START OVER.";
						drawString(30, 10, buffer, RED);

					}

					if (party == 1) {
						drawImage3(0, 0, PANTSUIT_WIDTH, PANTSUIT_HEIGHT, pantsuit);
						buffer = "YOU LOST. PRESS SELECT TO START OVER.";
						drawString(30, 10, buffer, RED);
					}

					state = LOSE_NODRAW;
					break;

				case LOSE_NODRAW:
					if (KEY_DOWN_NOW(BUTTON_SELECT)) {
						state = START;
					}
					break;

				case WIN:
					if (party == 0) {
						drawImage3(0, 0, PANTSUIT_WIDTH, PANTSUIT_HEIGHT, pantsuit);
					}

					if (party == 1) {
						drawImage3(0, 0, TRUMP_WIDTH, TRUMP_HEIGHT, trump);
					}
					buffer = "YOU WON! PRESS SELECT TO START OVER.";
					drawString(30, 11, buffer, BLUE);
					state = WIN_NODRAW;
					break;

				case WIN_NODRAW:
					if (KEY_DOWN_NOW(BUTTON_SELECT)) {
						state = START;
					}
				 	break;
  		}
  		prevPressed = KEY_DOWN_NOW(BUTTON_A);
    }
    return 0;
}
