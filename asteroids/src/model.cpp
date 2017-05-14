/* Asteroids model */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"
#include "controller.h"

double AX, AY, BX, BY, CX, CY;
double  hypotenuse = 10;
float angle = 0.0;
float angle_stepsize = 0.5;

void spinShipLeft() {
		//rotate ship
		angle -= angle_stepsize;
	
		//new ship point coordinates
		AX = hypotenuse * cos(angle);
		AY = hypotenuse * sin(angle);
		BX = hypotenuse * cos(angle+2.44346);
		BY = hypotenuse * sin(angle+2.44346);
		CX = hypotenuse * cos(angle+3.83972);
		CY = hypotenuse * sin(angle+3.83972);
	
		//set ship to new coordinates
		shipAX = centreX + AX;
		shipAY = centreY + AY;
		shipBX = centreX + BX;
		shipBY = centreY + BY;
		shipCX = centreX + CX; 
		shipCY = centreY + CY;
		
		leftPress = false;
}

void spinShipRight() {
		//rotate ship
		angle += angle_stepsize;
	
		//new ship point coordinates
		AX = hypotenuse * cos(angle);
		AY = hypotenuse * sin(angle);
		BX = hypotenuse * cos(angle+2.44346);
		BY = hypotenuse * sin(angle+2.44346);
		CX = hypotenuse * cos(angle+3.83972);
		CY = hypotenuse * sin(angle+3.83972);
	
		//set ship to new coordinates
		shipAX = centreX + AX;
		shipAY = centreY + AY;
		shipBX = centreX + BX;
		shipBY = centreY + BY;
		shipCX = centreX + CX; 
		shipCY = centreY + CY;
	
		rightPress = false;
}

void accelerateShip() {
		//x and y velocity
		float vX = 0.1*(hypotenuse * cos (angle));
		float vY = 0.1*(hypotenuse * sin (angle));
	
		//move ship
		centreX += vX;
		centreY += vY;
		shipAX += vX;
		shipAY += vY;
		shipBX += vX;
		shipBY += vY;
		shipCX += vX;
		shipCY += vY;
}

void decelerateShip() {
		//x and y velocity
		float vX = 0.05*(hypotenuse * cos (angle));
		float vY = 0.05*(hypotenuse * sin (angle));

		//move ship
		centreX -= vX;
    centreY -= vY;
		shipAX -= vX;
		shipAY -= vY;
		shipBX -= vX;
		shipBY -= vY;
		shipCX -= vX;
		shipCY -= vY;
}

void newRock(rock_t* head) {
		if (rockNumber < 4) {
			rock_t* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = (rock_t*)malloc(sizeof(rock_t));
			current->next->p.x = randrange(-10, 480);				//spawn random X coordinate within range 
			current->next->p.y = randrange(-10, 282);				//spawn random Y coordinate within range 
			current->next->v.x = randrange(-1, 2);					//set random X velocity within range
			current->next->v.y = randrange(-1, 2);					//set random Y velocity within range
			if (current->next->v.x == 0 || current->next->v.y == 0) {		//if asteroid has no velocity in X or Y plane
				current->next->v.x = randrange(-1, 2);
				current->next->v.y = randrange(-1, 2);
			}
			current->next->next = NULL;
			rockNumber++;
		}
}

void moveRock(rock_t* head) {
	rock_t* current = head;
		if (current !=NULL) {
		//add velocity to coordinate, move ship
				current->p.x += current->v.x;
				current->p.y += current->v.y;
			
				//wrap asteroids around screen
				if (current->p.x>485) {current->p.x = -5;}
				if (current->p.x<-5) {current->p.x = 485;}
				if (current->p.y>277) {current->p.y = -5;}
				if (current->p.y<-5) {current->p.y = 277;}
				
				current = current->next;
				moveRock(current);
		}
}

void fireMissile(missile_t* head) {
	missile_t* current = head;
		while (current !=NULL) {
		//add velocity to missile, move missile
				current->p.x += current->v.x;
				current->p.y += current->v.y;
				
				current = current->next;
		}
}

void newMissile(missile_t* head) {
		missile_t* current = head;
	
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = (missile_t*)malloc(sizeof(missile_t));
		
		current->next->p.x = shipAX;		//set missile firing position
		current->next->p.y = shipAY;		//set missile firing position
		current->next->v.x = 0.5*(hypotenuse * cos (angle));			//set missile velocity
		current->next->v.y = 0.5*(hypotenuse * sin (angle));			//set missile velocity
	
		current->next->next = NULL;
}

void physics(void)
{
		newRock(asteroids);
		moveRock(asteroids);
	
		if (leftPress == true) {
				spinShipLeft();
		}
		if (rightPress == true) {
				spinShipRight();
		}
		if (upPress == true) {
				accelerateShip();
		}
		if (downPress == true) {
				decelerateShip();
		}
		
		fireMissile(shots);
}
