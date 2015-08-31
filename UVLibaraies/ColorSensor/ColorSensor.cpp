/*
1. Wire directly to ground to turn it off completely.
2. Wire to a spare digital pin and control it with digitalWrite().
3. Wire the LED pin to the INT pin and control with setInterrupt() (See Library Reference
*/

#include "ColorSensor.h"
#include "Arduino.h";
#include "Wire.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);


ColorSensor::ColorSensor(){

	
}

void ColorSensor::initializedColorSensor(){

	if(tcs.begin()){
		Serial.println("Found sensor");
	}else{
		Serial.println("Color sensor not found.....check connecton!");
		while(1);
	}
}


void ColorSensor::getSkinColor(){
		
	uint16_t r, g, b, c, colorTemp, lux;

	tcs.getRawData(&r, &g, &b, &c);
  	colorTemp = tcs.calculateColorTemperature(r, g, b);
 	lux = tcs.calculateLux(r, g, b);

 	Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

}




