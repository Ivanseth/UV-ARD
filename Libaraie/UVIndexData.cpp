
#include "UVIndex.h"
#include "Arduino.h";

const int UV_INDEX_ARRAY = 11;
const int MSD_ARRAY = 11; 

const String MSDValue[MSD_ARRAY] = {"70-120",
"35-100",
"22-67",
"18-50",
"15-40",
"11-34",
"10-29",
"9-25",
"8-24",
"7-20",
"6-18",
"5-7"}; // Minutes to Skin Damage, is set up in the y-axis

const int UVIndexValue[UV_INDEX_ARRAY] = {1,2,3,4,5,6,7,8,9,10,11,12};





UVIndex::UVIndex(){


}


//Her kan man også lage en parameter for hud type: skinType
void UVIndex::getMinutes(float uvValue){

	for(int i = 0; i < UV_INDEX_ARRAY; i++){

			int convertedValue = (int)(uvValue + 0.5);

			if(convertedValue  == UVIndexValue[i]){

				return MSDValue[i];

			}

	}

}











