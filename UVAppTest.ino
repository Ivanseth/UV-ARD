
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

const int TABEL_LENGTH = 5;

float uvItensityValues[TABEL_LENGTH]; //This will contain five uv itensity values;
float uvItensity;


const int UVOUT = A0; //Output from the sensor
const int REF_3v3 = A1;	//3.3V power on the arduino
const int pushButton = 2;






void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3v3, INPUT);
  pinMode(pushButton, INPUT);

  lcd.setCursor(0,0);
  lcd.print("Welcome User");

  lcd.setCursor(0,1);
  lcd.print("UVIten.: ");

}


void loop() {

    
  	//printUVintensetyToDisplay(uvItensity);
    //printUVintensetyToSerial( uvLevel,refLevel,outputVoltage,uvItensity);

    lcd.setCursor(0,1);
    lcd.print("UVIten.: ");
    lcd.setCursor(9,1);
    float uvValue = updateUVItensity();
    lcd.print(uvValue);

    collectUVData();


  	delay(100);
}



float updateUVItensity(){

    int uvLevel =  averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3v3);
    float outputVoltage = 3.3/ refLevel * uvLevel;

    uvItensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensety level
    
    if(uvItensity < 0) uvItensity = 0;

    return uvItensity;
}


/*
void printUVintensetyToDisplay(float uvItensity){
  
  lcd.setCursor(12,1);
  lcd.print(uvItensity);
}*/



void collectUVData(){
 
  int i = 0;
  if(digitalRead(pushButton) == HIGH){
     
     while(i < TABEL_LENGTH){

        displayCountdownInSec(5,i);
        uvItensityValues[i] = updateUVItensity();
        delay(1000);
        i++;
      }

      if(i == TABEL_LENGTH ){

        i=0;  
        displayFinalUVItensety(calculateAverageUVIntensety(uvItensityValues));
      }
  }
    
}

//Regner ut gjennomsnittet til en tabell
//Denne function kan settes i en egen classe
float calculateAverageUVIntensety(float values[]){


    displayCalculatingToDisplay();
    float value = 0;

    for(int i =0; i < TABEL_LENGTH; i++){
      value += values[i];
    }
    
    value /= TABEL_LENGTH;
    return value;
}


//Regner ut gjennomsnittet til inputs
//Denne function kan settes i en egen classe
int averageAnalogRead(float pinToRead){

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
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




///////////////////////////////////////////////////////////////
//Denne klassen kan inneholde alle print/text/display visninger



void displayCalculatingToDisplay(){


    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Calculating..");
    delay(300);

}


//Sett I egen klasse
void displayFinalUVItensety(float uvItensity){

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Value: ");
        lcd.setCursor(6,0);
        lcd.print(uvItensity);


}

//Sett i egen klasse
void displayCountdownInSec(int startSec, int remianingSec){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Collection data....");
  lcd.setCursor(0,1);
  lcd.print("Waiting: ");
  lcd.setCursor(8,1);
  lcd.print(startSec-remianingSec);

}



//Sett i egen klasse
void printUVintensetyToSerial(float uvLevel, float refLevel, float outputVoltage, float uvItensity){
    

    Serial.print("UV Level: ");
    Serial.print(uvLevel);

    Serial.print(" Ref leve: ");
    Serial.print(refLevel);

    Serial.print(" Output Volt: ");
    Serial.print(outputVoltage);

    Serial.print(" UV intensety (mW/cm^2): ");
    Serial.println(uvItensity);
  
}

