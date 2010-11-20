/*
 Touch.h
 Touch
 
 Created by Kelly Egan on 4/30/10.
 
 This is a simple library for interfacing a resistive touchscreen with an Arduino.
 
 The MIT License
 
 Copyright (c) <2010> Kelly Egan
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
*/

#ifndef Touch_h
#define Touch_h

#include "WProgram.h"

//Button types
enum {
  EMPTY,
  PUSH,
  SLIDER,
  SPIN
};

typedef struct {
  char type;
  int value;
  int ulX;     //upper left corner x position
  int ulY;     //upper left corner y position
  int lrX;     //lower right corner x position
  int lrY;     //lower right corner y position
} button;

class Touch 
{

public:
  Touch(char Y1, char X2, char Y2, char X1, char nButs);
  void read();
  int xPos();
  int yPos();
  int xStart();
  int yStart();
  boolean touched();
  boolean setButton( char id, char type, int ulx, int uly, int lrx, int lry);
  int readButton( char id );
  

private:
  char _Y1;
  char _X2;
  char _Y2;
  char _X1;
  
  int _xPos;
  int _yPos;
  int _xStart;
  int _yStart;
  boolean _touched;
  boolean _newTouch;
  button* _buttons;
  char _numButtons;
  
};

#endif
