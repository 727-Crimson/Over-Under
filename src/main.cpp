/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Engineering                                      */
/*    Created:      Mon Jun 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// TopRight             motor         10              
// BottomLeft           motor         13              
// TopLeft              motor         2               
// BottomRight          motor         20              
// Controller1          controller                    
// flyWheelTop          motor         3               
// flyWheelBottom       motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void driv(int pct1){
  TopRight.spin(forward, pct1, vex::velocityUnits::pct);
  BottomRight.spin(forward, pct1, vex::velocityUnits::pct);
  TopLeft.spin(forward, pct1, vex::velocityUnits::pct);
  BottomLeft.spin(forward, pct1, vex::velocityUnits::pct);
}

void stahp(){
  TopRight.stop();
  BottomRight.stop();
  TopLeft.stop();
  BottomLeft.stop();
}

void flyWheel(){
  if(Controller1.ButtonL1.pressing()){
    flyWheelTop.spin(forward);
    flyWheelBottom.spin(forward);
    wait(0.5, seconds);
  } else{
    flyWheelTop.stop();
    flyWheelBottom.stop();
  }
}

void moveForSec(int secs){
  driv(50);
  wait(secs, sec);
  stahp();

}

void driveToTarget(int degrees, int sped) {
  int current1 = TopRight.position(deg);
  int target = current1 + degrees;
  double error = target - current1;
  while(error > 5){
    current1 = TopRight.position(deg);
    error = target - current1;
    driv(sped);
  }
  stahp();
}

int slew(int target, int current, int slew_step) {
  if (target > current + slew_step) {
    return current + slew_step;
  } else if(target < current - slew_step) {
    return current - slew_step;
  }
  
  return target;
}

void stoneSlewDrive(int target, int current, int slew1) {
  int err = 0;
  if (current > target) {
    err = current - target;
  } else if (target >= current) {
    err = target - current;
  }
  int rem = err%slew1;
  int slewTimes = (err-rem)/slew1;
  for (int i=0; i<slewTimes, i++;) {
    driv(slew(target, current, slew1));
    wait(10, msec);
  }
  int finalSlew = 0;
  if (current > target) {
    finalSlew = current - (slewTimes * slew1);
  } else if (target >= current) {
    finalSlew = current + (slewTimes * slew1);
  }
  slew(target, finalSlew, rem);
}



int main() {
  int currentSpeedL=0;
  int currentSpeedR=0;
  flyWheelBottom.setVelocity(100, percent);
  flyWheelTop.setVelocity(100, percent);
  vexcodeInit();
   while(true){
     int targetSpeedL=Controller1.Axis1.value() - Controller1.Axis3.value();
     int targetSpeedR=Controller1.Axis1.value() + Controller1.Axis3.value();
     currentSpeedL=slew(currentSpeedL, targetSpeedL, 30);
     currentSpeedR=slew(currentSpeedR, targetSpeedR, 30);

     TopRight.spin(forward, targetSpeedR, vex::velocityUnits::pct);
     BottomRight.spin(forward, targetSpeedR, vex::velocityUnits::pct);
     TopLeft.spin(forward, targetSpeedL, vex::velocityUnits::pct);
     BottomLeft.spin(forward, targetSpeedL, vex::velocityUnits::pct);

    flyWheel();
   } 
}
