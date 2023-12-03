#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include "window.h"
#include "piece.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  // https://en.wikipedia.org/wiki/X11_color_names#Color_name_chart
  // https://www.w3schools.com/colors/colors_x11.asp

  vector<string> color_vals {
    "white",
    "black",
    "red",
    "khaki",
    "darkolivegreen",
    "transparent",
    "gray"
  };

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(size_t i=0; i < color_vals.size(); ++i) {
      XParseColor(d,cmap,color_vals[i].c_str(),&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,Xwindow::Black);

  setFont("lucidasans-bold-18");

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  XStoreName(d, w, "Chess - Rehan Anjum, Ali Syed, Kush Patel");

  usleep(1000);

  // XLoadFont(d, "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1")
  // XLoadFont(d, "-misc-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1");

  XEvent ev;
  while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::setFont(const char * fontname) {
  // Code for loading up custom fonts was taken from:
  // https://github.com/QMonkey/Xlib-demo/blob/master/src/load_font.c
  XFontStruct * font;
  font = XLoadQueryFont (d, fontname);
  if (! font) {
      fprintf (stderr, "unable to load font %s: using fixed\n", fontname);
      font = XLoadQueryFont (d, "fixed");
  }
  XSetFont (d, DefaultGC(d, s), font->fid);
}

void Xwindow::drawTitle() {

  setFont("lucidasans-bold-24");
  // XLoadFont(d, "-misc-seravek-medium-r-normal--0-0-0-0-p-0-iso10646-1");
  string msg = "CHESS";
  drawString(957, 120, msg);
  setFont("lucidasans-bold-18");
  drawBitMap(80, 12.5, 2, icon, Xwindow::Black);

}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawBitMap(int cellDim, int row, int col, const int bitmap[80][80], int cellColour) {
  XImage *image = XGetImage(d, w, 0, 0, cellDim, cellDim, AllPlanes, 1);
  for (int row = 0; row < cellDim; ++row) {
    for (int col = 0; col < cellDim; ++col) {
      if (bitmap[row][col] == Transparent) {
        XPutPixel(image, col, row, colours[cellColour]);
      } else {
        XPutPixel(image, col, row, colours[bitmap[row][col]]);
      }
    }
  }
  XPutImage(d, w, gc, image, 0, 0, cellDim * row, cellDim * col, cellDim, cellDim);
  XDestroyImage(image);
  XSync(d, 1);
}