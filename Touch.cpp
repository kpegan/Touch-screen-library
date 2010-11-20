/*
 Touch.cpp
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


#include "WProgram.h"
#include "Touch.h"

Touch::Touch(char Y1, char X2, char  Y2, char X1, char nButs) {
  _Y1 = Y1;
  _X2 = X2;
  _Y2 = Y2;
  _X1 = X1;

  //Set the size of array of buttons
  _numButtons = nButs;
  button buttonArray[_numButtons];
  _buttons = buttonArray;

  for(int i = 0; i < _numButtons; i++) {
    _buttons[i].type = EMPTY;
    _buttons[i].value = -1;
    _buttons[i].ulX = 0;
    _buttons[i].ulY = 0;
    _buttons[i].lrX = 0;
    _buttons[i].lrY = 0;
 }

  _xPos = 1024;
  _yPos = 1024;
  _xStart = _xPos;
  _yStart = _yPos;
  _touched = false;
  _newTouch = true;
}

void Touch::read() {
  //Setup Y axis to reading value
  pinMode(_X1, INPUT);
  pinMode(_X2, INPUT);
  pinMode(_Y1, OUTPUT);
  pinMode(_Y2, OUTPUT);
  digitalWrite(_Y1, HIGH);
  digitalWrite(_Y2, LOW);
  delay(1);
  _yPos = analogRead(_X1);
  
  //Setup X axis for reading value
  pinMode(_Y1, INPUT);
  pinMode(_Y2, INPUT);
  pinMode(_X1, OUTPUT);
  pinMode(_X2, OUTPUT);
  digitalWrite(_X1, HIGH);
  digitalWrite(_X2, LOW);
  delay(1);
  
  _xPos = analogRead(_Y1);
  if(_xPos < 950 && _yPos < 950 ) {
    if(_newTouch) {
      _xStart = _xPos;
      _yStart = _yPos;
      _newTouch = false;
    }
    _touched = true;
  } else  {
    _touched = false;
    _newTouch = true; 
  }
  
}

int Touch::xPos(){
  return _xPos;
}

int Touch::yPos(){
  return _yPos;
}

int Touch::xStart(){
  return _xStart;
}

int Touch::yStart(){
  return _yStart;
}

boolean Touch::touched(){
  return _touched;
}
