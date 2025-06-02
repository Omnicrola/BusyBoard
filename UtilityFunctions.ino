unsigned long lastLoopTime = 0;

// calculate elapsed time since the last loop() as a fraction of 1 second
float getDeltaTime() {
  unsigned long currentTime = millis();
  unsigned long timeElapsed = currentTime - lastLoopTime;
  float delta = timeElapsed / 1000.0;
  lastLoopTime = currentTime;
  return delta;
}