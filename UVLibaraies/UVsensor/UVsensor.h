

#ifndef UVsensor_h
#define UVsensor_h
 
 class UVsensor{
 	public:
 		UVsensor(int output, int ref_3v3);
 		float updateUVItensity();
 		int averageAnalogRead(float pinToRead);

 	private:
 		float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
 		void printUVintensetyToSerial(int uvLevel, int refLevel, float outputVoltage, float uvItensity);
 		int _output;
 		int _ref_3v3;
 };

#endif