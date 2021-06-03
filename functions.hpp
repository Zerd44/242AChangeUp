#include "okapi/api.hpp"
using namespace okapi;

// extern void master();

extern int overCount;

extern void intake();
extern void index();

extern void turn(int speed, char direction, double deg);
extern void turnOver(int speed, char direction, double deg);
extern void brake(char braketype);

extern void autontest();

extern void setDrive(int left, int right);

extern void rotate(double angle, int number);

extern void calibrate();
