class IR{
public:
	IR(uint8_t pin) {
		this->pin.init(pin, INPUT);
		barrierValue = 0;
		currentState = false;
		lastState = false;
		currentDebouncedState = false;
		lastDebouncedState = false;
		flagDetected = false;
		flagLost = false;
		debounceTimerStartTime = 0;
		debounceDelay = 100;
	}
	void listen() {
		if (0 == barrierValue) return;
		currentValue = pin.read();
		currentState = abs(currentValue - barrierValue) > 30;
		if (lastState != currentState) {
			debounceTimerStartTime = CURRENT_TIME;
		} else if (debounceTimerStartTime > 0 && (CURRENT_TIME - debounceTimerStartTime) > debounceDelay) { //debounced
			debounceTimerStartTime = 0;
			lastDebouncedState = currentDebouncedState;
			currentDebouncedState = currentState;
			if (lastDebouncedState != currentDebouncedState) {
				flagDetected = currentDebouncedState;
				flagLost = !currentDebouncedState;
			}
		}
		lastState = currentState;
		/*Serial.print(currentValue);
		Serial.print(" ");
		Serial.print(currentState);
		Serial.print(" ");
		Serial.println(currentDebouncedState);*/
	}
	bool onDetect() { if (flagDetected) {flagDetected = false;return true;}return false; } 
	bool onLost() { if (flagLost) {flagLost = false;return true;}return false; } 
	void calibration() {
		//Serial.println("init value...");
		barrierValue = 0;
		currentState = false;
		lastState = false;
		currentDebouncedState = false;
		lastDebouncedState = false;
		flagDetected = false;
		flagLost = false;
		debounceTimerStartTime = 0;
		delay(500);
		uint8_t i = 0, l = 30;
		uint16_t s = 0;
		for (i = 0; i < l; i++) {
			s += pin.read();
			delay(200);
		}
		barrierValue = s / l;
		Serial.print("barrierValue=");
		Serial.println(barrierValue);
	}
private:
	PinA pin;
	bool calibrateFlag;
	bool currentState;
	bool lastState;
	bool currentDebouncedState;
	bool lastDebouncedState;
	bool flagDetected;
	bool flagLost;
	uint16_t currentValue;
	uint16_t barrierValue;
	uint8_t barrierValueDelta;
	unsigned long int debounceTimerStartTime;
	unsigned int debounceDelay;
};
