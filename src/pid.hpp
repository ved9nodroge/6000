#ifndef PID_H
#define PID_H
#include <stdbool.h>
#include "Point.hpp"

class Slew_t {
   public:
    double slewRate, output;
    int prevTime;
    Slew_t();
    double update(double in);
};
class Pid_t {
   public:
    double unwind, DONE_ZONE, maxIntegral, iActiveZone, dInactiveZone, target, sensVal, prevSensVal, prevErr, errTot, kp, ki, kd, deriv, prop, derivativeUpdateInterval;
    int prevTime, doneTime, prevDUpdateTime;
    Pid_t();
    double update();
};
class Odometry_t {
   private:
    double x, y, a, L, prevDL, prevDR;

   public:
    void update();
    Odometry_t(double L);
    double getX();
    double getY();
    double getA();
    void setA(double a);
    void setX(double x);
    void setY(double y);
    Point getPos();
};

void pidDriveInit(Point target, const int wait);
bool pidDrive();
void pidDriveLineInit(Point start, Point target, const int wait);
bool pidDriveLine();
void pidTurnInit(const double angle, const int wait);
bool pidTurn();
bool pidTurnSweep(double tL, double tR, int wait);
void pidDriveArcInit(Point start, Point target, double rMag, int rotationDir, int wait);
void pidFollowArcInit(Point start, Point target, double rMag, int rotationDir, int wait);
bool pidDriveArc();
void pidDriveArcBias(int b);
void printArcData();

extern Pid_t clawPid, drfbPid, DLPid, DRPid, drivePid, turnPid, curvePid;
extern Slew_t flywheelSlew, drfbSlew, DLSlew, DRSlew, clawSlew;
extern Odometry_t odometry;
extern int g_pidTurnLimit;

#endif