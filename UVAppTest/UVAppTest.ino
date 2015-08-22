#include <UVIndexData.h>
#include <UVsensor.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(8,9,4,5,6,7);

const int TABEL_LENGTH = 5;
float uvItensityValues[TABEL_LENGTH]; //This will contain five uv itensity values;

const int UVOUT = A0; //Output from the sensor
const int REF_3v3 = A1;	//3.3V power on the arduino
const int pushButton = 2;

UVsensor UVsensor(UVOUT, REF_3v3);
UVIndexData uvData;


void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

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

    char* testChar;

    testChar = uvData.getMinutes(uvValue);

    for(int i = 0; i < 6; i++){
        Serial.print(testChar[i]);
    }
    Serial.println();

    collectUVData(); 


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
        float calcAvgUvInte =  calculateAverageUVIntensety(uvItensityValues);
        displayFinalUVItensety(calcAvgUvInte);
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
void displayFinalUVItensety(float uvItensity){

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Value: ");
        lcd.setCursor(6,0);
        lcd.print(uvItensity);


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
  lcd.print("Collection data....");
  lcd.setCursor(0,1);
  lcd.print("Waiting: ");
  lcd.setCursor(8,1);
  lcd.print(startSec-remianingSec);

}





