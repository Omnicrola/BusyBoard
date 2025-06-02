unsigned long debug_previousMillis = 0;
int debug_currentLedState = LOW; 


void blinkDebugLed(){
  unsigned long currentMillis = millis();

  if (currentMillis - debug_previousMillis >= DEBUG_BLINK_INTERVAL) {
    debug_previousMillis = currentMillis;

    if (debug_currentLedState == LOW) {
      debug_currentLedState = HIGH;
    } else {
      debug_currentLedState = LOW;
    }

    digitalWrite(TEST_PIN_OUT, debug_currentLedState);
  }
}

void debugSetLedState(int newState) {
  if(newState != debug_currentLedState){
    debug_currentLedState = newState;
    digitalWrite(TEST_PIN_OUT, debug_currentLedState);
  }
}