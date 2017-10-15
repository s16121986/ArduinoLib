class Leak : public ModuleA {
public:
	Leak(int pin) : ModuleA(pin, INPUT) {
		highValue = 100;
		currentDebouncedState = LOW;
		debounceDelay = 120;
	}
	void listen() {
		currentState = read() > highValue;
		if (currentState != lastState) {
			debounceTimerStartTime = CURRENT_TIME;
		} else if (debounceTimerStartTime > 0 && (CURRENT_TIME - debounceTimerStartTime) > debounceDelay) {
			currentDebouncedState = currentState;
		}
		lastState = currentState;
	}
	bool isHigh() { return currentDebouncedState; }
protected:
	bool lastState;
	bool currentState;
	bool lastDebouncedState;
	bool currentDebouncedState;
	uint16_t highValue;
	unsigned long int debounceTimerStartTime;
	unsigned int debounceDelay;
};
