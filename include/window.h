#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d; // Pointer to X Display structure; "holds all the information (screen, keyboard, mouse, etc.) about the display"
  Window w; // Window ID (handle) for the window
  int s; // Screen number
  GC gc; // "Graphics Context" used for drawing
  unsigned long colours[10]; // Colours array

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  // enum {White=0, Black, Red, Green, Blue}; // Available colours.
  enum {White=0, Black, Red, Khaki, DarkOliveGreen, Transparent, Gray, LightCoral, FireBrick, LightSteelBlue3, Moccasin};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Draws the title of the board
  void drawTitle();

  // Code for loading up custom fonts was taken from:
  // https://github.com/QMonkey/Xlib-demo/blob/master/src/load_font.c
  void setFont(const char * fontname);

  // Draws a BitMap
  // Documentation used from:
  // https://tronche.com/gui/x/xlib/graphics/XGetImage.html
  void drawBitMap(int cellDim, int x, int y, const int bitmap[80][80], int cellColour);

};

enum colors {White=0, Black, Red, Khaki, DarkOliveGreen, Transparent, Gray, LightCoral, FireBrick, LightSteelBlue3, Moccasin};

#endif
