unsigned int PWM_DELAY = 1000;
byte PWM_BRIGHTNESS = 255;

class PWM : public ModuleD{
public:
	PWM() {}
	PWM(int pin) : ModuleD(pin, OUTPUT) {
		dimmingIncrement = 1;
		currentBrightness = 0;
		maxBrightness = 255;
		lastBrightness = maxBrightness;
		brightnessDelayTime = 0;
		dimmingFlag = false;
		setPWMMode(true);
	}
	void listen() {
		currentTime = CURRENT_TIME;
		if (dimmingFlag) {
			currentBrightness += dimmingIncrement * 5;
			if (currentBrightness <= 0) {
				currentBrightness = 0;
				dimmingIncrement = 1;
			} else if (currentBrightness >= maxBrightness) {
				currentBrightness = maxBrightness;
				dimmingIncrement = -1;
			}
			write(currentBrightness);
		} else if (brightnessDelayTime > 0) {
			if (currentTime - brightnessDelayTime >= brightnessDelay) {
				Serial.println(currentBrightness);
				write(currentBrightness);
				brightnessDelayTime = 0;
			} else {
				Serial.println(lastBrightness + (currentBrightness - lastBrightness) * (float)(currentTime - brightnessDelayTime) / brightnessDelay);
				write(lastBrightness + (currentBrightness - lastBrightness) * (float)(currentTime - brightnessDelayTime) / brightnessDelay);
			}
		}
	}
	void on() { on(PWM_BRIGHTNESS, PWM_DELAY); }
	void on(byte brightness) { on(brightness, PWM_DELAY); }
	void on(byte brightness, int speed) {
		if (brightness == currentBrightness) return;
		lastBrightness = currentBrightness;
		currentBrightness = brightness;
		brightnessDelay = speed;
		if (speed == 0) {
			write(currentBrightness);
			brightnessDelayTime = 0;
		} else {
			brightnessDelayTime = currentTime;
		}
	}
	void off() { off(0); }
	void off(int speed) { if (currentBrightness > 0) on(0, speed); }
	bool isOn() { return currentBrightness > 0; }
	void toggle() { if (isOn()) off(); else on(); }
	void setBrightnessDelay(unsigned int delay) { brightnessDelay = delay; }
	void setBrightness(byte brightness) { if (isOn()) on(brightness); else lastBrightness = brightness; }
	byte getBrightness() { return currentBrightness; }
	void setDimming(bool flag) {
		dimmingFlag = flag;
		if (flag) {
			lastBrightness = currentBrightness;
		}
		brightnessDelayTime = 0;
	}
	bool isDimming() { return dimmingFlag; }
	/*void setEEPROMAddress(byte addr) {
		EEPROMAddress = addr;
		brightnessCache = EEPROM.read(EEPROMAddress);
	}*/
private:
	byte maxBrightness;
	byte currentBrightness = 0;
	byte lastBrightness = 0;
	
	unsigned int brightnessDelay;
	unsigned long int brightnessDelayTime;	
	unsigned long int currentTime;
	
	bool dimmingFlag;
	byte dimmingIncrement;
};