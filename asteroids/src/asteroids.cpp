/* Asteroids
    Sample solution for assignment
    Semester 2 -- Small Embedded Systems
    Dr Alun Moon
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

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"
#include "utils.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
int		shields;
struct ship player;
int rockNumber;

float Dt = 0.01f;

//rock_t *asteroids;

const coordinate_t centre = {
		240,136		//centre of screen
};

const coordinate_t vertex[] = {
    {0,-10}, {-10,10}, {10,10}		//coordinates of points of ship in relation to centre
};

//centre
double centreX = centre.x;
double centreY = centre.y;

//top point
double shipAX = centre.x+vertex[0].x;
double shipAY = centre.y+vertex[0].y;

//back left point
double shipBX = centre.x+vertex[1].x;
double shipBY = centre.y+vertex[1].y;

//back right point
double shipCX = centre.x+vertex[2].x;
double shipCY = centre.y+vertex[2].y;

rock_t *asteroids;
missile_t *shots;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);

void initialise() {
	//initialises asteroid linked list
	asteroids = static_cast<rock_t*>(malloc(sizeof(rock_t)));
	asteroids->p.x=0;
	asteroids->p.y=0;
	asteroids->v.x=2;
	asteroids->v.y=2;
	asteroids->next=NULL;
	
	//initialises missile linked list
	shots = static_cast<missile_t*>(malloc(sizeof(missile_t)));
	shots->next=NULL;
}

int main()
{
		//calls method to initialise double buffer
    init_DBuffer();
	
		initialise();
	
    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.1);
	
    lives = 5;		//number of lives
		shields = 3;		//number of shields
	
    while( userbutton.read() ){ /* remember 1 is not pressed */
        paused=true;
        wait_ms(100);	
    }
    paused = false;
		
		/*while(true) {
			if (lives < 1) {
				view.detach();
				model.detach();
				controller.detach();
				gameOver();
			}*/
    
    //while(true) {
        /* do one of */
        /* Wait until all lives have been used
        while(lives>0){
            // possibly do something game related here
            wait_ms(200);
        }
        */
        /* Wait until each life is lost
        while( inPlay ){
            // possibly do something game related here
            wait_ms(200);
        }
        */
}
