/*
  This file houses the byte arrays that encode the bitmaps to draw on the main display, as well as the function
  that decodes and writes them to the display.

  Each byte in the bitmaps below encodes a color index (0-15) in the low nibble, and a repetition count (max of 16) in the high nibble.
  This enables some very basic compression to save memory, as well as being extremely fast to decode, to allow the data to be sent
  directly out of the pin connected to the Neopixel strip instead of frame-buffered using the standard Neopixel matrix library.

*/

const uint8_t rocketBitmap[] {
  0,149,48,17,128,17,80,49,96,49,48,81,64,81,32,87,64,87,32,70,23,64,22,71,32,71,22,64,22,71,32,70,23,64,87,32,23,22,39,22,64,22,23,22,23,22,32,22,23,22,23,22,64,23,22,39,22,32,87,64,54,39,32,23,38,39,64,39,22,23,22,32,23,38,39,64,54,39,32,87,64,17,55,17,16,33,55,33,32,49,23,97,23,49,32,33,21,22,21,49,24,21,22,21,24,17,32,17,24,21,22,21,24,17,16,24,53,24,64,40,21,40,32,40,21,40,80,56,80,24,96,21,16,24,16,21,208,21,240,240,240,240,240,240,240,240,240,240,240,240,240
};

const uint8_t squatchBitmap[] {
0,83,16,224,32,224,32,224,32,224,32,224,18,20,224,20,16,224,32,224,32,224,32,224,16,240,32,48,51,18,20,83,16,32,16,67,36,34,19,64,32,48,35,144,32,96,98,32,32,34,20,35,18,20,51,16,19,34,32,20,195,20,32,36,19,16,51,36,35,36,16,32,32,68,18,20,18,80,32,96,20,112,32,224,16
};

const uint8_t squatchFoot[] {
  0,153,208,34,32,34,16,34,48,18,128,66,16,18,16,50,35,18,32,18,51,66,83,18,48,83,98,112,82,35,18,112,18,51,34,51,18,112,50,240,240,34,32,34,16,34,48,18,128,66,16,18,16,50,35,18,32,18,51,66,83,18,48,83,98,112,82,35,18,112,18,51,34,51,18,112,50,224,34,32,34,16,34,48,18,128,66,16,18,16,50,35,18,32,18,51,66,83,18,48,83,98,112,82,35,18,112,18,51,34,51,18,112,50,240,48,34,112,34,16,34,112,18,16,18,16,66,48,18,35,50,16,50,51,18,32,18,83,34,83,80,146,128,18,35,34,51,18,96,18,51,18,16,50,192
};

// custom index color pallate
const uint8_t COLOR_MAP[][3] = {
  { 0, 0, 0 },        // 0 B - black
  { 0, 0, 255 },      // 1 C - blue
  { 173, 100, 23 },   // 2 D - dark brown
  { 250, 197, 79 },   // 3 L - light brown
  { 196, 135, 0 },    // 4 M - medium brown
  { 255, 90, 0 },     // 5 O - orange
  { 255, 0, 0 },      // 6 R - red
  { 255, 255, 255 },  // 7 W - white
  { 255, 255, 0 },    // 8 Y - yellow
  { 0, 255, 0},       // 9 G - green
};


/*
Draw a color-indexed bitmap using the Neopixel Direct functions

   One of the tradeoffs of writing to the LED array this way (instead of the Neopixel Matrix library) is that each 
   bitmap must describe a value for (almost) every single pixel, even if the overall bitmap is smaller than the 
   display grid itself. This function will write black(0,0,0) to any remaining pixels in the display if the
   uncompressed bitmap data ends up shorter than the display.

*/ 
uint8_t colorIndex, pixelCount, r, g, b = 0;
void drawIndexedBitmap(int xStart, int yStart, uint8_t compressedBitmap[]) {

  // get the size of the bitmap
  uint8_t highByte = compressedBitmap[0];
  uint8_t lowByte = compressedBitmap[1];
  uint16_t bitmapSize = (uint16_t)highByte << 8 | (uint16_t)lowByte;

  int skipCount = 0;
  int startingOffset = 0;
  int pixelsDrawn = 0;

  // disable interrupts
  cli();

  // skip forward (draw blank pixels) based on the start position
  if(xStart > 0) {
    for(int i=0; i<xStart*DISPLAY_ROWS; i++) {
      sendPixel(0,0,0);
    }
  } else {
    // this sets how many pixels to skip over, so it appears the image is drawn partially "off" (to the left) of the display
    startingOffset = xStart * DISPLAY_ROWS * -1;
  }

  for(int i=2; i < bitmapSize+2; i++) {
    // get the next color and how many times it's repeated
    pixelCount = (compressedBitmap[i] >> 4) & 0x0F;
    colorIndex = compressedBitmap[i] & 0x0F;
    r = COLOR_MAP[colorIndex][0] /16;
    g = COLOR_MAP[colorIndex][1] /16;
    b = COLOR_MAP[colorIndex][2] /16;

    // set a sequential number of pixels the same color
    for(int p=0; p<pixelCount; p++){
      if(skipCount < startingOffset) {
        // do nothing and increment
        skipCount++;
      } else {
        pixelsDrawn++;
        sendPixel(r,g,b);
      }
    }
  }


  // clear off the rest of the pixels we didn't have any data for (either because the bitmap
  // is smaller than the display, or we shifted the image off the left side of the display)
  for(int i=0; i<DISPLAY_SIZE - pixelsDrawn; i++){
        sendPixel(0,0,0);
  }


  // resume interrupts
  sei();
  // delay to allow latch
  show();
}
