#ifndef CELLS_H
#define CELLS_H

#define SET_X(ptr,n) ((ptr)->attr1 = ((ptr)->attr1 & ~(0x1FF)) | (n));
#define SET_Y(ptr,n) ((ptr)->attr0 = ((ptr)->attr0 & ~(0x1FF)) | (n));
#define GRAB_X(ptr) (((ptr)->attr1) & (0x1FF))
#define GRAB_Y(ptr) (((ptr)->attr0) & (0x1FF))

int obj_cnt;

typedef enum {RED, GRAY, PINK, SMALL_PINK, BLUE} TYPE;
typedef enum {ALIVE, DEAD} STATUS;
typedef enum {TRACK, NONE} ATTACK_TYPE;


/*
    @member TYPE: information of cell type
    @member STATUS: wether the cell is dead or not
    @member ATTACK_TYPE: the attack type
    @member health_pool: how many bullets it takes to kill cell
    @member health: currently how many bullets it takes to kill cell
    @member vector: direction and speed cell is traveling. This
                    field is not used for player, gray, and blue
                    cells.
 */
typedef struct {
    TYPE type;
    STATUS status;
    ATTACK_TYPE attack;
    OamEntry *OAM_ptr;

    int health_pool;
    int health;

    int vecx;
    int vecy;
} cell;

void spawn();
void chase(OamEntry *self, OamEntry *target);
cell create_cell(TYPE type, int x, int y);
void clear_OAM();
int update();

#endif