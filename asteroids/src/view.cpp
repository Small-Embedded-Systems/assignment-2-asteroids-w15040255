/* Asteroids view
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"

#include "objects.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(0,51,102); /* Midnight Blue */

/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}

void DrawPlayingArea() {
		graphics->drawLine(0,26, 480,26, WHITE);	//LCD=480x272 pixels
}

void DrawTime() {		//display time
		graphics->setTextSize(2);
		graphics->setCursor(380,6);
		graphics->printf("TIME: %.0f",elapsed_time);
}

void DrawScore() {	//display score
		graphics->setTextSize(2);
		graphics->setCursor(215,6);
		graphics->printf("SCORE: %d",score);
}

void DrawLives() {	//display lives
		graphics->setTextSize(2);
		graphics->setCursor(4,6);
		graphics->printf("LIVES: ");
		for(int i=1; i<=lives; i++) {
			graphics->drawLine((i*22)+65,2, ((i*22)+65)-10,22, WHITE);
			graphics->drawLine((i*22)+65,2, ((i*22)+65)+10,22, WHITE);	
			graphics->drawLine(((i*22)+65)-10,22, (i*22)+65,12, WHITE);
			graphics->drawLine(((i*22)+65)+10,22, (i*22)+65,12, WHITE);
		}
}

void DrawShip() {		//draw ship
		graphics->drawLine(shipAX,shipAY, shipBX,shipBY, WHITE);			//front left line
		graphics->drawLine(shipAX,shipAY, shipCX,shipCY, WHITE);			//front right line
		graphics->drawLine(shipBX,shipBY, centreX,centreY, WHITE);		//back left line
		graphics->drawLine(shipCX,shipCY, centreX,centreY, WHITE);		//back right line
		//wraps ship around screen
		if (shipAX>500 && shipBX>480 && shipCX>480) {
				shipAX = 0;
				centreX = shipAX-10;
				shipBX = centreX-10;
				shipCX = centreX-10;
		} else if (shipAX<-10 && shipBX<0 && shipCX<0) {
				shipAX = 480;
				centreX = shipAX+10;
				shipBX = centreX+10;
				shipCX = centreX+10;
		}
		if (shipAY>272 && shipBY>272 && shipCY>272) {
				shipAY = 36;
				centreY = shipAY-10;
				shipBY = centreY-10;
				shipCY = centreY-10;
		} else if (shipAY<26 && shipBY<26 && shipCY<26) {
				shipAY = 272;
				centreY = shipAY+10;
				shipBY = centreY+10;
				shipCY = centreY+10;
		}
}

void DrawShields (rock_t* head) {
		rock_t* current = head;
		//draw shields
		for(int i=1; i<=shields; i++) {
				graphics->drawCircle(centreX, centreY, 15 + (i*3), WHITE);
		}
		//reposition asteroid when collision with ship occurs and decrementation of shields
		if (current->p.x+16 > (centreX-10) && current->p.x+0 < (centreX+10) && current->p.y+16 > (centreY-10) && current->p.y+0  < (centreY+10)) {
			current->p.x = randrange(-10, 490);
			current->p.y = randrange(-10, 282);
			shields--;
			//if no shields remain, decrement lives
			if (shields < 1) {
				score += elapsed_time;
				elapsed_time = 0;
				lives--;
			}
		}
}

void DrawAsteroid (rock_t *head) {
		rock_t* current = head;
		while (current != NULL) {
			//draw asteroid from bitmap
			graphics->drawBitmap(current->p.x, current->p.y, Asteroid, 16,16, WHITE);
			current = current->next;
		}
}

void DrawMissile(missile_t *head) {
			missile_t* current = head;
			while (current != NULL) {
				//draw missile
				graphics->fillCircle(current->p.x, current->p.y, 3, RED);
				current = current->next;
			}
}

void gameOver() {
		swap_DBuffer();
		graphics->fillScreen(BLACK);
		graphics->setTextSize(5);
		graphics->setCursor(110,60);
		graphics->printf("GAME OVER");
		graphics->setCursor(110,150);
		graphics->printf("SCORE: %d",score);
		init_DBuffer();
}

void incrementTime() {		//counts up
	elapsed_time += 0.025;
	if (lives < 1) {
		elapsed_time = 0;
	}
}

void draw(void)
{
		graphics->fillScreen(background);
		
		DrawPlayingArea();
		DrawTime();
		DrawScore();
    DrawLives();
		DrawShip();
		DrawShields(asteroids);
		DrawMissile(shots);
		DrawAsteroid(asteroids);
		incrementTime();
		
		//when no lives remain game over
		while (lives<1) {
			gameOver();
		}
	
    swap_DBuffer();
}
