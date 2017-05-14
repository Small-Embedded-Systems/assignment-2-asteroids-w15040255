/* Game state */

extern float elapsed_time; /* time this ship has been active */
extern int   score;        /* total score so far */
extern int   lives;        /* lives remaining */
extern int	 shields;

extern int rockNumber;

extern double centreX;
extern double centreY;

extern double shipAX;
extern double shipAY;
extern double shipBX;
extern double shipBY;
extern double shipCX;
extern double shipCY;

//extern struct coordinate_t centre;
//extern struct coordinate_t vertex[];

//instead of declaring centreX as centre.x, make centre.x extern

extern struct ship player;

extern struct rock_t *asteroids; /* array of rocks / pointer to linked-list */
extern struct missile_t *shots;  /* array of missiles / pointer to linked-list */

extern const float Dt; /* Time step for physics, needed for consistent motion */
