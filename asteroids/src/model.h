/* Asteroids Model */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some insitial struct types if you want to usd them */
struct ship {
    coordinate_t p;
    vector_t     v;
};

/* initial struts for building linked lists */
typedef struct rock_t {
    coordinate_t p;
		vector_t v;
    struct rock_t *next;
}rock_t;

typedef struct missile_t {
    coordinate_t p;
		vector_t v;
    struct missile_t *next;
}missile_t;

void physics(void);

void newMissile(missile_t *head);
