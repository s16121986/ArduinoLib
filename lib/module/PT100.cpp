#define PT100_A 0.0039083
#define PT100_B -0.0000005775

class PT100 : public ModuleA{
public:
	PT100 (int pin, unsigned int R1): ModuleA(pin, INPUT) {
		this->R1 = R1;
	}
	float getTemperature() {
		U1 = 5.0 * read() / 1023.0;
		if (U1 == 0) return NAN;
		else if (U1 > 2.0) return NAN;
		Rt = U1 * R1 / (U - U1);
		Serial.print(";U1=");
		Serial.print(U1);
		Serial.print(";Rt=");
		Serial.print(Rt);/**/
		return (sqrt(pow(PT100_A, 2.0) - 4 * PT100_B * (1 - Rt / 100.0)) - PT100_A) / (2.0 * PT100_B);
	}
protected:
	float U = 5.1;
	float U1;
	float Rt;
	float R1;
};
