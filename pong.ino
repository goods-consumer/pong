#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"

// initialize matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 1,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB + NEO_KHZ800);
// initial x- and y-coordinates of the ball
int xPos = 1;
int yPos = 0;
// initial x- and y-directions of the ball
int xDir = 1;
int yDir = -1; 
// determines how the ball bounces
int bounce = 1;  

// moves and draws the ball
void updateBall() {
  draw(xPos, yPos, off);
  xPos += xDir;
  yPos -= (yDir * bounce);
  if (xPos == 1 || xPos == 6) {  // when the ball reaches a paddle
    xDir *= -1;
    bounce = random(2);
  } 
  if (bounce != 0 && (yPos == 0 || yPos == 7)) {  // when the ball reaches the top or bottom
    yDir *= -1;
  }
  draw(xPos, yPos, white);
}

// moves and draws the paddles
void updatePaddles() {
  RGB color;
  for (int row = 0; row < 8; row++) { 
    if (row >= yPos - 1 && row <= yPos + 1 ||               
                     yPos == 0 && row == 2 ||   // cannot draw at indices -1 and 8, 
                     yPos == 7 && row == 5) {   // instead draw at 2 and 5 respectively 
      color = white;
    } else {
      color = off;
    } 
    draw(0, row, color);
    draw(7, row, color);
  }
}

// draws a pixel of the specified color at the specified coordinates
void draw(int x, int y, RGB color) {
  matrix.drawPixel(x, y, matrix.Color(color.r, color.g, color.b));
}

// runs at start to initialize the matrix
void setup() {
  matrix.begin();
  matrix.setBrightness(5);
}

// runs repeatedly and controls the program
void loop() {
  updateBall();
  updatePaddles();
  matrix.show();
  delay(60);
}

