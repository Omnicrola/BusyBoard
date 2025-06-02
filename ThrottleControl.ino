// **********
//  Throttle LED display !
// **********

// total LEDs on the throttle "meter"
const int THROTTLE_LED_COUNT = 15;

// approximate upper and lower bounds of the range the cable can move the linear potentiometer
const int THROTTLE_MIN = 450;
const int THROTTLE_MAX = 720;

// what indexed color to "draw" on the throttle, based on it's current level (15 levels)
const uint8_t throttleMap[] {6, 6, 6, 6, 5, 5, 5, 5, 8, 8, 8, 8, 8, 9, 9, 9};

// using the standard NeoPixel library here, since it's easier and the memory use is not as high as the main display
Adafruit_NeoPixel throttlePixels = Adafruit_NeoPixel(14, THROTTLE_OUT, NEO_GRB + NEO_KHZ800);

// called once from the main setup
void throttleSetup() {
  throttlePixels.begin();
}

void throttleLoop() {
  // current value of the linear potentiometer
  int throttleValue = analogRead(THROTTLE_IN);

  // remap the analog value into a range of 0-15;
  int throttleLevel = map(throttleValue, THROTTLE_MIN, THROTTLE_MAX, 0, 15);
  throttleLevel = constrain(throttleLevel, 0, THROTTLE_LED_COUNT);

  // get the indexed color and display it on all pixels
  uint8_t r = COLOR_MAP[throttleLevel][0] /4;
  uint8_t g = COLOR_MAP[throttleLevel][1] /4;
  uint8_t b = COLOR_MAP[throttleLevel][2] /4;

  throttlePixels.clear();
  for(int i=0; i < throttleLevel; i++){
    throttlePixels.setPixelColor(i, throttlePixels.Color(r,g,b));
  }
  throttlePixels.show();
  
}