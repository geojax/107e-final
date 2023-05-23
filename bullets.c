#include "bullets.h"
struct bullet {
    double x;
    double y;
    double dx;
    double dy;
};
#define MAX_BULLETS 64

// a ring buffer of bullets.
// only the bullets on screen need to be updated.
static struct bullet bullets[MAX_BULLETS];

static void destroy_bullet();

void bullets_spawn(double x, double y, double xmult, double ymult)
{
    
}
