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

Touch::Touch( char Y1, char X2, char Y2, char X1 ) {
  _Y1 = Y1;
  _X2 = X2;
  _Y2 = Y2;
  _X1 = X1;

  for(int i = 0; i < 20; i++) {
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
  //Save last x and y position
  _xLast = _xPos; 
  _yLast = _yPos;

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
  _xPos = analogRead(_Y1);  //Read new xPos

  if(_xPos < 950 && _yPos < 950 ) {
    if(_newTouch) {
      //If its first touch reset last position
      //to current position to avoid stray readings
      _xLast = _xPos;
      _yLast = _yPos;
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

int Touch::xLast(){
  return _xLast;
}

int Touch::yLast(){
  return _yLast;
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


boolean Touch::setButton( char id, char type, int ulx, int uly, int lrx, int lry) {
  if(id < 20) {
    _buttons[id].type = type;
    _buttons[id].ulX = ulx;
    _buttons[id].ulY = uly;
    _buttons[id].lrX = lrx;
    _buttons[id].lrY = lry;

    return true;
  } else {
    return false;
  }
}

int Touch::readButton( char id ) {
  float xCenter, yCenter, angle, lastAngle, deltaAngle;
  if(_touched) {
    //Check if X coordinate is within button bounds
    if(_xPos > _buttons[id].ulX && _xPos < _buttons[id].lrX) {
      //Check if Y coordinate is within button bounds
      if(_yPos > _buttons[id].ulY && _yPos < _buttons[id].lrY ) {
        //Touch is within button bouds
        switch( _buttons[id].type ) {
          case PUSH:
            return 1;
	    break;
	  case VSLIDER:
	    return  map(_yPos, _buttons[id].ulY, _buttons[id].lrY, 0, 255 );
	    break;
	  case HSLIDER:
	    return map(_xPos, _buttons[id].ulX, _buttons[id].lrX, 0, 255 );
	    break;
	  case SPINNER:
            xCenter = ( _buttons[id].lrX - _buttons[id].ulX ) / 2 + _buttons[id].ulX;
            yCenter = ( _buttons[id].lrY - _buttons[id].ulY ) / 2 + _buttons[id].ulY;
            angle = atan2( _yPos - yCenter, _xPos - xCenter );
            lastAngle = atan2( _yLast - yCenter, _xLast - xCenter );
	    deltaAngle = angle - lastAngle;
	    if(deltaAngle > 3.5) {
	      deltaAngle = PI * 2 - deltaAngle;
	    } else if (deltaAngle < -3.5) {
	      deltaAngle = PI * 2 + deltaAngle;
	    }
	    Serial.print(" ulX ");
	    Serial.print(_buttons[id].ulX, DEC);
	    Serial.print(" ulY ");
	    Serial.print(_buttons[id].ulY, DEC);
	    Serial.print(" lrX ");
	    Serial.print(_buttons[id].lrX, DEC);
	    Serial.print(" lrY ");
	    Serial.print(_buttons[id].lrY,DEC);
	    Serial.print(" X ");
	    Serial.print(_xPos, DEC);
	    Serial.print(" Y ");
	    Serial.print(_yPos, DEC);
	    Serial.print(" cX ");
	    Serial.print(xCenter, DEC);
	    Serial.print(" cY ");
	    Serial.print(yCenter, DEC);
	    Serial.print(" lX ");
	    Serial.print(_xLast, DEC);
	    Serial.print(" ly");
	    Serial.print(_yLast, DEC);
	    Serial.print("  A ");
	    Serial.print(angle,DEC);
	    Serial.print("  L ");
	    Serial.print(lastAngle,DEC);
	    Serial.print("  D ");
	    Serial.print(deltaAngle, DEC);
	    Serial.println();
	    return 1;
	    break;
	  default:
	    return 0;
          
        }
        return 1;
      }
    }
  }
  return 0;
}

