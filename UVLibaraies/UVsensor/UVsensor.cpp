
#include "UVsensor.h";
#include "Arduino.h";


UVsensor::UVsensor(int output, int ref_3v3 ){
	
	pinMode(output, INPUT);
  pinMode(ref_3v3, INPUT);
  
	_output = output;
	_ref_3v3 = ref_3v3;
}




float UVsensor::updateUVItensity(){

    int uvLevel =  averageAnalogRead(_output);
    int refLevel = averageAnalogRead(_ref_3v3);
    
    float outputVoltage = (3.3/ refLevel * uvLevel);
    float uvItensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensety level
    //printUVintensetyToSerial(uvLevel, refLevel, outputVoltage, uvItensity);
   
    if(uvItensity < 0) uvItensity = 0;

    return uvItensity;
}



int UVsensor::averageAnalogRead(float pinToRead){

  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for(int x = 0; x < numberOfReadings; x++){
    runningValue += analogRead(pinToRead);    
  }

  runningValue /= numberOfReadings;

  return runningValue;

}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
//Denne function kan settes i en egen classe
float UVsensor::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Sett i egen klasse
void UVsensor::printUVintensetyToSerial(int uvLevel, int refLevel, float outputVoltage, float uvItensity){
    

    Serial.print("UV Level: ");
    Serial.print(uvLevel);

    Serial.print(" Ref leve: ");
    Serial.print(refLevel);

    Serial.print(" Output Volt: ");
    Serial.print(outputVoltage);

    Serial.print(" UV intensety (mW/cm^2): ");
    Serial.println(uvItensity);
  
}

