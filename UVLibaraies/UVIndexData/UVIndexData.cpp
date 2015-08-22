/*
 UVIndexData.cpp-This file will contain the data or the calculation of the MSD(Minutes to Skin Damage)
*/

#include "UVIndexData.h";
#include "Arduino.h";

const int UV_INDEX_ARRAY = 12;
const int MSD_ARRAY = 12; 

String MSDAlwaysValue[MSD_ARRAY] = {
"70-120",
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

String MSDUsallyValue[MSD_ARRAY] = {
"120",
"100-120",
"67-111",
"50-84",
"50-67",
"33-56",
"28-47",
"25-43",
"23-38",
"20-34",
"18-30",
"16-28"};



const int UVIndexValue[UV_INDEX_ARRAY] = {1,2,3,4,5,6,7,8,9,10,11,12}; //UV Index (mJ/cm^2)



UVIndex::UVIndex(){

}


//Her kan man også lage en parameter for hud type: skinType
void UVIndexData::getMinutes(float uvValue){

	for(int i = 0; i < UV_INDEX_ARRAY; i++){

		int convertedValue = (int)(uvValue + 0.5);

		if(convertedValue  == UVIndexValue[i]){

			return MSDAlwaysValue[i];

		}
	}
}











