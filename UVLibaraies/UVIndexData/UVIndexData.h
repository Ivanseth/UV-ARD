

#ifndef UVIndexData_h
#define UVIndexData_h

#include "Arduino.h";

class UVIndexData{
	public:
		UVIndexData();
		char* getMinutes(float uvValue);
	private:
		void stringToCharArray(int index, int stringSize);
};

#endif