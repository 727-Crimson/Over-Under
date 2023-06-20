using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor TopRight;
extern motor BottomLeft;
extern motor TopLeft;
extern motor BottomRight;
extern controller Controller1;
extern motor flyWheelTop;
extern motor flyWheelBottom;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );