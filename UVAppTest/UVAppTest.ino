#include <UVIndexData.h>
#include <UVsensor.h>
#include <LiquidCrystal.h>
#include "ColorSensor.h"


#include "Wire.h"
#include "Adafruit_TCS34725.h"

LiquidCrystal lcd(8,9,4,5,6,7);

const int TABEL_LENGTH = 5;
float uvItensityValues[TABEL_LENGTH]; //This will contain five uv itensity values;

const int UVOUT = A0; //Output from the sensor
const int REF_3v3 = A1;	//3.3V power on the arduino
const int pushButton = 2;

//Classe´s
UVsensor UVsensor(UVOUT, REF_3v3);
UVIndexData uvData;
ColorSensor colorSeneor;




void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  colorSeneor.initializedColorSensor();
  pinMode(pushButton, INPUT);

  lcd.setCursor(0,0);
  lcd.print("Welcome User");

  lcd.setCursor(0,1);
  lcd.print("UVIndex: ");

}


void loop() {

    float uvValue = UVsensor.updateUVItensity(); // sensor class

    lcd.setCursor(0,1);
    lcd.print("UVIten.: ");
    lcd.setCursor(9,1);
    lcd.print(uvValue); 

    collectUVData(); 
    colorSeneor.getSkinColor();

  	delay(100);
}


//This will collect the data after pushing the button
void collectUVData(){
 
  int i = 0;
  if(digitalRead(pushButton) == HIGH){
     
     while(i < TABEL_LENGTH){

        displayCountdownInSec(5,i);
        uvItensityValues[i] = UVsensor.updateUVItensity();
        delay(1000);
        i++;
      }

      if(i == TABEL_LENGTH ){

        i=0;  
        float calcAvgUvItensity =  calculateAverageUVIntensety(uvItensityValues);
        displayFinalUVItensety(calcAvgUvItensity);
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





///////////////////////////////////////////////////////////////
//Denne klassen kan inneholde alle print/text/display visninger

void displayCalculatingToDisplay(){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Calculating..");
    delay(300);
}


//Sett I egen klasse
void displayFinalUVItensety(char uvItensity){

    char *pointerMSDValue;
    pointerMSDValue = uvData.getMinutes(uvItensity);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MSD: ");
    lcd.setCursor(4,0);
    lcd.print(pointerMSDValue);

}

void displayFinalMSD(float msd){

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MSD: ");
        lcd.setCursor(6,0);
        lcd.print(msd);
}


//Sett i egen klasse
void displayCountdownInSec(int startSec, int remianingSec){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Collecting data....");
  lcd.setCursor(0,1);
  lcd.print("Waiting: ");
  lcd.setCursor(8,1);
  lcd.print(startSec-remianingSec);

}






