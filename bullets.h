// bullets.h
#ifndef BULLETS_HEADER
#define BULLETS_HEADER

void bullets_init();

void bullets_update();

void bullets_draw();

// Spawn a bullet at x, y.
// Default bullet speed will bu multiplied by xmult and ymult in both
// x and y directions. To make a bullet go horizontally, for example, pass 0 for ymult.
void bullets_spawn(double x, double y, double xmult, double ymult);
#endif
