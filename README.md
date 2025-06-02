# BusyBoard

## Project Summary
This is an Arduino project I wrote to drive a busyboard for a toddler, which got real extra real fast. It uses a set of 4 toggle switches to drive behavior of 64x8 WS2812 LED display matrix. It also has a throttle control!

TBD : Add pictures of finished project and circuit diagrams

## Technical Highlights
The overall code is very straightforward, with simple logic controlling when to display certain images on the display.

The way the bitmaps are encoded and displayed is not standard. The standard NeoPixel Matrix library reserves memory based on the size of
your NeoPixel strip (512 pixels in this project). At ~3bytes per pixel, thats ~1500bytes and the Arduino Uno 3 only has 2000. This makes using
the standard library infeasible. Additionally I wanted to store the bitmaps in memory to allow for quick changes. The final requirement was to 
be able to quickly and easily take a pixel pattern from Google Sheets and transcode it for use on the Arduino. 

The solution I came up with is a very simplistic encoding scheme. 

### Encoding
The `neopixel_color_converter.html` file is a standalone encoder that will take a tab-delimited string of letters from a Google Sheet and encode it. The encoder reads the input, transfoms it to match the serpentine layout of the LED matrix, and then encodes it by counting when indexed color repeats (up to a maximum of 15 times). In the last step, the encoder stores the total length of the array for ease of use. The output string is then copied into the `Bitmaps.INO` file as a `uint8_t` array.

### Decoding
When a bitmap is drawn, the decoder loops over each `uint8_t` and uses the high nibble to determine the color index, and the low nibble to determine how many times to repeat it before moving to the next element in the bitmap.

## Color Indexes
The colors selected to be used are simply the ones that were needed to draw simple images, and I didn't even use all 16 available indices.  I briefly toyed with the idea of encoding a color map into the beginning of each bitmap array, but decided not to since the total number of colors across all the bitmaps I needed was so small.


## Attribution
The code for writing directly to the Neopixel array was taken from 
https://github.com/bigjosh/SimpleNeoPixelDemo
Which has a detailed blog entry here:
https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
