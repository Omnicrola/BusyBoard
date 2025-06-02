// **********
//  Rockets!
// **********

// How fast the rocket moves. Because of the complexities of consistently 
// aligning the bitmap on an LED strip wired in serpentine, this 
// should be a multiple of 2
const int ROCKET_SPEED = 2;

// this determines how far from the right side to draw the rocket
int rocketOffset = 0;
// called from main loop when switch is enabled
void launchRocket() {

  // draw the bitmap, with an increasing offset from the right side of the display
  drawIndexedBitmap(0-rocketOffset, 0, rocketBitmap);

  // increment, and reset if necessary
  rocketOffset = rocketOffset + ROCKET_SPEED;
  if(rocketOffset > 64){
    rocketOffset = -64;
  }
  delay(25);
}

// make sure the next time the switch is on, we start at the beginning
void clearRocket() {
  rocketOffset = -64;
}
