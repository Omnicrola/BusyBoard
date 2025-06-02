// **********
//  Sasquatch!
// **********

// this effect displays only once per switch toggle
bool displayedOnce = false;

// called once by main setup
void setupSquatchMode() {
  // nothing to setup
}

// called from main loop when switch is enabled
void runSquatchMode() {

  if(!displayedOnce) {
    drawIndexedBitmap(32, 0, squatchFoot);
    delay(2000);
    drawIndexedBitmap(0, 0, squatchFoot);
    delay(2000);

    displayedOnce = true;
  }
}

void clearSquatchMode() {
  displayedOnce = false;
}