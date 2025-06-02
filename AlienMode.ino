// **********
//  Aliens!
// **********

// CONSTANTS
uint8_t alienGradient[] {8,16,32,64,128,255,255,128,64,32,16,8}; // fibbonaci seems to make the most pleasing visual gradient
const int GRADIENT_SIZE = 12;
const int ALIEN_SPEED = DISPLAY_ROWS * 1; // how fast the gradient moves
const int ALIEN_FLIP_DISTANCE = (GRADIENT_SIZE / -2) * DISPLAY_ROWS; // half the width of the gradient, times the display height

// VARS
int alienOffset = 0; // current offset 
bool forwardDirection = true; // used to make the animation "bounce" and reverse direction

// SETUP
void setupAlienMode(){
  // aliens are mysterious, and apparently are always ready
}

// TICK
void runAlienMode(){

  // increment or decrement position
  if(forwardDirection) {
    alienOffset += ALIEN_SPEED;
  } else {
    alienOffset -= ALIEN_SPEED;
  }
  
  // decide if we should reverse direction
  if(alienOffset > DISPLAY_SIZE) {
    forwardDirection = false;
  } else if(alienOffset < ALIEN_FLIP_DISTANCE) {
    forwardDirection = true;
  }
  
  drawAlienPulse();
}

void drawAlienPulse() {

  int gradientIndex = 0;
  int columnIndex = 0;

  if(alienOffset < 0) {
    // if the offset is less than zero (off the side of the display)
    // then just skip those parts of the gradient that aren't actually displayed
    gradientIndex = alienOffset / -DISPLAY_ROWS;
  }

  // disable interrupts
  cli();

  // loop over the entire display pixel by pixel, using the gradient array to determine
  // the intensity of each column, and writing black to the rest of the pixels
  for(int i=0; i < DISPLAY_SIZE; i++) {
    if(i > alienOffset && gradientIndex < GRADIENT_SIZE) {
      // is it green? so green. supergreen.
      sendPixel(0, alienGradient[gradientIndex], 0);
      columnIndex++;
      if(columnIndex > DISPLAY_SIZE) {
        columnIndex = 0;
        gradientIndex++;
      }
    } else {
      sendPixel(0,0,0);
    }
  }

  // resume interrupts
  sei();
  // delay to allow pixel latch
  show();

}

void clearAlienMode(){
  // nothing to reset, the gradient can resume moving where ever it stopped
}