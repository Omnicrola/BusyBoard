  #include <Adafruit_GFX.h>
  #include <Adafruit_NeoMatrix.h>
  #include <Adafruit_NeoPixel.h>

// I/O PIN ASSIGNMENTS
const int ALIEN_INPUT = 12;
const int SQUATCH_INPUT = 10;
const int ROCKET_INPUT = 13;
const int THROTTLE_IN = A5;
const int THROTTLE_OUT = 9;

// this PIN value is now hardcoded in "NeopixelDirect.ino", but kept here for reference
// const int DISPLAY_OUTPUT_PIN =  11;
const int DISPLAY_SIZE = 512;
const int DISPLAY_COLS = 64;
const int DISPLAY_ROWS = 8;

// debugging
const int TEST_PIN_OUT = 7;
const long DEBUG_BLINK_INTERVAL = 200;


// main setup
void setup() {
  Serial.begin(9600);
  pinMode(ROCKET_INPUT, INPUT_PULLUP);
  pinMode(ALIEN_INPUT, INPUT_PULLUP);
  pinMode(SQUATCH_INPUT, INPUT_PULLUP);
  pinMode(TEST_PIN_OUT, OUTPUT);
  
  // setup the LED output pin
  ledsetup();  

  // secondary setups in other INO files
  throttleSetup();
  setupAlienMode();
  setupSquatchMode();
}

// main loop
void loop() {
  // This is here in case framerates needed to be normalized. 
  // Instead I've just used delays because I'm lazy and 
  // this really doesn't need to actually be threaded like a game engine
  // ------
  // float deltaTime = getDeltaTime();
 
  // get physical switch states
  int rocketState = digitalRead(ROCKET_INPUT);
  int alienState = digitalRead(ALIEN_INPUT);
  int squatchState = digitalRead(SQUATCH_INPUT);

  // In priority order, determine if we should trigger a specific
  // graphic on the main display, or clear the display and do nothing.
  // Functions here are in other INO files
  if(rocketState){
    launchRocket();

  } else if(squatchState){
    runAlienMode();

  } else if(alienState){
    runSquatchMode();

  } else {
    clearRocket();
    clearSquatchMode();
    clearAlienMode();
    showColor(0,0,0);
  }

  // always update the throttle meter, separate from the main display
  throttleLoop();

}

